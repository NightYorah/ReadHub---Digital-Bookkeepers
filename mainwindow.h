#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QString>
#include "uploadwindow.h"
#include <vector>

struct UserReview
{
    QString username;
    int rating;
    QString comment;
    QString date;
};

struct BookItem
{
    QString title;
    QString author;
    QString date;
    double rating;
    QString path;
    QList<UserReview> reviews;
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
    void displayBooks(const std::vector<BookItem> &books);

public:
    void setBooks(const QList<FileUpload> &books);

private:
    QString libraryFilePath() const;
    void saveLibrary() const;
    void loadLibrary();
    void saveAllReviews() const;
    void loadAllReviews();
};
#endif // MAINWINDOW_H
