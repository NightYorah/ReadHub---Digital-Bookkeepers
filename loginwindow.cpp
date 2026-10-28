#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    loadEmptyCredential();
    newAccountCredential = {"", ""}; //set the new account credential as empty
    loadDummyCredentials();

    // signal connections
    /// onUsernameEntered called on finishing edit of usernameLineEdit text
    connect(ui->loginUsernameLineEdit, &QLineEdit::textEdited, this, &LoginWindow::onUsernameEntered);
    /// onPassowrdEntered called on finishing edit of passwordLineEdit text
    connect(ui->loginPasswordLineEdit, &QLineEdit::textEdited, this, &LoginWindow::onPasswordEntered);
    /// onLoginClicked called on clicking login button
    connect(ui->loginPushButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    /// onUsernameEntered called on finishing edit of usernameLineEdit text
    connect(ui->signupUsernameLineEdit, &QLineEdit::textEdited, this, &LoginWindow::onNewUsernameEntered);
    /// onUsernameEntered called on finishing edit of usernameLineEdit text
    connect(ui->signupPasswordLineEdit, &QLineEdit::textEdited, this, &LoginWindow::onNewPasswordEntered);
    /// onSignupClicked called on clicking signup button
    connect(ui->signupPushButton, &QPushButton::clicked, this, &LoginWindow::onSignupClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::loadEmptyCredential()
{
    loginCredential = {"", ""};
    newAccountCredential = {"", ""}; //set the new account credential as empty
}

void LoginWindow::loadDummyCredentials()
{
    dummyCredentials = {{"testuser123", "password"},
                        {"veryREALadmin1", "123765890"},
                        {"H4CK3RM4N","KeHkb#_Dnv2*09j9K2Q`:"},
                        {"a", "1"}};
}

void LoginWindow::clearInfoLabels()
{
    ui->loginFailLabel->clear();
    ui->signupFailLabel->clear();
}

void LoginWindow::onUsernameEntered(const QString &text)
{
    loginCredential.username = text;
}

void LoginWindow::onPasswordEntered(const QString &text)
{
    loginCredential.password = text;
}

void LoginWindow::onLoginClicked()
{
    // succeed if loginCredential matches existing credential
    for (const auto &credential : dummyCredentials) {
        if (loginCredential.username == credential.username
            && loginCredential.password == credential.password)
        {
            loginSuccess();
        }
    }
    loginFail();
    // TODO: MAKE WORK FOR NON-DUMMY VALUES
}

void LoginWindow::loginFail()
{
    clearInfoLabels();
    ui->loginFailLabel->setText("<font color='red'>Invalid username or password.</font>");
}

void LoginWindow::loginSuccess()
{
    clearInfoLabels();;
    newMainWindow = new MainWindow();
    newMainWindow->show();
    this->close();
    // TODO: MAKE WHO SIGNS IN ACTUALLY AFFECT VIEW OF CONTENT ON MAIN PAGE
}

void LoginWindow::onNewUsernameEntered(const QString &text)
{
    newAccountCredential.username = text;
}

void LoginWindow::onNewPasswordEntered(const QString &text)
{
    newAccountCredential.password = text;
}

void LoginWindow::onSignupClicked()
{
    // get the input from the editor
    newAccountCredential.username = ui->signupUsernameLineEdit->text();
    newAccountCredential.password = ui->signupPasswordLineEdit->text();

    // fail if username or password are blank
    if (!newAccountCredential.username.isEmpty() && !newAccountCredential.password.isEmpty())
    {
        // fail if username matches exiswting credential
        for (const auto &credential : dummyCredentials) {
            if (newAccountCredential.username == credential.username)
            {
                signupFail();
                return;
            }
        }
        signupSuccess();
        return;
    }
    signupFail();
    // TODO: MAKE WORK FOR NON-DUMMY VALUES
}

void LoginWindow::signupFail()
{
    clearInfoLabels();
    ui->signupFailLabel->setText("<font color='red'>Username unavailable</font>");
}

void LoginWindow::signupSuccess()
{
    clearInfoLabels();
    ui->signupFailLabel->setText("<font color='green'>New Account Created!</font>");
    newAccountCredential = {newAccountCredential.username, newAccountCredential.password};
    dummyCredentials.push_back(newAccountCredential);
    // TODO: MAKE PERMANENT STORAGE FOR CREDENTIALS
}
