#include "mainwindow.h"
#include "uploadwindow.h"
#include "./ui_mainwindow.h"
#include "loginwindow.h"
#include <algorithm>
#include <QPushButton>
#include "readwindow.h"

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
        QListWidgetItem *item = new QListWidgetItem(ui->bookListWidget);
        QPushButton *btn = new QPushButton(displayText);
        item->setSizeHint(btn->sizeHint());
        ui->bookListWidget->setItemWidget(item, btn);

        //Added functionality of reading a book from main window library
        const QString path = book.path;
        connect(btn, &QPushButton::clicked, this, [path] {
            if (path.isEmpty()) return;   // dummy books have no file
            auto *window = new ReadWindow(path);
            window->setAttribute(Qt::WA_DeleteOnClose);
            window->show();
        });
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

//Added functionality of creating a new library item when a PDF is uploaded
//TESTING COULD INCLUDE THE METADATA STORED (correctly or not) AND HOW IT IS NOT SAVED PERMANENTLY
void MainWindow::setBooks(const QList<FileUpload> &books)
{
    for (const FileUpload &item : books)
    {
        BookItem b;
        b.title  = item.book_title.isEmpty() ? item.filePath : item.book_title;
        b.author = item.book_author;
        b.rating = 0.0;
        b.path   = item.filePath;
        m_allBooks.push_back(b);
    }
    displayBooks(m_allBooks);
}


