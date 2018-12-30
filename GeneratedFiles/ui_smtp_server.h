/********************************************************************************
** Form generated from reading UI file 'smtp_server.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMTP_SERVER_H
#define UI_SMTP_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SMTP_serverClass
{
public:
    QWidget *centralWidget;
    QTextBrowser *messageBrowser;
    QListWidget *userList;
    QLabel *label;
    QLabel *label_2;
    QTextBrowser *contentBrowser;
    QLabel *label_3;
    QLabel *pic_label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SMTP_serverClass)
    {
        if (SMTP_serverClass->objectName().isEmpty())
            SMTP_serverClass->setObjectName(QStringLiteral("SMTP_serverClass"));
        SMTP_serverClass->resize(900, 675);
        centralWidget = new QWidget(SMTP_serverClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        messageBrowser = new QTextBrowser(centralWidget);
        messageBrowser->setObjectName(QStringLiteral("messageBrowser"));
        messageBrowser->setGeometry(QRect(10, 40, 211, 561));
        userList = new QListWidget(centralWidget);
        userList->setObjectName(QStringLiteral("userList"));
        userList->setGeometry(QRect(250, 40, 291, 171));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 71, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(250, 10, 55, 16));
        contentBrowser = new QTextBrowser(centralWidget);
        contentBrowser->setObjectName(QStringLiteral("contentBrowser"));
        contentBrowser->setGeometry(QRect(250, 240, 581, 351));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(250, 220, 55, 16));
        pic_label = new QLabel(centralWidget);
        pic_label->setObjectName(QStringLiteral("pic_label"));
        pic_label->setGeometry(QRect(600, 20, 55, 16));
        SMTP_serverClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SMTP_serverClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 900, 26));
        SMTP_serverClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SMTP_serverClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SMTP_serverClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SMTP_serverClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SMTP_serverClass->setStatusBar(statusBar);

        retranslateUi(SMTP_serverClass);

        QMetaObject::connectSlotsByName(SMTP_serverClass);
    } // setupUi

    void retranslateUi(QMainWindow *SMTP_serverClass)
    {
        SMTP_serverClass->setWindowTitle(QApplication::translate("SMTP_serverClass", "SMTP_server", 0));
        label->setText(QApplication::translate("SMTP_serverClass", "record:", 0));
        label_2->setText(QApplication::translate("SMTP_serverClass", "User:", 0));
        label_3->setText(QApplication::translate("SMTP_serverClass", "mail:", 0));
        pic_label->setText(QApplication::translate("SMTP_serverClass", "picture:", 0));
    } // retranslateUi

};

namespace Ui {
    class SMTP_serverClass: public Ui_SMTP_serverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMTP_SERVER_H
