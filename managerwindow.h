#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QDialog>

namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ManagerWindow(QWidget *parent = nullptr);
    ~ManagerWindow();

private:
    Ui::ManagerWindow *ui;
};

#endif // MANAGERWINDOW_H
