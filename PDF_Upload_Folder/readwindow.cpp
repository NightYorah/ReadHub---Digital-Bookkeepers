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
    resize(1920, 1080);

    auto *pagesWidget = new QWidget;
    auto *pagesLayout = new QVBoxLayout(pagesWidget);
    pagesLayout->setAlignment(Qt::AlignHCenter);

    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(pagesWidget);
    scrollArea->setWidgetResizable(true);
    setCentralWidget(scrollArea);

    const QByteArray pathBytes = pdfPath.toUtf8();
    document = FPDF_LoadDocument(pathBytes.constData(), nullptr);

    if (!document) {
        readLabel->setText("Could not open the PDF.");
        QMessageBox::warning(this, "PDF Error", "Could not open the PDF.");
        return;
    }

    const int pageCount = FPDF_GetPageCount(document);
    constexpr double scale = 1.0;  // Try 1.0 first; increase if memory allows

    for (int i = 0; i < pageCount; ++i) {
        FPDF_PAGE page = FPDF_LoadPage(document, i);
        if (!page) {
            continue;
        }

        const int width =
            static_cast<int>(FPDF_GetPageWidthF(page) * scale);
        const int height =
            static_cast<int>(FPDF_GetPageHeightF(page) * scale);

        if (width <= 0 || height <= 0) {
            FPDF_ClosePage(page);
            continue;
        }

        FPDF_BITMAP bitmap = FPDFBitmap_Create(width, height, 1);
        if (!bitmap) {
            FPDF_ClosePage(page);
            continue;
        }

        FPDFBitmap_FillRect(bitmap, 0, 0, width, height, 0xFFFFFFFF);
        FPDF_RenderPageBitmap(bitmap, page, 0, 0, width, height, 0, 0);

        const auto *pixels =
            static_cast<const uchar *>(FPDFBitmap_GetBuffer(bitmap));

        if (pixels) {
            QImage image(
                pixels,
                width,
                height,
                FPDFBitmap_GetStride(bitmap),
                QImage::Format_ARGB32
                );

            auto *pageLabel = new QLabel;
            pageLabel->setAlignment(Qt::AlignCenter);
            pageLabel->setPixmap(QPixmap::fromImage(image.copy()));
            pagesLayout->addWidget(pageLabel);

            auto *numberLabel = new QLabel(QString("Page %1").arg(i + 1));
            numberLabel->setAlignment(Qt::AlignCenter);
            pagesLayout->addWidget(numberLabel);
        }

        FPDFBitmap_Destroy(bitmap);
        FPDF_ClosePage(page);
    }
}

ReadWindow::~ReadWindow()
{
    if (document)
        FPDF_CloseDocument(document);
}