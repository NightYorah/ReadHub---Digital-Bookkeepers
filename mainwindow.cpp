#include "mainwindow.h"
#include "uploadwindow.h"
#include "./ui_mainwindow.h"
#include "loginwindow.h"
#include "readwindow.h"
#include "StarRatingWidget.h"

#include <algorithm>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadDummyData();
    loadLibrary();
    loadAllReviews(); //load all books' comments and ratings
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
        {"Harry Potter", "J.K. Rowling", "1997-06-26", 4.9, "", {
            {"testuser123", 5, "A timeless classic! World-building is incredible.", "2026-11-15"},
            {"a", 4, "Great pacing and memorable characters.", "2026-11-18"}
            }},
        {"Jane Eyre", "Charlotte Brontë", "1847-10-16", 4.5, "", {
            {"testuser123", 5, "Deeply moving story with strong themes.", "2026-11-12"}
            }},
        {"Wuthering Heights", "Emily Brontë", "1847-12-01", 4.3, "", {
            {"Bob", 4, "Dark, intense, and unforgettable.", "2026-11-14"}
            }},
        {"Gone with the Wind", "Margaret Mitchell", "1936-06-30", 4.8, "", {
            {"testuser123", 5, "Epic historical fiction, very engaging.", "2026-11-19"}
            }}
    };
}

void MainWindow::displayBooks(const std::vector<BookItem>& books)
{
    ui->bookListWidget->clear();

    for (const auto& book : books) {
        QListWidgetItem *item = new QListWidgetItem(ui->bookListWidget);

        QWidget *rowContainer = new QWidget();
        QVBoxLayout *rowLayout = new QVBoxLayout(rowContainer);
        rowLayout->setContentsMargins(2, 2, 2, 2);
        rowLayout->setSpacing(0);

        //Left btn can be click to read books, right btn can be click to show reviews
        QHBoxLayout *topBar = new QHBoxLayout();
        topBar->setSpacing(4);

        QString displayText = QString("%1  |  Author: %2  |  Date: %3 | Rating: %4 ★")
            .arg(book.title, book.author, book.date)
            .arg(QString::number(book.rating, 'f', 1));

        QPushButton *btn = new QPushButton(displayText);
        btn->setStyleSheet("QPushButton { text-align: left; padding: 6px 10px; }");
        topBar->addWidget(btn, 1);

        QPushButton *reviewToggleBtn = new QPushButton(
            QString("Reviews (%1) ▼").arg(book.reviews.size())
            );
        reviewToggleBtn->setStyleSheet(
            "QPushButton { padding: 6px 10px; background-color: #fff8e7; border: 1px solid #f39c12; border-radius: 3px; color: #d35400; font-weight: bold; }");
        topBar->addWidget(reviewToggleBtn);
        rowLayout->addLayout(topBar);

        // Added functionality of reading a book from main window library
        const QString path = book.path;
        connect(btn, &QPushButton::clicked, this, [path] {
            if (path.isEmpty()) return;   // dummy books have no file
            auto *window = new ReadWindow(path);
            window->setAttribute(Qt::WA_DeleteOnClose);
            window->show();
        });

        // book widget: tos how others comments, rating, and comment box
        QWidget *drawer = new QWidget();
        drawer->setVisible(false);
        drawer->setStyleSheet("background-color: #f9f9f9; border: 1px solid #dcdde1; border-top: none;");
        QVBoxLayout *drawerLayout = new QVBoxLayout(drawer);
        drawerLayout->setContentsMargins(12, 8, 12, 10);
        drawerLayout->setSpacing(6);

        QLabel *othersHeader = new QLabel("<b>Other Users' Ratings & Reviews:</b>");
        drawerLayout->addWidget(othersHeader);

        QLabel *othersContent = new QLabel();
        othersContent->setWordWrap(true);
        if (book.reviews.isEmpty()) {
            othersContent->setText("No reviews yet. Be the first to rate!");
        } else {
            QStringList lines;
            for (const auto& r : book.reviews) {
                int c = qBound(0, r.rating, 5);
                QString stars = QString("★").repeated(c) + QString("☆").repeated(5 - c);
                QString commentStr = r.comment.isEmpty() ? "(Rating only)" : r.comment;
                lines << QString("• <b>%1</b> [%2] (%3): %4").arg(r.username, stars, r.date, commentStr);
            }
            othersContent->setText(lines.join("<br>"));
        }
        drawerLayout->addWidget(othersContent);

        // five stars rating box
        QHBoxLayout *starRow = new QHBoxLayout();
        starRow->addWidget(new QLabel("<b>Your Rating:</b>"));
        StarRatingWidget *starWidget = new StarRatingWidget();
        starRow->addWidget(starWidget);
        starRow->addStretch();
        drawerLayout->addLayout(starRow);

        // comment box
        QTextEdit *commentBox = new QTextEdit();
        commentBox->setPlaceholderText("Write your review here...");
        commentBox->setFixedHeight(55);
        drawerLayout->addWidget(commentBox);

        // submit button
        QHBoxLayout *submitRow = new QHBoxLayout();
        submitRow->addStretch();
        QPushButton *submitBtn = new QPushButton("Submit Review");
        submitBtn->setStyleSheet("background-color: #2980b9; color: white; font-weight: bold; padding: 4px 12px;");
        submitRow->addWidget(submitBtn);
        drawerLayout->addLayout(submitRow);

        rowLayout->addWidget(drawer);

        // unfold/fold widget
        connect(reviewToggleBtn, &QPushButton::clicked, this, [drawer, reviewToggleBtn, rowContainer, item, count = book.reviews.size()]() {
            bool show = !drawer->isVisible();
            drawer->setVisible(show);
            reviewToggleBtn->setText(QString("Reviews (%1) %2").arg(count).arg(show ? "▲" : "▼"));
            rowContainer->adjustSize();
            item->setSizeHint(rowContainer->sizeHint());
        });

        // submit new comments and ratings
        const QString bookTitle = book.title;
        connect(submitBtn, &QPushButton::clicked, this, [this, bookTitle, starWidget, commentBox]() {
            int chosenStars = starWidget->rating();
            if (chosenStars == 0) {
                QMessageBox::warning(this, "Rating Required", "Please click on the stars (1 to 5) to rate.");
                return;
            }
            QString reviewText = commentBox->toPlainText().trimmed();
            QString today = QDateTime::currentDateTime().toString("yyyy-MM-dd");

            for (auto& b : m_allBooks) {
                if (b.title == bookTitle) {
                    b.reviews.append({"User", chosenStars, reviewText, today});
                    double sum = 0;
                    for (const auto& r : b.reviews) sum += r.rating;
                    b.rating = sum / b.reviews.size();
                    break;
                }
            }

            saveLibrary();     // upload json document ratings
            saveAllReviews();  // save reciews
            displayBooks(m_allBooks);
        });

        item->setSizeHint(rowContainer->sizeHint());
        ui->bookListWidget->setItemWidget(item, rowContainer);
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
    else if (index == 1) { // Rating (five stars)
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
    saveLibrary();
    loadAllReviews();
    displayBooks(m_allBooks);
}

QString MainWindow::libraryFilePath() const
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + "/library.json";
}

void MainWindow::saveLibrary() const
{
    QJsonArray arr;
    for (const BookItem &b : m_allBooks)
    {
        if (b.path.isEmpty())
        {
            continue;
        }
        QJsonObject o;
        o["title"] = b.title;
        o["author"] = b.author;
        o["date"] = b.date;
        o["rating"] = b.rating;
        o["path"] = b.path;
        arr.append(o);
    }
    QFile f(libraryFilePath());
    if(f.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        f.write(QJsonDocument(arr).toJson(QJsonDocument::Indented));
    }
}

void MainWindow::loadLibrary()
{
    QFile f(libraryFilePath());
    if(!f.open(QIODevice::ReadOnly))
    {
        return;
    }
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    if(!doc.isArray())
    {
        return;
    }
    for (const QJsonValue &v : doc.array())
    {
        const QJsonObject o = v.toObject();
        BookItem b;
        b.title  = o["title"].toString();
        b.author = o["author"].toString();
        b.date   = o["date"].toString();
        b.rating = o["rating"].toDouble();
        b.path   = o["path"].toString();

        if(!QFileInfo::exists(b.path))
        {
            continue;
        }
        m_allBooks.push_back(b);
    }
}

void MainWindow::saveAllReviews() const
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    QFile f(dir + "/reviews.json");

    QJsonObject root;
    for (const BookItem &b : m_allBooks) {
        QJsonArray arr;
        for (const UserReview &r : b.reviews) {
            QJsonObject obj;
            obj["username"] = r.username;
            obj["rating"] = r.rating;
            obj["comment"] = r.comment;
            obj["date"] = r.date;
            arr.append(obj);
        }
        root[b.title] = arr;
    }

    if (f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        f.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    }
}

void MainWindow::loadAllReviews()
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile f(dir + "/reviews.json");
    if (!f.open(QIODevice::ReadOnly)) return;

    const QJsonObject root = QJsonDocument::fromJson(f.readAll()).object();
    for (BookItem &b : m_allBooks) {
        if (root.contains(b.title)) {
            b.reviews.clear();
            double sum = 0;
            for (const QJsonValue &v : root[b.title].toArray()) {
                QJsonObject obj = v.toObject();
                UserReview r{
                    obj["username"].toString(),
                    obj["rating"].toInt(),
                    obj["comment"].toString(),
                    obj["date"].toString()
                };
                b.reviews.append(r);
                sum += r.rating;
            }
            if (!b.reviews.isEmpty()) {
                b.rating = sum / b.reviews.size();
            }
        }
    }
}