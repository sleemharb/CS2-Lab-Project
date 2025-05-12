#include "dashboard.h"
#include "ui_dashboard.h"
#include <QStringListModel>
#include <QListView>
#include <QLabel>
#include <QDebug> // Added for debugging

Dashboard::Dashboard(const QString& userName, const QVector<Stock>& inventory, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dashboard),
    m_userName(userName), // Correctly initialize m_userName
    m_inventory(inventory) // Correctly initialize m_inventory
{
    ui->setupUi(this);
    ui->welcomeLabel->setText("Welcome, " + m_userName + "!"); // Use the member variable
    updateSummaryStatistics();
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::updateSummaryStatistics()
{
    ui->totalItemsValue->setText("Total Items: " + QString::number(m_inventory.size()));
    ui->lowStockAlertsValue->setText("Low Stock Alerts: " + QString::number(calculateLowStockCount()));
}

int Dashboard::calculateLowStockCount() const
{
    int lowStockCount = 0;
    for (const auto& stock : m_inventory) {
        if (stock.quantity < 5) {
            lowStockCount++;
        }
    }
    return lowStockCount;
}

