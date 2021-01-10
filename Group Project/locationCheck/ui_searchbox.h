/********************************************************************************
** Form generated from reading UI file 'searchbox.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHBOX_H
#define UI_SEARCHBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_searchBox
{
public:
    QWidget *centralWidget;
    QPushButton *searchButton;
    QListWidget *listWidget;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    QLineEdit *lineEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *searchBox)
    {
        if (searchBox->objectName().isEmpty())
            searchBox->setObjectName(QStringLiteral("searchBox"));
        searchBox->resize(406, 413);
        centralWidget = new QWidget(searchBox);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        searchButton = new QPushButton(centralWidget);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        searchButton->setGeometry(QRect(290, 30, 99, 30));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 90, 381, 241));
        confirmButton = new QPushButton(centralWidget);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        confirmButton->setGeometry(QRect(290, 340, 99, 30));
        cancelButton = new QPushButton(centralWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(180, 340, 99, 30));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(12, 30, 271, 32));
        searchBox->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(searchBox);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        searchBox->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(searchBox);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        searchBox->setStatusBar(statusBar);

        retranslateUi(searchBox);

        QMetaObject::connectSlotsByName(searchBox);
    } // setupUi

    void retranslateUi(QMainWindow *searchBox)
    {
        searchBox->setWindowTitle(QApplication::translate("searchBox", "searchBox", nullptr));
        searchButton->setText(QApplication::translate("searchBox", "Search", nullptr));
        confirmButton->setText(QApplication::translate("searchBox", "Confirm", nullptr));
        cancelButton->setText(QApplication::translate("searchBox", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class searchBox: public Ui_searchBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHBOX_H
