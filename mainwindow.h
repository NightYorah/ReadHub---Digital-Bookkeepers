#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QList>
#include "uploadwindow.h"

struct BookItem{
    QString title;
    QString author;
    QString date;
    double rating;
    QString path;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchTextChanged(const QString &text);
    void onSortOptionChanged(int index);

    void on_Switch2Upload_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<BookItem> m_allBooks;

    void loadDummyData();
    void displayBooks(const std::vector<BookItem>& books);

public:
    void setBooks(const QList<FileUpload> &books);
};
#endif // MAINWINDOW_H
