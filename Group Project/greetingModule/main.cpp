#include "greetings.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    greetings gr(nullptr);
    gr.createGreetingsGui(argc, argv);
    return 0;
}
