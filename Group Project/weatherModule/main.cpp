#include "weatherprofile.h"
#include <iostream>


int main(int argc, char *argv[])
{
    //builds weatherProfile Object
    std::WeatherProfile weath(nullptr,true, 55489, true, true, true);
    //prompts user to fill in information to be displayed
   // weath.getUserInput();
    //calls the create gui class to start the gui
    weath.createWeatherGui(argc, argv);

        return 0;

}
