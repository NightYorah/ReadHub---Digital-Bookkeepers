#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "mainwindow.h"

struct Credential
{
    QString username;
    QString password;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onUsernameEntered(const QString &text);
    void onPasswordEntered(const QString &text);
    void onLoginClicked();
    void onNewUsernameEntered(const QString &text);
    void onNewPasswordEntered(const QString &text);
    void onSignupClicked();

private:
    Ui::LoginWindow *ui;
    Credential loginCredential;
    Credential newAccountCredential;
    std::vector<Credential> dummyCredentials;
    MainWindow *newMainWindow;

    void loadEmptyCredential();
    void loadDummyCredentials();
    void loginFail();
    void loginSuccess();
    void signupFail();
    void signupSuccess();
    void clearInfoLabels();
};

#endif // LOGINWINDOW_H
