#include "uploadwindow.h"
#include "./ui_uploadwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include <fpdfview.h>
#include <fpdf_doc.h>
#include "readwindow.h"
#include "mainwindow.h"

UploadWindow::UploadWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UploadWindow)
{
{
    ui->setupUi(this);

//Hides these buttons until they are needed
    ui->Load_FP->hide();
    ui->Back2Main->hide();

    FPDF_LIBRARY_CONFIG config{};
    config.version = 2;
    FPDF_InitLibraryWithConfig(&config);


    //When Upload_Button pressed, opens file explorer
    connect(ui->Upload_Button, &QPushButton::clicked, this, [this]{
        fileName = QFileDialog::getOpenFileName(this, tr("Choose a PDF"), QString(), tr ("PDF Files (*.pdf)"));

//If no file is selected, goes back to the upload menu
    if(fileName.isEmpty())
    {
        ui->File_Path->clear();
        ui->Load_FP->hide();
        ui->Back2Main->show();
        return;
    }

    const QByteArray pathBytes = fileName.toUtf8();
    FPDF_DOCUMENT book = FPDF_LoadDocument(pathBytes.constData(), nullptr);

    //Error message for a PDF not being loaded correctly
    if(!book)
    {
        QMessageBox::warning(this, tr("PDF ERROR"), tr("Could not open the PDF"));
        return;
    }

    //Clears journey to ensure that every new upload is fresh
    journey = FileUpload();
    journey.filePath = fileName;

    unsigned long len = FPDF_GetMetaText(book, "Title", nullptr, 0);
    if (len > 2)
    {
        QByteArray buf(static_cast<int>(len), 0);
        FPDF_GetMetaText(book, "Title", buf.data(), len);
        journey.book_title = QString::fromUtf16(reinterpret_cast<const char16_t *>(buf.constData()));
    }

    len = FPDF_GetMetaText(book, "Author", nullptr, 0);
    if (len > 2)
    {
        QByteArray buf(static_cast<int>(len), 0);
        FPDF_GetMetaText(book, "Author", buf.data(), len);
        journey.book_author = QString::fromUtf16(reinterpret_cast<const char16_t *>(buf.constData()));
    }

    ui->Load_FP->show();

    //const int pageCount = FPDF_GetPageCount(book); unused but syntax might be useful later


    FPDF_CloseDocument(book);

    ui->File_Path->setText(fileName);
    }
    );

    connect(ui->Load_FP, &QPushButton::clicked, this, [this]()
    {

        if (fileName.isEmpty()) return;
        book_metadata.append(journey);
        QMessageBox::information(this, tr("Upload"), tr("PDF Uploaded"));
        ui->Back2Main->show();
    });
}
}

UploadWindow::~UploadWindow()
{
    delete ui;
}

//Allows the user to navigate back to the main menu
void UploadWindow::on_Back2Main_clicked()
{
    MainWindow *w = new MainWindow();
    w->setBooks(book_metadata);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    this->close();
}

