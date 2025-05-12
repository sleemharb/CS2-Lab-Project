#include "search.h"
#include "ui_search.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QHeaderView>

search::search(QTableWidget *tableWidget, QWidget *parent)
    : QDialog(parent), ui(new Ui::search), tableWidget(tableWidget)
{
    ui->setupUi(this);
    setWindowTitle("Search Items");

    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    connect(ui->ssearchbutton, &QPushButton::clicked, this, &search::on_ssearchbutton_clicked);
}
search::~search()
{
    delete ui;
}

void search::setStocks(const QVector<Stock> &stocks)
{
    allStocks = stocks;
}

void search::on_ssearchbutton_clicked()
{
    QString searchText = ui->lineEdit_name->text().trimmed();

    QVector<Stock> filteredStocks;

    for (const Stock &stock : allStocks) {
        if (searchText.isEmpty() || stock.name.contains(searchText, Qt::CaseInsensitive)) {
            filteredStocks.append(stock);
        }
    }


    if (filteredStocks.isEmpty()) {
        QMessageBox::information(this, "No Results", "No stocks found matching your search criteria.");
    }

    tableWidget->clearContents();
    tableWidget->setRowCount(filteredStocks.size());

    for (int row = 0; row < filteredStocks.size(); ++row) {
        const Stock &stock = filteredStocks[row];

        QTableWidgetItem* nameItem = new QTableWidgetItem(stock.name);
        nameItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(row, 0, nameItem);

        QTableWidgetItem* quantityItem = new QTableWidgetItem(QString::number(stock.quantity));
        quantityItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(row, 1, quantityItem);

        QTableWidgetItem* priceItem = new QTableWidgetItem("$" + QString::number(stock.price, 'f', 2));
        priceItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(row, 2, priceItem);

        QTableWidgetItem* categoryItem = new QTableWidgetItem(stock.category);
        categoryItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(row, 3, categoryItem);

        QTableWidgetItem* supplierItem = new QTableWidgetItem(stock.supplier);
        supplierItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(row, 4, supplierItem);

        QString lowStockText = (stock.quantity < 5) ? "Yes" : "No";
        QTableWidgetItem* lowStockItem = new QTableWidgetItem(lowStockText);
        lowStockItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(row, 5, lowStockItem);
    }

    tableWidget->resizeColumnToContents(0);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
}

void search::setStocks(const std::vector<Stock> &stocks)
{
    allStocks.clear();
    for (const auto &stock : stocks) {
        allStocks.append(stock);
    }
}
