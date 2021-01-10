#ifndef GUESTWINDOW_H
#define GUESTWINDOW_H

#include <QDialog>

namespace Ui {
class guestwindow;
}

class guestwindow : public QDialog
{
    Q_OBJECT

public:
    explicit guestwindow(QWidget *parent = nullptr);
    ~guestwindow();

private:
    Ui::guestwindow *ui;
};

#endif // GUESTWINDOW_H
