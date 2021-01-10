/*
 * Ian Borwick - 250950449
 * Class header for countries records of covid data
 *      builds objects using the constructor
 * October 1st 2020
 */
#ifndef CS3307_ASN1_INDAVIDUAL_COUNTRYRECORD_H
#define CS3307_ASN1_INDAVIDUAL_COUNTRYRECORD_H


namespace std {

    class countryRecord { //The class countryRecord
        public: //Access specifier
            //attributes for class
            string countryName;
            string countryCode;
            int newConfirmedCases{};
            int newDeaths{};
            int newRecCases{};
            int totalConfirmedCases{};
            int totalDeaths{};
            int totalRecCases{};

            //Constructor declaration and initialization with parameters
            countryRecord(string countryName, string countryCode, int newConfirmedCases, int newDeaths,
                          int newRecCases, int totalConfirmedCases, int totalDeaths, int totalRecCases);

            //Destructor
            ~countryRecord();
        };
}


#endif //CS3307_ASN1_INDAVIDUAL_COUNTRYRECORD_H
