#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "additem.h"

ManagerWindow::ManagerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::on_pushButton_additem_clicked()
{
    additem *addItemWindow = new additem(this);
    addItemWindow->show();
}

