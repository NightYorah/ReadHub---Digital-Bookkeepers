#ifndef UPLOADWINDOW_H
#define UPLOADWINDOW_H

#include <QString>
#include <QList>
#include <QMainWindow>
#include <QImage>
#include <fpdfview.h>

#include "readwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class UploadWindow;
}
QT_END_NAMESPACE

struct FileUpload
{
    QString path;
    QString book_title;
    QString book_author;
    QString book_publisher;
    QString publish_date;
};

class UploadWindow : public QMainWindow
{
    Q_OBJECT

private:
    FPDF_DOCUMENT book = nullptr;
    int currentPage = 0;
    void showPage(int pageIndex);

public:
    explicit UploadWindow(QWidget *parent = nullptr);
    ~UploadWindow() override;

private:
    ReadWindow *mMyReadWindow;

private:
    Ui::UploadWindow *ui;


private:
    QList<FileUpload> book_metadata;
};

#endif // UPLOADWINDOW_H
