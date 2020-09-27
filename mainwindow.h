#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include <regex>
#include "User.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_usernameLE_textChanged(const QString &arg1);

    void on_passwordLE_textChanged(const QString &arg1);

    void on_newUserLE_textChanged(const QString &arg1);

    void on_emailLE_textChanged(const QString &arg1);

    void on_newPasswordLE_textChanged(const QString &arg1);

    void on_signInPB_clicked();

    void on_loginPB_clicked();

private:
    Ui::MainWindow *ui;

    vector<User> users;
    enum StackW {LOGIN_SIGNIN, LERMA_INTERFACE};

    void enableLoginPB();
    void enableSignInPB();
    void validateUser();


};
#endif // MAINWINDOW_H
