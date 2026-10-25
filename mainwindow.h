#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

struct BookItem{
    QString title;
    QString author;
    QString date;
    double rating;
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

private:
    Ui::MainWindow *ui;
    std::vector<BookItem> m_allBooks;

    void loadDummyData();
    void displayBooks(const std::vector<BookItem>& books);
};
#endif // MAINWINDOW_H
