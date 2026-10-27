#include "uploadwindow.h"
#include "./ui_uploadwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include <fpdfview.h>
#include "readwindow.h"

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


    ui->Quick_PDF->hide();
    ui->Back2Main->hide();

    FPDF_LIBRARY_CONFIG config{};
    config.version = 2;
    FPDF_InitLibraryWithConfig(&config);


    //When Upload_Button pressed, opens file explorer
    connect(ui->Upload_Button, &QPushButton::clicked, this, [this]{
        const QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a PDF"), QString(), tr ("PDF Files (*.pdf)"));


    if(fileName.isEmpty())
    {
        ui->Back2Main->show();
        return;
    }
    else
    {
        ui->Back2Main->show();
    }

    const QByteArray pathBytes = fileName.toUtf8();
    FPDF_DOCUMENT book = FPDF_LoadDocument(pathBytes.constData(), nullptr);

    ui->Quick_PDF->show();

    if(!book)
    {
        QMessageBox::warning(this, tr("PDF ERROR"), tr("Could not open the PDF"));
        return;
    }


    FPDF_CloseDocument(book);

    //file path needs to be stored for later use
    //After file upload, give success screen
    //Fall back to main library page
    //when library book clicked, open book on its first page
    //be able to click thru all pages until end, then go back to lib main page or book overview screen

    ui->File_Path->setText(fileName);
    }
    );
}

UploadWindow::~UploadWindow()
{
    delete ui;
}
