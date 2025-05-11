#ifndef ADDITEM_H
#define ADDITEM_H
#include <vector>
#include <QWidget>
using namespace std;

namespace Ui {
class additem;
}

class additem : public QWidget
{
    Q_OBJECT

public:
    explicit additem(QWidget *parent = nullptr);
    ~additem();

private slots:

    void on_additemButton_clicked();

private:
    Ui::additem *ui;
};

#endif // ADDITEM_H
