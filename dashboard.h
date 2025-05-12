#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <QVector>
#include "stock.h"
#include <QStringListModel>
#include <QListView>

namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(const QString& userName, const QVector<Stock>& inventory, QWidget *parent = nullptr);
    ~Dashboard();
private:
    Ui::Dashboard *ui;
    QString m_userName;
    QVector<Stock> m_inventory;
    void updateSummaryStatistics();
    int calculateLowStockCount() const;
};

#endif // DASHBOARD_H
