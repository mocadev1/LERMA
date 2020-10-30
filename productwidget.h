#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QString>
#include <QPixmap>
#include <iostream>

namespace Ui {
class ProductWidget;
}

class ProductWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductWidget(QString i="", QString n="", double p=0, QWidget *parent = nullptr);
    ~ProductWidget();

    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    double getPrice() const;
    void setPrice(float value);

private:
    Ui::ProductWidget *ui;

    QString id;
    QString name;
    double price;
};

#endif // PRODUCTWIDGET_H
