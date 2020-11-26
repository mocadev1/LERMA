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

/**
 * Enables the addPB in the UI if arg1 > 0
 * @param arg1
 */
void ProductWidget::on_quantitySB_valueChanged(int arg1)
{
    if(arg1 > 0)
    {
        ui->addPB->setEnabled(true);
    }
    else
    {
        ui->addPB->setEnabled(false);
    }
}

/**
 * Here the productWidget emits the SIGNAL
 * that is catched in the MainWindow
 */
void ProductWidget::on_addPB_clicked()
{
    emit addItem(id, ui->quantitySB->value());
    ui->quantitySB->setValue(0);
}
