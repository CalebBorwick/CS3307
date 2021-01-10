/********************************************************************************
** Form generated from reading UI file 'userwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERWINDOW_H
#define UI_USERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_userwindow
{
public:
    QLabel *label;

    void setupUi(QDialog *userwindow)
    {
        if (userwindow->objectName().isEmpty())
            userwindow->setObjectName(QStringLiteral("userwindow"));
        userwindow->resize(800, 540);
        label = new QLabel(userwindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(260, 180, 291, 131));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);

        retranslateUi(userwindow);

        QMetaObject::connectSlotsByName(userwindow);
    } // setupUi

    void retranslateUi(QDialog *userwindow)
    {
        userwindow->setWindowTitle(QApplication::translate("userwindow", "Dialog", nullptr));
        label->setText(QApplication::translate("userwindow", "Hello!!! User.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userwindow: public Ui_userwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERWINDOW_H
