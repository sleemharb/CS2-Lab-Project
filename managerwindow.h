#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H
#include "additem.h"
#include "stock.h"
#include "user.h"
#include <QDialog>

namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QDialog
{
    Q_OBJECT
public:
explicit ManagerWindow(User loggedInUser, QWidget *parent = nullptr);
    ~ManagerWindow();

private slots:
    void on_pushButton_additem_clicked();
    void on_pushButton_deleteItem_clicked();
    void on_pushButton_report_clicked();

private:
    Ui::ManagerWindow *ui;
    additem *additem;
    User user;
    std::vector<Stock> stocks;
    void loadStocksFromFile();
    void refreshStockList();
};

#endif // MANAGERWINDOW_H
