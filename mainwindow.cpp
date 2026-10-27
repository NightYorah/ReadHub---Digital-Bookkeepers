#include "mainwindow.h"
#include "uploadwindow.h"
#include "./ui_mainwindow.h"
#include "loginwindow.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadDummyData();
    displayBooks(m_allBooks);

    connect(ui->searchLineEdit, &QLineEdit::textChanged,
            this, &MainWindow::onSearchTextChanged);

    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSortOptionChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDummyData()
{
    m_allBooks = {
                   {"Harry Potter", "J.K. Rowling", "1997-06-26", 4.9},
                   {"Jane Eyre", "Charlotte Brontë", "1847-10-16", 4.5},
                   {"Wuthering Heights", "Emily Brontë", "1847-12-01", 4.3},
                   {"Gone with the Wind", "Margaret Mitchell", "1936-06-30", 4.8}
    };
}

void MainWindow::displayBooks(const std::vector<BookItem>& books)
{
    ui->bookListWidget->clear();
    for (const auto& book : books) {
        QString displayText = QString("%1  |  Author: %2  |  Date: %3 | Rating: %4 ★")
            .arg(book.title, book.author, book.date)
            .arg(QString::number(book.rating, 'f', 1));
        ui->bookListWidget->addItem(displayText);
    }
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    std::vector<BookItem> filteredBooks;
    for (const auto& book : m_allBooks) {
        if (text.isEmpty() || book.title.contains(text, Qt::CaseInsensitive)) {
            filteredBooks.push_back(book);
        }
    }
    displayBooks(filteredBooks);
}

void MainWindow::onSortOptionChanged(int index)
{
    std::vector<BookItem> sortedBooks = m_allBooks;
    if (index == 0) { // Title (A-Z)
        std::sort(sortedBooks.begin(), sortedBooks.end(), [](const BookItem& a, const BookItem& b){
            return a.title < b.title;
        });
    }
    else if (index == 1) { //Rating(five stars)
        std::sort(sortedBooks.begin(), sortedBooks.end(), [](const BookItem& a, const BookItem& b){
            return a.rating > b.rating;
        });
    }
    displayBooks(sortedBooks);
}
void MainWindow::on_Switch2Upload_clicked()
{
    UploadWindow *w = new UploadWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    this->close();
}


void MainWindow::on_pushButton_clicked()
{
    LoginWindow *w = new LoginWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    this->close();
}

