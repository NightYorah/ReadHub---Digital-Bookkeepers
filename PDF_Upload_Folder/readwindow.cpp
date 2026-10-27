#include "readwindow.h"

#include <QImage>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QScrollArea>

ReadWindow::ReadWindow(const QString &pdfPath, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("PDF Reader");
    resize(1920, 1080);

    readLabel = new QLabel;
    readLabel->setAlignment(Qt::AlignCenter);

    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(readLabel);
    scrollArea->setWidgetResizable(false);
    scrollArea->setAlignment(Qt::AlignCenter);
    setCentralWidget(scrollArea);

    const QByteArray pathBytes = pdfPath.toUtf8();
    document = FPDF_LoadDocument(pathBytes.constData(), nullptr);

    if (!document) {
        readLabel->setText("Could not open the PDF.");
        QMessageBox::warning(this, "PDF Error", "Could not open the PDF.");
        return;
    }

    FPDF_PAGE page = FPDF_LoadPage(document, 0);
    if (!page) {
        readLabel->setText("Could not load the first page.");
        QMessageBox::warning(this, "PDF Error", "Could not load the first page.");
        return;
    }

    constexpr double scale = 2.0;
    const int width =
        static_cast<int>(FPDF_GetPageWidthF(page) * scale);
    const int height =
        static_cast<int>(FPDF_GetPageHeightF(page) * scale);

    if (width <= 0 || height <= 0) {
        readLabel->setText("The first page has invalid dimensions.");
        QMessageBox::warning(this, "PDF Error",
                             "The first page has invalid dimensions.");
        FPDF_ClosePage(page);
        return;
    }

    FPDF_BITMAP bitmap = FPDFBitmap_Create(width, height, 1);
    if (!bitmap) {
        readLabel->setText("Could not create the page image.");
        QMessageBox::warning(this, "PDF Error",
                             "Could not create the page image.");
        FPDF_ClosePage(page);
        return;
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

        readLabel->setPixmap(QPixmap::fromImage(image.copy()));
        readLabel->adjustSize();
    } else {
        readLabel->setText("PDFium returned an empty image.");
        QMessageBox::warning(this, "PDF Error",
                             "PDFium returned an empty image.");
    }

    FPDFBitmap_Destroy(bitmap);
    FPDF_ClosePage(page);
}

ReadWindow::~ReadWindow()
{
    if (document)
        FPDF_CloseDocument(document);
}
