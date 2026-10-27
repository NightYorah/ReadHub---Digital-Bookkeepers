#include "uploadwindow.h"
#include "./ui_uploadwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include <fpdfview.h>
#include "readwindow.h"
#include "mainwindow.h"

UploadWindow::UploadWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UploadWindow)
{
    ui->setupUi(this);

    connect(ui->Quick_PDF, &QPushButton::clicked, this, [this] {
        auto *window = new ReadWindow(ui->File_Path->text());
        window->setAttribute(Qt::WA_DeleteOnClose);
        window->show();
    });

//Hides these buttons until they are needed
    ui->Quick_PDF->hide();
    ui->Back2Main->hide();

    FPDF_LIBRARY_CONFIG config{};
    config.version = 2;
    FPDF_InitLibraryWithConfig(&config);


    //When Upload_Button pressed, opens file explorer
    connect(ui->Upload_Button, &QPushButton::clicked, this, [this]{
        const QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a PDF"), QString(), tr ("PDF Files (*.pdf)"));

//If no file is selected, goes back to the upload menu
    if(fileName.isEmpty())
    {
        ui->Back2Main->show();
    }

    const QByteArray pathBytes = fileName.toUtf8();
    FPDF_DOCUMENT book = FPDF_LoadDocument(pathBytes.constData(), nullptr);

    ui->Quick_PDF->show();

    //Error message for a PDF not being loaded correctly
    if(!book)
    {
        QMessageBox::warning(this, tr("PDF ERROR"), tr("Could not open the PDF"));
        return;
    }

    const int pageCount = FPDF_GetPageCount(book);


    FPDF_CloseDocument(book);

    ui->File_Path->setText(fileName);
    }
    );
}

UploadWindow::~UploadWindow()
{
    delete ui;
}

//Allows the user to navigate back to the main menu
void UploadWindow::on_Back2Main_clicked()
{
    MainWindow *w = new MainWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    this->close();
}

