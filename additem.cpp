#include "additem.h"
#include "ui_additem.h"
#include "stock.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <vector>
#include <QMessageBox>
#include <QComboBox>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>


additem::additem(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::additem)
{
    ui->setupUi(this);
    ui->label_quantityError->clear();
}

additem::~additem()
{
    delete ui;
    emit itemAdded();
}



void additem::on_additemButton_clicked()
{
    ui->label_quantityError->clear();

    QString enteredName = ui->lineEdit_name->text().trimmed();
    QString quantityStr = ui->lineEdit_quantity->text().trimmed();
    QString priceStr = ui->lineEdit_price->text().trimmed();
    QString enteredCategory = ui->lineEdit_category->text().trimmed();
    QString enteredSupplier = ui->lineEdit_supplier->text().trimmed();

    if (enteredName.isEmpty() || quantityStr.isEmpty() || priceStr.isEmpty() ||
        enteredCategory.isEmpty() || enteredSupplier.isEmpty()) {
        ui->label_quantityError->setText("Please fill all fields.");
        ui->label_quantityError->setStyleSheet("color: red;");
        return;
    }

    bool quantityOk, priceOk;
    int quantity = quantityStr.toInt(&quantityOk);
    double price = priceStr.toDouble(&priceOk);

    if (!quantityOk || quantity < 0) {
        ui->label_quantityError->setText("Quantity must be positive.");
        ui->label_quantityError->setStyleSheet("color: red;");
        return;
    }
    if (!priceOk || price < 0) {
        ui->label_quantityError->setText("Price must be positive.");
        ui->label_quantityError->setStyleSheet("color: red;");
        return;
    }

    for (const Stock& stock : stocks) {
        if (stock.name == enteredName && stock.supplier == enteredSupplier) {
            QMessageBox::warning(this, "Duplicate Item", "This item from this supplier already exists.");
            return;
        }
    }

    Stock newStock = { enteredName, quantity, price, enteredCategory, enteredSupplier };
    stocks.push_back(newStock);

    QString filePath = "/Users/bassantibrahim/Desktop/InventoryProject/stocks.txt";
    QFile file(filePath);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Stock& stock : stocks) {
            out << stock.name << "," << stock.quantity << "," << stock.price << "," << stock.category << "," << stock.supplier << "\n";
        }
        file.close();
        QMessageBox::information(this, "Item Added", "Item successfully added!");
        emit itemAdded();
        ui->lineEdit_name->clear();
        ui->lineEdit_quantity->clear();
        ui->lineEdit_price->clear();
        ui->lineEdit_category->clear();
        ui->lineEdit_supplier->clear();
        ui->label_quantityError->clear();
    } else {
        QMessageBox::critical(this, "File Error", "Could not open stocks.txt to save item.");
    }
}



void additem::loadStocksFromFile()
{
    stocks.clear();
    QString filePath = "/Users/bassantibrahim/Desktop/InventoryProject/stocks.txt";
    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) {
                QStringList parts = line.split(",");
                if (parts.size() >= 5) {
                    Stock stock;
                    stock.name = parts[0];
                    stock.quantity = parts[1].toInt();
                    stock.price = parts[2].toDouble();
                    stock.category = parts[3];
                    stock.supplier = parts[4];
                    stocks.push_back(stock);
                }
            }
        }
        file.close();
    }
}

