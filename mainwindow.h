#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QMainWindow>
#include <QMessageBox>
// #include <QValidator>
// #include <QRegExpValidator>
#include <QAction>
#include <QFile> /// Para el uso de la base de datos en formato JSON
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDateTime>
#include <QRandomGenerator>

#include <vector>
#include <regex>
#include <algorithm>
#include <queue>

#include "User.h"
#include "productwidget.h"
#include "graph.h"

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

    void on_sortCB_currentIndexChanged(int index);

    void on_searchLE_textChanged(const QString &arg1);

    void addToCart(QString item, int quantity);

private:
    Ui::MainWindow *ui;

    vector<User> users;
    vector<ProductWidget*> products;
    vector<ProductWidget*> deptProducts;

    QAction* openFileAction;
    QFile dbFile;
    QJsonArray usersArray;
    QJsonArray productsArray;
    QJsonArray cart;

    QString currentDept;
    QString currentOrder;
    size_t currentUserIndex;

    Graph<string> graph;

    class myComparison
    {
      bool reverse;
    public:
      myComparison(const bool& revparam=false)
        {reverse=revparam;}
      bool operator() (const pair<string, int>& lhs, const pair<string, int>&rhs) const
      {
        if (reverse) return (lhs.second > rhs.second);
        else return (lhs.second < rhs.second);
      }
    };

    priority_queue< pair<string, int>, vector< pair<string, int> >, myComparison> recommendations;


    enum StackW {LOGIN_SIGNIN, LERMA_INTERFACE};
    enum CategoriesCB {ALL, FOOD_DRINKS, BOOKS,
                       ELECTRONICS, HOME_KITCHEN,
                       SPORTS_OUTDOORS};
    enum OrderCB {DEFAULT, ASCENDING, DESCENDING};

    void enableLoginPB();
    void enableSignInPB();
    void validateUser();

    void saveDB();
    void loadDB();

    void fillDeptProducts();
    void sortDeptProducts();
    void loadProductsWidgets();
    void cleanProductsSA();

    bool findUsrOrMailInVctr();

    void addPurchaseToHistory();

    void createGraph();

    void fillRecommendations();
    void randomRecommendations();
    void loadRecommendationsWidgets();
    void cleanRecommendationsSA();
};
#endif // MAINWINDOW_H
