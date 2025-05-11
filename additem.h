#ifndef ADDITEM_H
#define ADDITEM_H

#include <QDialog>

namespace Ui {
class additem;
}

class additem : public QDialog
{
    Q_OBJECT
public:
    explicit additem(QWidget *parent = nullptr);
    ~additem();

private slots:
    void on_additemButton_clicked();

private:
    Ui::additem *ui;
    void loadStocksFromFile();

signals:
    void itemAdded();
};

#endif
