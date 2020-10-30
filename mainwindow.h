#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include <regex>
#include "User.h"
#include "productwidget.h"

// #include <QValidator>
// #include <QRegExpValidator>

#include <QAction>
#include <QFile> /// Para el uso de la base de datos en formato JSON
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

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

    void openFile();

    void on_categoriesCB_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    vector<User> users;
    vector<ProductWidget*> products;
    QAction* openFileAction;
    QFile dbFile;
    QJsonArray usersArray;
    QJsonArray productsArray;
    QString currentDept;

    enum StackW {LOGIN_SIGNIN, LERMA_INTERFACE};
    enum CategoriesCB {ALL, FOOD_DRINKS, BOOKS,
                       ELECTRONICS, HOME_KITCHEN,
                       SPORTS_OUTDOORS};

    void enableLoginPB();
    void enableSignInPB();
    void validateUser();

    void saveDB();
    void loadDB();

    void loadProductsWidgets();

    bool findUsrOrMailInVctr();

    void cleanProductsSA();

};
#endif // MAINWINDOW_H
