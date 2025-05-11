#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "additem.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>

ManagerWindow::ManagerWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    loadStocksFromFile();
    refreshStockList();
    additem = new class additem(this);
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
       delete additem;
}

void ManagerWindow::on_pushButton_additem_clicked()
{
    additem->show();
    connect(additem, &additem::itemAdded, this, [this]() {
        loadStocksFromFile();
        refreshStockList();
    });
    additem->setAttribute(Qt::WA_DeleteOnClose);
    additem->show();
}

void ManagerWindow::loadStocksFromFile()
{
    stocks.clear();
    QString filePath = "../../stocks.txt";
    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                QStringList parts = line.split(",");
                if (parts.size() >= 5) {
                    QString name = parts[0];
                    int quantity = parts[1].toInt();
                    double price = parts[2].toDouble();
                    QString category = parts[3];
                    QString supplier = parts[4];
                    stocks.emplace_back(name, quantity, price, category, supplier);
                }
            }
        }
        file.close();
    }
}

void ManagerWindow::refreshStockList()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount((stocks.size()));
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Quantity" << "Price" << "Category" << "Supplier" << "Low stock");

    for (int row = 0; row < (stocks.size()); ++row) {
        const Stock& stock = stocks[row];
        QTableWidgetItem* nameItem = new QTableWidgetItem(stock.name);
        nameItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 0, nameItem);

        QTableWidgetItem* quantityItem = new QTableWidgetItem(QString::number(stock.quantity));
        quantityItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 1, quantityItem);

        QTableWidgetItem* priceItem = new QTableWidgetItem("$" + QString::number(stock.price, 'f', 2));
        priceItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 2, priceItem);

        QTableWidgetItem* categoryItem = new QTableWidgetItem(stock.category);
        categoryItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 3, categoryItem);

        QTableWidgetItem* supplierItem = new QTableWidgetItem(stock.supplier);
        supplierItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 4, supplierItem);

        QString lowStockText = (stock.quantity < 5) ? "Yes" : "No";
        QTableWidgetItem* lowStockItem = new QTableWidgetItem(lowStockText);
        lowStockItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 5, lowStockItem);

    }

    ui->tableWidget->resizeColumnToContents(0);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
}
