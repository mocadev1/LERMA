#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableLoginPB()
{
    if (ui->usernameLE->text().length() > 0 and
            ui->passwordLE->text().length() > 0)
    {
        ui->loginPB->setEnabled(true);
    }
    else
    {
        ui->loginPB->setEnabled(false);
    }
}

void MainWindow::enableSignInPB()
{
    if(ui->newUserLE->text().length() > 0 and
            ui->emailLE->text().length() > 0 and
            ui->newPasswordLE->text().length() > 0)
    {
        ui->signInPB->setEnabled(true);
    }
    else
    {
        ui->signInPB->setEnabled(false);
    }
}

void MainWindow::validateUser()
{
    QMessageBox message;
    vector<User>::iterator it;
    QString user = ui->usernameLE->text();
    QString password = ui->passwordLE->text();
    // A lambda function that returns true if finds a username within a vector
    it = find_if(users.begin(), users.end(), [&user, &password](User u) -> bool
    {
        return u.getUsername() == user and u.getPassword() == password;
    }
    );

    if(it == users.end())
    {
        message.setText("Invalida Credentials");
        message.setIcon(QMessageBox::Warning);
        message.exec();
    }
    else
    {
        message.setText("Welcome to LERMA " + user);
        ui->viewSW->setCurrentIndex(LERMA_INTERFACE);
        message.exec();
    }
}

void MainWindow::on_usernameLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableLoginPB();
}

void MainWindow::on_passwordLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableLoginPB();
}

void MainWindow::on_newUserLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSignInPB();
}

void MainWindow::on_emailLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSignInPB();
}

void MainWindow::on_newPasswordLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSignInPB();
}

void MainWindow::on_signInPB_clicked()
{
    QMessageBox message;
    User u;

    u.setUsername(ui->newUserLE->text());
    u.setEmail(ui->emailLE->text());
    u.setPassword(ui->newPasswordLE->text());

    users.push_back(u);

    message.setText("New user created");
    message.exec();

    ui->newUserLE->clear();
    ui->emailLE->clear();
    ui->newPasswordLE->clear();
}

void MainWindow::on_loginPB_clicked()
{
    validateUser();
    ui->usernameLE->clear();
    ui->passwordLE->clear();
}
