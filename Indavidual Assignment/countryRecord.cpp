/*
 * Ian Borwick - 250950449
 * Class for countries records of covid data
 *      builds objects using the constructor
 * October 1st 2020
 */
#include <iostream>
#include <string>
#include <utility>
#include "countryRecord.h"


using namespace std;

//Constructor with parameters for countryRecord class
//assigns parameters to the individual attributes of countryRecord to create objects
std::countryRecord::countryRecord(string name, string code, int NCC, int ND, int NRC, int TCC, int TD, int TRC) {
        //attributes for countryRecord Class
        this -> countryName = std::move(name);
        this -> countryCode = std::move(code);
        this -> newConfirmedCases = NCC;
        this -> newDeaths = ND;
        this -> newRecCases = NRC;
        this -> totalConfirmedCases = TCC;
        this -> totalDeaths = TD;
        this -> totalRecCases = TRC;
}

//Destructor for countryRecord objects
std::countryRecord::~countryRecord() = default;


