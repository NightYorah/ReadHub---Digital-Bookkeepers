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

    // A small helper for messages that should appear in the reader window.
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

    // Page indexes start at zero, so i = 0 is the first page.
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

            // Make the image own its pixels before destroying the PDFium bookmap.
            image = image.copy();

            // Make a small widget for this page: a page number and its image.
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

        // These are temporary PDFium objects for this page.
        FPDFBitmap_Destroy(bookmap);
        FPDF_ClosePage(page);
    }

    if (renderedPages == 0) {
        showMessage("Could not render any pages.");
        QMessageBox::warning(this, "PDF Error", "Could not render any pages.");
    } else if (failedPages > 0) {
        showMessage("Some pages could not be rendered.");
    }

    // Size the scroll area's contents to fit the page widgets.
    pagesWidget->adjustSize();
}

ReadWindow::~ReadWindow()
{
    if (document)
        FPDF_CloseDocument(document);
}
