#include "lunarprofile.h"

int main(int argc, char *argv[])
{
    std::LunarProfile lunar(nullptr, true, 55489);
    //lunar.getUserInput();
    lunar.createLunarPhaseGui(argc,argv);

    return 0;
}
