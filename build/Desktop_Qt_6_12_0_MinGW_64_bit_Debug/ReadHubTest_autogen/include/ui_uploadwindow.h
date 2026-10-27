/********************************************************************************
** Form generated from reading UI file 'uploadwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADWINDOW_H
#define UI_UPLOADWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UploadWindow
{
public:
    QWidget *centralwidget;
    QPushButton *Upload_Button;
    QLabel *File_Path;
    QPushButton *Quick_PDF;
    QPushButton *Back2Main;

    void setupUi(QMainWindow *UploadWindow)
    {
        if (UploadWindow->objectName().isEmpty())
            UploadWindow->setObjectName("UploadWindow");
        UploadWindow->resize(800, 600);
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI Symbol")});
        font.setPointSize(14);
        UploadWindow->setFont(font);
        centralwidget = new QWidget(UploadWindow);
        centralwidget->setObjectName("centralwidget");
        Upload_Button = new QPushButton(centralwidget);
        Upload_Button->setObjectName("Upload_Button");
        Upload_Button->setGeometry(QRect(260, 160, 131, 41));
        File_Path = new QLabel(centralwidget);
        File_Path->setObjectName("File_Path");
        File_Path->setGeometry(QRect(200, 220, 311, 41));
        Quick_PDF = new QPushButton(centralwidget);
        Quick_PDF->setObjectName("Quick_PDF");
        Quick_PDF->setGeometry(QRect(210, 290, 111, 41));
        Back2Main = new QPushButton(centralwidget);
        Back2Main->setObjectName("Back2Main");
        Back2Main->setGeometry(QRect(360, 290, 121, 41));
        UploadWindow->setCentralWidget(centralwidget);

        retranslateUi(UploadWindow);

        QMetaObject::connectSlotsByName(UploadWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UploadWindow)
    {
        UploadWindow->setWindowTitle(QCoreApplication::translate("UploadWindow", "UploadWindow", nullptr));
#if QT_CONFIG(whatsthis)
        Upload_Button->setWhatsThis(QCoreApplication::translate("UploadWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        Upload_Button->setText(QCoreApplication::translate("UploadWindow", "Choose File...", nullptr));
#if QT_CONFIG(whatsthis)
        File_Path->setWhatsThis(QCoreApplication::translate("UploadWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        File_Path->setText(QCoreApplication::translate("UploadWindow", "File_Path", nullptr));
        Quick_PDF->setText(QCoreApplication::translate("UploadWindow", "Open PDF", nullptr));
        Back2Main->setText(QCoreApplication::translate("UploadWindow", "Main Library", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UploadWindow: public Ui_UploadWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADWINDOW_H
