#include "searchbox.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //builds searchBox object
    std::searchBox w;
    //shows the search window
    w.show();

    return a.exec();
}
