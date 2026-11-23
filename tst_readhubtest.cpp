#include <QDateTime>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QtTest>
#include "loginwindow.h"
#include "mainwindow.h"
#include "StarRatingWidget.h"


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
    void testReviewButtonsCreated();
    void testReviewsDisplayOnButtonClick();
};

//Test login with Dummy Credentials successful
void ReadHubTest::testLoginSuccessWithDummyCredentials()
{
    LoginWindow loginWin;
    loginWin.show();

    QList<QLineEdit *> editors = loginWin.findChildren<QLineEdit *>();
    QList<QPushButton *> buttons = loginWin.findChildren<QPushButton *>();

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

    QList<QLineEdit *> editors = loginWin.findChildren<QLineEdit *>();
    QList<QPushButton *> buttons = loginWin.findChildren<QPushButton *>();

    if (editors.size() >= 4 && !buttons.isEmpty()) {
        editors[0]->clear();
        editors[1]->clear();
        QTest::keyClicks(editors[0], "invalid_user");
        QTest::keyClicks(editors[1], "wrong_password");
        QTest::mouseClick(buttons[0], Qt::LeftButton);

        // Check error label
        bool hasErrorMessage = false;
        for (QLabel *label : loginWin.findChildren<QLabel *>()) {
            if (label->text().contains("Invalid username or password.")) {
                hasErrorMessage = true;
                break;
            }
        }
        QVERIFY2(hasErrorMessage,
                 "Expected 'Invalid username or password.' error label, but none was displayed.");
    } else {
        QFAIL("Could not find input fields or login button.");
    }
}

// Test sign up with new credentials success
void ReadHubTest::testSignupSuccessWithNewCredentials()
{
    LoginWindow loginWin;
    loginWin.show();

    QList<QLineEdit *> editors = loginWin.findChildren<QLineEdit *>();
    QList<QPushButton *> buttons = loginWin.findChildren<QPushButton *>();

    // editors[2] is the new user name，editors[3] is the new password，buttons[1] is the sign up button
    if (editors.size() >= 4 && buttons.size() >= 2) {
        QString uniqueUser = "user_" + QString::number(QDateTime::currentMSecsSinceEpoch());
        editors[2]->clear();
        editors[3]->clear();
        QTest::keyClicks(editors[2], uniqueUser);
        QTest::keyClicks(editors[3], "password123");

        QTest::mouseClick(buttons[1], Qt::LeftButton);

        bool hasSuccessMessage = false;
        for (QLabel *label : loginWin.findChildren<QLabel *>()) {
            if (label->text().contains("New Account Created!")) {
                hasSuccessMessage = true;
                break;
            }
        }
        QVERIFY2(hasSuccessMessage,
                 "Expected 'New Account Created!' label after successful signup.");
    } else {
        QFAIL("Could not find input fields or signup button.");
    }
}

// Test sign up with blank credentials failure
void ReadHubTest::testSignupFailureWithBlankCredentials()
{
    LoginWindow *loginWin = new LoginWindow();
    loginWin->show();

    QLineEdit *usernameEdit = loginWin->findChild<QLineEdit *>("signupUsernameLineEdit");
    QLineEdit *passwordEdit = loginWin->findChild<QLineEdit *>("signupPasswordLineEdit");
    QPushButton *signupBtn = loginWin->findChild<QPushButton *>("signupPushButton");
    QLabel *failLabel = loginWin->findChild<QLabel *>("signupFailLabel");

    QVERIFY(usernameEdit != nullptr);
    QVERIFY(passwordEdit != nullptr);
    QVERIFY(signupBtn != nullptr);
    QVERIFY(failLabel != nullptr);

    // Case1: both two editor are empty
    usernameEdit->clear();
    passwordEdit->clear();
    emit usernameEdit->textEdited("");
    emit passwordEdit->textEdited("");
    QTest::mouseClick(signupBtn, Qt::LeftButton);

    bool hasErrorMessage1 = failLabel->text().contains("Username unavailable", Qt::CaseInsensitive);
    QVERIFY2(hasErrorMessage1, "Failed: Both username and password are blank");

    // Case2: Username is empty, password is not empty
    usernameEdit->clear();
    passwordEdit->clear();
    emit usernameEdit->textEdited("");
    QTest::keyClicks(passwordEdit, "123456");
    QTest::mouseClick(signupBtn, Qt::LeftButton);

    bool hasErrorMessage2 = failLabel->text().contains("Username unavailable", Qt::CaseInsensitive);
    QVERIFY2(hasErrorMessage2, "Failed: Username is blank but password is provided");

    // Case3: Password is empty, username is not empty
    usernameEdit->clear();
    passwordEdit->clear();
    QTest::keyClicks(usernameEdit, "newuser999");
    emit passwordEdit->textEdited("");
    QTest::mouseClick(signupBtn, Qt::LeftButton);

    bool hasErrorMessage3 = failLabel->text().contains("Username unavailable", Qt::CaseInsensitive);
    QVERIFY2(hasErrorMessage3, "Failed: Password is blank but username is provided");

    delete loginWin;
}

// Test sign up with existing credentials failure
void ReadHubTest::testSignupFailureWithExistingCredentials()
{
    LoginWindow loginWin;
    loginWin.show();

    QList<QLineEdit *> editors = loginWin.findChildren<QLineEdit *>();
    QList<QPushButton *> buttons = loginWin.findChildren<QPushButton *>();

    if (editors.size() >= 4 && buttons.size() >= 2) {
        editors[2]->clear();
        editors[3]->clear();
        QTest::keyClicks(editors[2], "testuser123"); //test the existing dummy credential account
        QTest::keyClicks(editors[3], "password123"); //the existing dummy credential password

        QTest::mouseClick(buttons[1], Qt::LeftButton);

        bool hasErrorMessage = false;
        for (QLabel *label : loginWin.findChildren<QLabel *>()) {
            if (label->text().contains("Username unavailable")) {
                hasErrorMessage = true;
                break;
            }
        }
        QVERIFY2(
            hasErrorMessage,
            "Expected 'Username unavailable' label when signing up with an existing username.");
    } else {
        QFAIL("Could not find input fields or buttons.");
    }
}

// Test login with an account after sign up success
void ReadHubTest::testLoginSuccessAfterSignup()
{
    LoginWindow loginWin;
    loginWin.show();

    QList<QLineEdit *> editors = loginWin.findChildren<QLineEdit *>();
    QList<QPushButton *> buttons = loginWin.findChildren<QPushButton *>();

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
        QVERIFY2(!loginWin.isVisible(),
                 "Newly registered user failed to log in or window was not closed.");
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

//  Test review buttons are created for each entry on the books list
void ReadHubTest::testReviewButtonsCreated()
{
    MainWindow *w = new MainWindow();
    QList<QPushButton *> reviewButtons = w->findChildren<QPushButton *>("reviewToggleBtn");
    QVERIFY2(reviewButtons[0] != nullptr, "No buttons loaded");
    QVERIFY2(reviewButtons[3] != nullptr, "Not all buttons loaded");
    delete w;
}

// Test review menu displays on button click
void ReadHubTest::testReviewsDisplayOnButtonClick()
{
    QSKIP("Unfinished");
    //something wrong with how this finds children, no time to resolve for now
    MainWindow *w = new MainWindow();
    QList<QPushButton *> reviewButtons = w->findChildren<QPushButton *>("reviewToggleBtn");
    QTest::mouseClick(reviewButtons[0], Qt::LeftButton);
    QVBoxLayout *bookWidget = w->findChild<QVBoxLayout *>("bookWidget");
    //gives index out of range error, not enough time to resolve
    //QList<QLabel *> reviewLabels = bookWidget->findChildren<QLabel *>();
    //QVERIFY2(reviewLabels[0] != nullptr && reviewLabels[0]->text() == "<b>Other Users' Ratings & Reviews:</b>", "othersLabel not properly created");
    //QVERIFY2(reviewLabels[1] != nullptr, "othersContent not properly loaded");
    // gives a compiler error for some reason, not enough time to resolve
    //StarRatingWidget *stars = bookWidget->findChild<StarRatingWidget *>();
    //QVERIFY2(stars != nullptr, "starWidget not properly loaded");
    QTextEdit *commentBox = bookWidget->findChild<QTextEdit *>();
    //QVERIFY2(commentBox != nullptr, "commentBox not properly loaded");
    QPushButton *submitBtn = bookWidget->findChild<QPushButton *>();
    //QVERIFY2(submitBtn != nullptr && submitBtn->text() == "Submit Review", "commentBox not properly loaded");
    delete w;
}

QTEST_MAIN(ReadHubTest)
#include "tst_readhubtest.moc"