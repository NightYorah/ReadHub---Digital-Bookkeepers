/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchLineEdit;
    QComboBox *sortComboBox;
    QPushButton *Switch2Upload;
    QPushButton *pushButton;
    QListWidget *bookListWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");

        verticalLayout->addLayout(horizontalLayout);

        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setLocale(QLocale(QLocale::English, QLocale::AmericanSamoa));

        verticalLayout->addWidget(searchLineEdit);

        sortComboBox = new QComboBox(centralwidget);
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->setObjectName("sortComboBox");
        sortComboBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        verticalLayout->addWidget(sortComboBox);

        Switch2Upload = new QPushButton(centralwidget);
        Switch2Upload->setObjectName("Switch2Upload");

        verticalLayout->addWidget(Switch2Upload);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        bookListWidget = new QListWidget(centralwidget);
        bookListWidget->setObjectName("bookListWidget");
        bookListWidget->setLocale(QLocale(QLocale::English, QLocale::AmericanSamoa));

        verticalLayout->addWidget(bookListWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search books by title", nullptr));
        sortComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Title(A-Z)", nullptr));
        sortComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Rating", nullptr));

        Switch2Upload->setText(QCoreApplication::translate("MainWindow", "Upload PDF", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
