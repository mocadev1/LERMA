#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QRegExp regexp();
    //QValidator* validator = new QRegExpValidator(regex, this); /// This is the "parent" of this thing
    //ui->emailLE->setValidator(validator);

    openFileAction = new QAction("&Open Database",  this);
    /* In the UI(front) will emitting a signal and in the back will be a method
     * will be "listening" to do somenthing.
     *
     * connect(who'sEmtting, signalKind, who'sListening, whatsGonnaDo);
    */
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    ui->menubar->addMenu("&File")->addAction(openFileAction);
}

MainWindow::~MainWindow()
{
    saveDB();
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
        message.setText("Invalid Credentials");
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

void MainWindow::saveDB()
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;

    jsonObj["users"] = dbArray;
    jsonDoc = QJsonDocument(jsonObj);

    dbFile.open(QIODevice::WriteOnly);
    dbFile.write(jsonDoc.toJson());
    dbFile.close();

}

void MainWindow::loadDB()
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;
    QByteArray data;

    dbFile.open(QIODevice::ReadOnly);
    data = dbFile.readAll();
    dbFile.close();

    jsonDoc = QJsonDocument::fromJson(data);
    jsonObj = jsonDoc.object();
    dbArray = jsonObj["users"].toArray();

    for (int i(0); i < dbArray.size(); ++i)
    {
        User u;
        QJsonObject obj = dbArray[i].toObject();
        u.setUsername(obj["name"].toString());
        u.setEmail(obj["email"].toString());
        u.setPassword(obj["password"].toString());
        users.push_back(u);
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
    QJsonObject jsonObj;
    QMessageBox message;
    User u;
    // The last part of the regex ("?:\\.") is a subpattern
    regex emailPatron("^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}-]+@[a-zA-Z0-9-]+(?:\\.[a-zA-Z0-9-]+)+$");

    u.setUsername(ui->newUserLE->text());
    u.setEmail(ui->emailLE->text());
    u.setPassword(ui->newPasswordLE->text());


    if(regex_match(u.getEmail().toStdString(), emailPatron))
    {
        users.push_back(u);

        message.setText("New user created");
    }
    else
    {
        message.setText("Invalid email, please try a real one");
        message.setIcon(QMessageBox::Warning);
    }

    message.exec();

    ui->newUserLE->clear();
    ui->emailLE->clear();
    ui->newPasswordLE->clear();

    jsonObj["name"] = u.getUsername();
    jsonObj["email"] = u.getEmail();
    jsonObj["password"] = u.getPassword();
    dbArray.append(jsonObj);
}

void MainWindow::on_loginPB_clicked()
{
    validateUser();
    ui->usernameLE->clear();
    ui->passwordLE->clear();
}

void MainWindow::openFile()
{
    QString name;
    name = QFileDialog::getOpenFileName(this,
                                        "Select Database",
                                        "",
                                        "JSON files (*.json)");
    if(name.length() > 0)
    {
        dbFile.setFileName(name);
        ui->loginGB->setEnabled(true);
        ui->signInGB->setEnabled(true);
        loadDB();
    }
}
