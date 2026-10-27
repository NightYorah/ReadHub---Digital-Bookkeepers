/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *loginTitleLabel;
    QLabel *usernameLabel;
    QLineEdit *loginUsernameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *loginPasswordLineEdit;
    QLabel *loginFailLabel;
    QPushButton *loginPushButton;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QLabel *SignupTitleLabel;
    QLabel *signupUsernameLabel;
    QLineEdit *signupUsernameLineEdit;
    QLabel *signupPasswordLabel;
    QLineEdit *signupPasswordLineEdit;
    QLabel *signupFailLabel;
    QPushButton *signupPushButton;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(800, 600);
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        loginTitleLabel = new QLabel(centralwidget);
        loginTitleLabel->setObjectName("loginTitleLabel");
        loginTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(loginTitleLabel);

        usernameLabel = new QLabel(centralwidget);
        usernameLabel->setObjectName("usernameLabel");
        usernameLabel->setMaximumSize(QSize(16777215, 32));
        usernameLabel->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout->addWidget(usernameLabel);

        loginUsernameLineEdit = new QLineEdit(centralwidget);
        loginUsernameLineEdit->setObjectName("loginUsernameLineEdit");

        verticalLayout->addWidget(loginUsernameLineEdit);

        passwordLabel = new QLabel(centralwidget);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setMaximumSize(QSize(16777215, 32));
        passwordLabel->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout->addWidget(passwordLabel);

        loginPasswordLineEdit = new QLineEdit(centralwidget);
        loginPasswordLineEdit->setObjectName("loginPasswordLineEdit");
        loginPasswordLineEdit->setMaxLength(32767);
        loginPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(loginPasswordLineEdit);

        loginFailLabel = new QLabel(centralwidget);
        loginFailLabel->setObjectName("loginFailLabel");
        loginFailLabel->setMaximumSize(QSize(16777215, 32));
        loginFailLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(loginFailLabel);

        loginPushButton = new QPushButton(centralwidget);
        loginPushButton->setObjectName("loginPushButton");
        loginPushButton->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(loginPushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        SignupTitleLabel = new QLabel(centralwidget);
        SignupTitleLabel->setObjectName("SignupTitleLabel");
        SignupTitleLabel->setMaximumSize(QSize(16777215, 32));
        SignupTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(SignupTitleLabel);

        signupUsernameLabel = new QLabel(centralwidget);
        signupUsernameLabel->setObjectName("signupUsernameLabel");
        signupUsernameLabel->setMaximumSize(QSize(16777215, 32));

        verticalLayout_3->addWidget(signupUsernameLabel);

        signupUsernameLineEdit = new QLineEdit(centralwidget);
        signupUsernameLineEdit->setObjectName("signupUsernameLineEdit");

        verticalLayout_3->addWidget(signupUsernameLineEdit);

        signupPasswordLabel = new QLabel(centralwidget);
        signupPasswordLabel->setObjectName("signupPasswordLabel");
        signupPasswordLabel->setMaximumSize(QSize(16777215, 32));

        verticalLayout_3->addWidget(signupPasswordLabel);

        signupPasswordLineEdit = new QLineEdit(centralwidget);
        signupPasswordLineEdit->setObjectName("signupPasswordLineEdit");
        signupPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout_3->addWidget(signupPasswordLineEdit);

        signupFailLabel = new QLabel(centralwidget);
        signupFailLabel->setObjectName("signupFailLabel");
        signupFailLabel->setMaximumSize(QSize(16777215, 32));

        verticalLayout_3->addWidget(signupFailLabel);

        signupPushButton = new QPushButton(centralwidget);
        signupPushButton->setObjectName("signupPushButton");
        signupPushButton->setMaximumSize(QSize(200, 16777215));

        verticalLayout_3->addWidget(signupPushButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout_3);

        LoginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        LoginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName("statusbar");
        LoginWindow->setStatusBar(statusbar);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "MainWindow", nullptr));
        loginTitleLabel->setText(QCoreApplication::translate("LoginWindow", "LOG IN", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginWindow", "Username:", nullptr));
        loginUsernameLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter Username", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginWindow", "Password:", nullptr));
        loginPasswordLineEdit->setInputMask(QString());
        loginPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter Password", nullptr));
        loginFailLabel->setText(QString());
        loginPushButton->setText(QCoreApplication::translate("LoginWindow", "Log In", nullptr));
        SignupTitleLabel->setText(QCoreApplication::translate("LoginWindow", "SIGN UP", nullptr));
        signupUsernameLabel->setText(QCoreApplication::translate("LoginWindow", "New Username:", nullptr));
        signupUsernameLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter New Account Username", nullptr));
        signupPasswordLabel->setText(QCoreApplication::translate("LoginWindow", "New Password:", nullptr));
        signupPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter New Account Password", nullptr));
        signupFailLabel->setText(QString());
        signupPushButton->setText(QCoreApplication::translate("LoginWindow", "No Account? Sign Up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
