#include "additem.h"
#include "ui_additem.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <vector>
#include <QMessageBox>
#include <QComboBox>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>
#include "stock.h"

additem::additem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::additem)
{
    ui->setupUi(this);
}

additem::~additem()
{
    delete ui;
}


bool validateQuantity(const int quantity) {
    if (quantity < 0)
        return false;
}

void additem::on_additemButton_clicked()
{
    ui->label_quantityError->clear();

    QString enteredName = ui->lineEdit_name->text();
    QString quantitystr = ui->lineEdit_quantity->text();
    QString pricestr = ui->lineEdit_price->text();
    QString enteredCategory = ui->lineEdit_category->text();
    QString enteredSupplier = ui->lineEdit_supplier->text().trimmed();

    if (enteredName.isEmpty() || quantitystr.isEmpty() || pricestr.isEmpty() ||
        enteredCategory.isEmpty() || enteredSupplier.isEmpty()) {
        ui->label_quantityError->setText("Please fill all fields.");
        ui->label_quantityError->setStyleSheet("color: red;");
        return;
    }

    bool quantityOk, priceOk;
    int quantity = quantitystr.toInt(&quantityOk);
    double price = pricestr.toDouble(&priceOk);

    if (!quantityOk || !validateQuantity(quantity)) {
        ui->label_quantityError->setText("Quantity must be positive.");
        ui->label_quantityError->setStyleSheet("color: red;");
        return;
    }
    if (!priceOk || price < 0) {
        ui->label_quantityError->setText("Price must be positive.");
        ui->label_quantityError->setStyleSheet("color: red;");
        return;
    }

    Stock newStock = { enteredName, quantity, price, enteredCategory, enteredSupplier };
    stocks.push_back(newStock);

    QFile file("stocks.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << enteredName << "," << quantity << "," << price << "," << enteredCategory << "," << enteredSupplier << "\n";
        file.close();
        QMessageBox::information(this, "Item successfully added.","");
        ui->lineEdit_name->clear();
        ui->lineEdit_quantity->clear();
        ui->lineEdit_price->clear();
        ui->lineEdit_category->clear();
        ui->lineEdit_supplier->clear();
    } else {
        QMessageBox::critical(this, "File Error", "Could not open stocks.txt to save item.");
        return;
    }
}




