#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <QTableWidget>
#include <QVector>
#include "stock.h"
#include <QDialog>


namespace Ui {
class search;
}

class search : public QDialog
{
    Q_OBJECT

public:
    explicit search(QTableWidget *tableWidget, QWidget *parent = nullptr);
    ~search();

    void setStocks(const QVector<Stock> &stocks);
    void setStocks(const std::vector<Stock> &stocks);
private slots:
    void on_ssearchbutton_clicked();

private:
    Ui::search *ui;
    QTableWidget *tableWidget;
    QVector<Stock> allStocks;

};

#endif // SEARCH_H
