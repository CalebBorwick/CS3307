#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "clockprofile.h"

int main(int argc, char *argv[])
{
    std::clockProfile clock(nullptr,true,true,false, false, true);
    clock.getUserInput();
    clock.createClockGui(argc, argv);

    return 0;
}
