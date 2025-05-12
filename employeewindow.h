#ifndef EMPLOYEEWINDOW_H
#define EMPLOYEEWINDOW_H

#include <QDialog>

namespace Ui {
class EmployeeWindow;
}

class EmployeeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeWindow(QWidget *parent = nullptr);
    ~EmployeeWindow();

private slots:
    void on_pushButton_view_clicked();

private:
    Ui::EmployeeWindow *ui;
    void on_pushButton_search_clicked();
    void loadStocksFromFile();
    void refreshStockList();
};

#endif // EMPLOYEEWINDOW_H
