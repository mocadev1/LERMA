#include "productwidget.h"
#include "ui_productwidget.h"

using namespace std;
ProductWidget::ProductWidget(QString i, QString n, double p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductWidget),
    id(i),
    name(n),
    price(p)
{
    ui->setupUi(this);

    QString path(":/imgs/");
    path += id + ".jpg";
    QPixmap pix(path);

    ui->imgLbl->setPixmap(pix.scaled(200, 200));
    ui->nameLbl->resize(200,200);
    ui->nameLbl->setWordWrap(true);
    ui->nameLbl->setText(name);
    ui->priceLbl->resize(200,200);
    ui->priceLbl->setWordWrap(true);
    ui->priceLbl->setText("$" + QString::number(price));

    cout << "path: " << path.toStdString() + "\n\n";
    cout << "id: " << i.toStdString() << endl;
    cout << "name: " << n.toStdString() << endl;
    cout << "price: " << p << endl;
}

ProductWidget::~ProductWidget()
{
    delete ui;
}

QString ProductWidget::getId() const
{
    return id;
}

void ProductWidget::setId(const QString &value)
{
    id = value;
}

QString ProductWidget::getName() const
{
    return name;
}

void ProductWidget::setName(const QString &value)
{
    name = value;
}

double ProductWidget::getPrice() const
{
    return price;
}

void ProductWidget::setPrice(float value)
{
    price = value;
}
