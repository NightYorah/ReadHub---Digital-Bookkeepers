#include <QtTest>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDateTime>
#include "loginwindow.h"
#include "mainwindow.h"

class ReadHubTest : public QObject
{
    Q_OBJECT

private slots:
    //Test for the login page
    void testLoginSuccessWithDummyCredentials();
    void testLoginFailureWithInvalidCredentials();
    void testSignupSuccessWithNewCredentials();
    void testSignupFailureWithBlankCredentials();
    void testSignupFailureWithExistingCredentials();
    void testLoginSuccessAfterSignup();

    //Test for the mainwindow page
    void testMainWindowInitialization();
};

//Test login with Dummy Credentials successful
void ReadHubTest::testLoginSuccessWithDummyCredentials()
{
    LoginWindow loginWin;
    loginWin.show();

    QList<QLineEdit*> editors = loginWin.findChildren<QLineEdit*>();
    QList<QPushButton*> buttons = loginWin.findChildren<QPushButton*>();

    if (editors.size() >= 4 && !buttons.isEmpty()) {
        // Simulate the input of Dummy Credentials with "testuser123" and "password"
        editors[0]->clear();
        editors[1]->clear();
        QTest::keyClicks(editors[0], "a");
        QTest::keyClicks(editors[1], "1");

        //Simulate click the login button
        QTest::mouseClick(buttons[0], Qt::LeftButton);

        // Check window state or success message since onLoginClicked lacks return statement
        QVERIFY2(!loginWin.isVisible(), "LoginWindow should be closed upon successful login.");
    } else {
        QFAIL("Could not find input fields or buttons.");
    }
}

// Test login with invalid credentials failure
void ReadHubTest::testLoginFailureWithInvalidCredentials()
{
    LoginWindow loginWin;
    loginWin.show();

    QList<QLineEdit*> editors = loginWin.findChildren<QLineEdit*>();
    QList<QPushButton*> buttons = loginWin.findChildren<QPushButton*>();

    if (editors.size() >= 4 && !buttons.isEmpty()) {
        editors[0]->clear();
        editors[1]->clear();
        QTest::keyClicks(editors[0], "invalid_user");
        QTest::keyClicks(editors[1], "wrong_password");
        QTest::mouseClick(buttons[0], Qt::LeftButton);

        // Check error label
        bool hasErrorMessage = false;
        for (QLabel *label : loginWin.findChildren<QLabel*>()) {
            if (label->text().contains("Invalid username or password.")) {
                hasErrorMessage = true;
                break;
            }
        }
        QVERIFY2(hasErrorMessage, "Expected 'Invalid username or password.' error label, but none was displayed.");
    } else {
        QFAIL("Could not find input fields or login button.");
    }
}

// Test sign up with new credentials success
void ReadHubTest::testSignupSuccessWithNewCredentials()
{
    LoginWindow loginWin;
    loginWin.show();

    QList<QLineEdit*> editors = loginWin.findChildren<QLineEdit*>();
    QList<QPushButton*> buttons = loginWin.findChildren<QPushButton*>();

    // editors[2] is the new user name，editors[3] is the new password，buttons[1] is the sign up button
    if (editors.size() >= 4 && buttons.size() >= 2) {
        QString uniqueUser = "user_" + QString::number(QDateTime::currentMSecsSinceEpoch());
        editors[2]->clear();
        editors[3]->clear();
        QTest::keyClicks(editors[2], uniqueUser);
        QTest::keyClicks(editors[3], "password123");

        QTest::mouseClick(buttons[1], Qt::LeftButton);

        bool hasSuccessMessage = false;
        for (QLabel *label : loginWin.findChildren<QLabel*>()) {
            if (label->text().contains("New Account Created!")) {
                hasSuccessMessage = true;
                break;
            }
        }
        QVERIFY2(hasSuccessMessage, "Expected 'New Account Created!' label after successful signup.");
    } else {
        QFAIL("Could not find input fields or signup button.");
    }
}

// Test sign up with blank credentials failure
void ReadHubTest::testSignupFailureWithBlankCredentials()
{
    LoginWindow loginWin;
    loginWin.show();

    QList<QLineEdit*> editors = loginWin.findChildren<QLineEdit*>();
    QList<QPushButton*> buttons = loginWin.findChildren<QPushButton*>();

    if (editors.size() >= 4 && buttons.size() >= 2) {
        editors[2]->clear();
        editors[3]->clear();
        QTest::keyClicks(editors[3], "password123");

        QTest::mouseClick(buttons[1], Qt::LeftButton);

        bool hasErrorMessage = false;
        for (QLabel *label : loginWin.findChildren<QLabel*>()) {
            if (label->text().contains("Username unavailable")) {
                hasErrorMessage = true;
                break;
            }
        }
        QVERIFY2(hasErrorMessage, "Expected 'Username unavailable' label when signing up with blank username.");
    } else {
        QFAIL("Could not find input fields or buttons.");
    }
}

// Test sign up with existing credentials failure
void ReadHubTest::testSignupFailureWithExistingCredentials()
{
    LoginWindow loginWin;
    loginWin.show();

    QList<QLineEdit*> editors = loginWin.findChildren<QLineEdit*>();
    QList<QPushButton*> buttons = loginWin.findChildren<QPushButton*>();

    if (editors.size() >= 4 && buttons.size() >= 2) {
        editors[2]->clear();
        editors[3]->clear();
        QTest::keyClicks(editors[2], "testuser123"); //test the existing dummy credential account
        QTest::keyClicks(editors[3], "password123"); //the existing dummy credential password

        QTest::mouseClick(buttons[1], Qt::LeftButton);

        bool hasErrorMessage = false;
        for (QLabel *label : loginWin.findChildren<QLabel*>()) {
            if (label->text().contains("Username unavailable")) {
                hasErrorMessage = true;
                break;
            }
        }
        QVERIFY2(hasErrorMessage, "Expected 'Username unavailable' label when signing up with an existing username.");
    } else {
        QFAIL("Could not find input fields or buttons.");
    }
}

// Test login with an account after sign up success
void ReadHubTest::testLoginSuccessAfterSignup()
{
    LoginWindow loginWin;
    loginWin.show();

    QList<QLineEdit*> editors = loginWin.findChildren<QLineEdit*>();
    QList<QPushButton*> buttons = loginWin.findChildren<QPushButton*>();

    if (editors.size() >= 4 && buttons.size() >= 2) {
        QString dynamicUser = "user_" + QString::number(QDateTime::currentMSecsSinceEpoch());
        QString dynamicPass = "pass_123456";

        editors[2]->clear();
        editors[3]->clear();
        QTest::keyClicks(editors[2], dynamicUser); //Setting up a new user name
        QTest::keyClicks(editors[3], dynamicPass); //Setting up a new password
        QTest::mouseClick(buttons[1], Qt::LeftButton);

        editors[0]->clear();
        editors[1]->clear();
        QTest::keyClicks(editors[0], dynamicUser); //Login with the new user name
        QTest::keyClicks(editors[1], dynamicPass); //Login with the new password
        QTest::mouseClick(buttons[0], Qt::LeftButton);

        //Check the success of login
        QVERIFY2(!loginWin.isVisible(), "Newly registered user failed to log in or window was not closed.");
    } else {
        QFAIL("Could not find input fields or buttons.");
    }
}

// Test MainWindow initialize
void ReadHubTest::testMainWindowInitialization()
{
    MainWindow *w = new MainWindow();
    QVERIFY2(w != nullptr, "MainWindow failed to initialize.");
    delete w;
}

QTEST_MAIN(ReadHubTest)
#include "tst_readhubtest.moc"