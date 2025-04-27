/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *signuppage;
    QLabel *username;
    QLineEdit *lineEdit_Susername;
    QLabel *label;
    QLineEdit *lineEdit_Spassword;
    QPushButton *signupButton;
    QLabel *label_2;
    QComboBox *comboBox_Srole;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        signuppage = new QLabel(centralwidget);
        signuppage->setObjectName("signuppage");
        signuppage->setGeometry(QRect(320, 0, 161, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Chalkduster")});
        font.setPointSize(21);
        font.setItalic(false);
        signuppage->setFont(font);
        username = new QLabel(centralwidget);
        username->setObjectName("username");
        username->setGeometry(QRect(70, 90, 61, 16));
        lineEdit_Susername = new QLineEdit(centralwidget);
        lineEdit_Susername->setObjectName("lineEdit_Susername");
        lineEdit_Susername->setGeometry(QRect(140, 90, 113, 21));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 140, 58, 16));
        lineEdit_Spassword = new QLineEdit(centralwidget);
        lineEdit_Spassword->setObjectName("lineEdit_Spassword");
        lineEdit_Spassword->setGeometry(QRect(140, 140, 113, 21));
        lineEdit_Spassword->setEchoMode(QLineEdit::EchoMode::Password);
        signupButton = new QPushButton(centralwidget);
        signupButton->setObjectName("signupButton");
        signupButton->setGeometry(QRect(340, 200, 100, 32));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 180, 58, 16));
        comboBox_Srole = new QComboBox(centralwidget);
        comboBox_Srole->addItem(QString());
        comboBox_Srole->addItem(QString());
        comboBox_Srole->addItem(QString());
        comboBox_Srole->setObjectName("comboBox_Srole");
        comboBox_Srole->setGeometry(QRect(140, 170, 103, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 37));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        signuppage->setText(QCoreApplication::translate("MainWindow", "Signup Form", nullptr));
        username->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        signupButton->setText(QCoreApplication::translate("MainWindow", "Signup", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        comboBox_Srole->setItemText(0, QCoreApplication::translate("MainWindow", "Admin", nullptr));
        comboBox_Srole->setItemText(1, QCoreApplication::translate("MainWindow", "Manager", nullptr));
        comboBox_Srole->setItemText(2, QCoreApplication::translate("MainWindow", "Employee", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
