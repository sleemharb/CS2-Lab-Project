#include "employeewindow.h"
#include "ui_employeewindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "search.h"

EmployeeWindow::EmployeeWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EmployeeWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_search, &QPushButton::clicked, this, &EmployeeWindow::on_pushButton_search_clicked);
    connect(ui->pushButton_view, &QPushButton::clicked, this, &EmployeeWindow::on_pushButton_view_clicked);
}

EmployeeWindow::~EmployeeWindow()
{
    delete ui;
}
void EmployeeWindow::loadStocksFromFile()
{
    stocks.clear();
    QString filePath = "/Users/bassantibrahim/Desktop/InventoryProject/stocks.txt";
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

void EmployeeWindow::refreshStockList()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(stocks.size());
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Quantity" << "Price" << "Category" << "Supplier" << "Low stock");

    for (size_t row = 0; row < stocks.size(); ++row) {
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

void EmployeeWindow::on_pushButton_search_clicked()
{
    search *searchWindow = new search(ui->tableWidget, this);
    searchWindow->setModal(true);
    searchWindow->setStocks(stocks);
    searchWindow->exec();
    searchWindow->deleteLater();
}

void EmployeeWindow::on_pushButton_view_clicked()
{
    loadStocksFromFile();
    refreshStockList();
}

