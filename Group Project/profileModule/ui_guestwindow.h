/********************************************************************************
** Form generated from reading UI file 'guestwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUESTWINDOW_H
#define UI_GUESTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_guestwindow
{
public:
    QLabel *label;

    void setupUi(QDialog *guestwindow)
    {
        if (guestwindow->objectName().isEmpty())
            guestwindow->setObjectName(QStringLiteral("guestwindow"));
        guestwindow->resize(800, 540);
        label = new QLabel(guestwindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(240, 190, 331, 121));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);

        retranslateUi(guestwindow);

        QMetaObject::connectSlotsByName(guestwindow);
    } // setupUi

    void retranslateUi(QDialog *guestwindow)
    {
        guestwindow->setWindowTitle(QApplication::translate("guestwindow", "Dialog", nullptr));
        label->setText(QApplication::translate("guestwindow", "Hello!!! Guest.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class guestwindow: public Ui_guestwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUESTWINDOW_H
