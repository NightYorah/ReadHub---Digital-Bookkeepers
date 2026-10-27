#include "readwindow.h"

#include <QImage>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

ReadWindow::ReadWindow(const QString &pdfPath, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("PDF Reader");
    resize(900, 700);

    // The scroll area holds one widget, which contains the page widgets.
    auto *pagesWidget = new QWidget;
    auto *pagesLayout = new QVBoxLayout(pagesWidget);
    pagesLayout->setAlignment(Qt::AlignHCenter);
    pagesLayout->setSpacing(12);

    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(pagesWidget);
    scrollArea->setWidgetResizable(false);
    scrollArea->setAlignment(Qt::AlignCenter);
    setCentralWidget(scrollArea);

    // Creates messages incase of error checks being needed to show the user something has went wrong
    auto showMessage = [pagesLayout](const QString &message) {
        auto *messageLabel = new QLabel(message);
        pagesLayout->addWidget(messageLabel);
    };

    const QByteArray pathBytes = pdfPath.toUtf8();
    document = FPDF_LoadDocument(pathBytes.constData(), nullptr);

    if (!document) {
        showMessage("Could not open the PDF.");
        QMessageBox::warning(this, "PDF Error", "Could not open the PDF.");
        return;
    }

    const int pageCount = FPDF_GetPageCount(document);

    if (pageCount <= 0) {
        showMessage("This PDF has no pages.");
        QMessageBox::warning(this, "PDF Error", "This PDF has no pages.");
        return;
    }

    constexpr double scale = 1.5;
    int renderedPages = 0;
    int failedPages = 0;

    // Starts at page 0 and continues to iterate until it hits the total page count
    for (int i = 0; i < pageCount; ++i) {
        FPDF_PAGE page = FPDF_LoadPage(document, i);

        if (!page) {
            ++failedPages;
            continue;
        }

        const int width =
            static_cast<int>(FPDF_GetPageWidthF(page) * scale);
        const int height =
            static_cast<int>(FPDF_GetPageHeightF(page) * scale);

        if (width <= 0 || height <= 0) {
            ++failedPages;
            FPDF_ClosePage(page);
            continue;
        }

        FPDF_BITMAP bookmap = FPDFBitmap_Create(width, height, 1);

        if (!bookmap) {
            ++failedPages;
            FPDF_ClosePage(page);
            continue;
        }

        FPDFBitmap_FillRect(bookmap, 0, 0, width, height, 0xFFFFFFFF);
        FPDF_RenderPageBitmap(bookmap, page, 0, 0, width, height, 0, 0);

        const auto *pixels =
            static_cast<const uchar *>(FPDFBitmap_GetBuffer(bookmap));

        if (pixels) {
            QImage image(
                pixels,
                width,
                height,
                FPDFBitmap_GetStride(bookmap),
                QImage::Format_ARGB32
                );

            // ensures the image has its pixels before cleaning them up
            image = image.copy();

            // Creates a widget for the page and other details such as pge number and for displaying images
            auto *onePageWidget = new QWidget;
            auto *onePageLayout = new QVBoxLayout(onePageWidget);

            auto *pageNumberLabel =
                new QLabel(QString("Page %1").arg(i + 1));
            pageNumberLabel->setAlignment(Qt::AlignCenter);

            auto *imageLabel = new QLabel;
            imageLabel->setAlignment(Qt::AlignCenter);
            imageLabel->setPixmap(QPixmap::fromImage(image));
            imageLabel->adjustSize();

            onePageLayout->addWidget(pageNumberLabel);
            onePageLayout->addWidget(imageLabel);

            pagesLayout->addWidget(onePageWidget);
            ++renderedPages;
        } else {
            ++failedPages;
        }

        //Necessary cleanup
        FPDFBitmap_Destroy(bookmap);
        FPDF_ClosePage(page);
    }

    if (renderedPages == 0) {
        showMessage("Could not render any pages.");
        QMessageBox::warning(this, "PDF Error", "Could not render any pages.");
    } else if (failedPages > 0) {
        showMessage("Some pages could not be rendered.");
    }

    // Fits the contents into the page widget's size
    pagesWidget->adjustSize();
}

ReadWindow::~ReadWindow()
{
    if (document)
        FPDF_CloseDocument(document);
}
