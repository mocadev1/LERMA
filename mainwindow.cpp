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
        MainWindow::showMaximized();
        message.setText("Welcome to LERMA " + user);
        ui->viewSW->setCurrentIndex(LERMA_INTERFACE);
        message.exec();
    }

}

void MainWindow::saveDB()
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;
    jsonObj["products"] = productsArray;
    jsonObj["users"] = usersArray; // Creates an JSON object that store a JSON array
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

    usersArray = jsonObj["users"].toArray();

    for (int i(0); i < usersArray.size(); ++i)
    {
        User u;
        QJsonObject obj = usersArray[i].toObject();
        u.setUsername(obj["name"].toString());
        u.setEmail(obj["email"].toString());
        u.setPassword(obj["password"].toString());
        users.push_back(u);
    }

    productsArray = jsonObj["products"].toArray();
    ProductWidget* pw;

    for (int i(0); i < productsArray.size(); ++i)
    {

        QJsonObject obj = productsArray[i].toObject();
        pw = new ProductWidget(obj["id"].toString(),
                              obj["name"].toString(),
                              obj["price"].toDouble(),
                              nullptr);
        products.push_back(pw);
    }

    fillDeptProducts();
    loadProductsWidgets();
}

/* Fills "deptProducts" only with the products that belongs to the
 * "currentDept" selected in the "categoriesCB"
 */
void MainWindow::fillDeptProducts()
{
    deptProducts.clear();

    for (size_t j(0); j < products.size(); ++j) {
        if(products[j]->getId().contains(currentDept)){
            deptProducts.push_back(products[j]);
        }
    }

}

/* Sorts "deptProducts" based on the "currentOrder" selected in "sortCB"
 */
void MainWindow::sortDeptProducts()
{
    if(currentOrder == "ascending"){
        sort(deptProducts.begin(), deptProducts.end(),
             [](const ProductWidget* a, const ProductWidget* b)
                {
                    return a->getPrice() < b->getPrice();
                });
    }
    else if( currentOrder == "descending"){
        sort(deptProducts.begin(), deptProducts.end(),
             [](const ProductWidget* a, const ProductWidget* b)
                {
                    return a->getPrice() > b->getPrice();
                });
    }
    else //default
        fillDeptProducts();

    for (size_t j(0); j < deptProducts.size(); ++j) {
        cout  << "ORDEN[" << j << "] " << deptProducts[j]->getName().toStdString() << endl;
    }
}

void MainWindow::loadProductsWidgets()
{
    cleanProductsSA();

    ProductWidget *product;
    int matchingProducts(0);
    for (size_t j(0); j < deptProducts.size(); ++j) {
        if(deptProducts[j]->getName().toLower().contains(
                                                ui->searchLE->text().toLower())) // This could be an atribute "searchingFor"
        {
            product = new ProductWidget(deptProducts[j]->getId(),
                                        deptProducts[j]->getName(),
                                        deptProducts[j]->getPrice(),
                                        ui->productsSA);
            ui->productsGrid->addWidget(product,
                              matchingProducts/4, matchingProducts%4);
            ++matchingProducts;
        }
    }
}

bool MainWindow::findUsrOrMailInVctr()
{
    vector<User>::iterator it;
    QString newUser = ui->newUserLE->text();
    QString newEmail = ui->emailLE->text();
    it = find_if(users.begin(), users.end(), [&newUser, &newEmail](User u) -> bool
    {
        return u.getUsername() == newUser or u.getEmail() == newEmail;
    }
    );
    return !(it == users.end());
}

void MainWindow::cleanProductsSA()
{
    QLayoutItem* item;
        while((item = ui->productsGrid->takeAt(0)))
        {
            delete item->widget();
            delete item;
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
        if(findUsrOrMailInVctr()){
            message.setText("Either username or email is already being used");
        }
        else
        {
            users.push_back(u);
            message.setText("New user created");

            jsonObj["name"] = u.getUsername();
            jsonObj["email"] = u.getEmail();
            jsonObj["password"] = u.getPassword();
            usersArray.append(jsonObj);
        }
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

void MainWindow::on_categoriesCB_currentIndexChanged(int index)
{
    switch(index){
    case ALL:
        currentDept = "";
        break;
    case FOOD_DRINKS:
        currentDept = "AB";
        break;
    case BOOKS:
        currentDept = "L";
        break;
    case ELECTRONICS:
        currentDept = "E";
        break;
    case HOME_KITCHEN:
        currentDept = "HC";
        break;
    case SPORTS_OUTDOORS:
        currentDept = "D";
        break;
    }

    ui->sortCB->setCurrentIndex(DEFAULT);
    fillDeptProducts();
    ui->searchLE->clear();
    loadProductsWidgets();

}

void MainWindow::on_sortCB_currentIndexChanged(int index)
{
    switch (index) {
    case DEFAULT:
        currentOrder = "default";
        break;
    case ASCENDING:
        currentOrder = "ascending";
        break;
    case DESCENDING:
        currentOrder = "descending";
        break;
    }

    sortDeptProducts();
    loadProductsWidgets();
    cout << "Cambio Sort a [" << index << "]: " << currentOrder.toStdString() << endl;
}

void MainWindow::on_searchLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    loadProductsWidgets();
}
