#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "countryRecord.h"
/*
 * Ian Borwick - 250950449
 * Covid data sorting
 *      Includes reading in the file and parsing it
 *      sorting the data according to user input
 *      displaying the data in graphs
 * October 1st 2020
 */
using namespace std;

//getData() reads in the file from user input and opens it to be used
//returns a vector containing countryRecord objects
vector<countryRecord> getData(){
    //variables used in function
    vector<countryRecord> record; //vector to hold all the countryRecord objects
    string line, word, temp, file;
    int index = 0;

    //get the file name from user
    fstream csvFile;
    cout << "Enter a file name: ";
    cin >> file;
    cout << endl;

    //attempts to open the file and read in line by line
    csvFile.open(file,ios::in);
    if (csvFile.is_open())
    {
        //reads the csv file line by line and parses it into individual lines ends when there are no lines remaining
        while ( getline (csvFile,line) )
        {
            //checks for comma in the title in the country name and removes it to allow for proper parsing
            if(line[0]=='"'){ //checks to see if the first char is a quotation mark
                bool boolean = true;
                int iterator = 0;
                string frontLine = line; //copy of the line before the comma
                string backLine = line; //copy of the line after the coma
                while (boolean){
                    if(line[iterator]==','){
                        frontLine.erase(iterator); // erases everything after the comma
                        backLine.erase(0,iterator+1); //erases everything before the comma
                        boolean = false;
                        line = frontLine+backLine; //concatenates the frontLine and backline to finish the comma removal
                    }
                    iterator++;
                }
            }
            stringstream stream(line); // prepares the data to be tokenized
            vector<string> toke; //creates a vector to hold the tokens of each line

            //tokenizes each line on commas and pushes it into the vector
            while(getline(stream, temp, ',')){
                toke.push_back(temp);
            }

            if(index>0) { //skips the first line as it is the titles of columns
                countryRecord rec(toke[0], toke[1], stoi(toke[3]), stoi(toke[4]), stoi(toke[5]), stoi(toke[8]),
                                  stoi(toke[9]), stoi(toke[10])); //creates a new object of countryRecord
                record.push_back(rec); //pushes the new object into the vector file
            }
            index++; //index is increased to assist with the skipping of the first line
        }
        csvFile.close(); // closes the input file
    }
    //if the file is unable to be opened gives a message and exits
    else {
        cout << "Unable to open file";
        exit(1);

    }
    return record;//returns the vector full of objects
}

//getDisplayData takes in the sorted data and returns the 10 values selected in the user input
//returns a vector containing 10 countryRecord objects
vector<countryRecord> getDisplayData(vector<countryRecord> sortedData){
    int it = 0;
    vector<countryRecord> displayData;
    for (const auto &i:sortedData){ // iterates through the total data
        if (it<10){
            displayData.push_back(i); // pushes the 10 values to a vector file to be displayed
        }
        it++; //increments iterator to make sure only 10 values are in the vector
    }
    return displayData; //returns the vector file with the 10 objects
}


//sortData takes in the unsorted record and through user prompts displays a chart of there selected data
void sortData(vector<countryRecord> record){
    string sortVal, order;
    int divCheck = 0;
    int div = 1;

    //user prompt to determine if data is ascending or descending
    cout << "would you like the data ascending or descending: \n\n"
            "ascending = A,\n"
            "descending = D\n";

    cin>> order; // record the order to the variable order

    if(order == "A"){//if the order selected in ascending
        //prompts user to select the data field they would like to sort by
        cout << "What data field would you like to sort by: \n\n"
                "new confirmed cases = NCC,\n"
                "new deaths = ND,\n"
                "new recovered cases = NRC,\n"
                "total confirmed cases = TCC,\n"
                "total deaths = TD, \n"
                "total recovered cases = TRC\n";

        cin>>sortVal;//record the sort value to the variable sortVal to allow for checks

        if(sortVal == "NCC"){//if the value is new confirmed cases
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.newConfirmedCases < rhs.newConfirmedCases;
            });
            vector<countryRecord> sorted = getDisplayData(record); //new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) { // iterates through sorted values
                if(i.newConfirmedCases==0){ //checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.newConfirmedCases/70;
                    divCheck++;
                }
                int symbolsPerCase = i.newConfirmedCases/div; //determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//print statement for the single countries
                cout<< "   |"<<endl;
            }
            cout<< string(70,'-') <<endl;
            cout << "New Confirmed Cases; Each # is approx "<< div <<" cases" <<endl;//end of graph print statements
        }
        else if (sortVal=="ND"){//if the value is new deaths
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.newDeaths < rhs.newDeaths;
            });
            vector<countryRecord> sorted = getDisplayData(record);//new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) {// iterates through sorted values
                if(i.newDeaths==0){//checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.newDeaths/70;
                    divCheck++;
                }
                int symbolsPerCase = i.newDeaths/div;//determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//print statement for the single countries
                cout<< "   |"<<endl;
            }
            cout<< string(70,'-') <<endl;
            cout << "New Deaths; Each # is approx "<< div <<" cases" <<endl;//end of graph print statements
        }
        else if (sortVal=="NRC"){//if the value is new recovered cases
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.newRecCases < rhs.newRecCases;
            });
            vector<countryRecord> sorted = getDisplayData(record);//new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) {
                if(i.newRecCases==0){//checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.newRecCases/70;
                    divCheck++;
                }
                int symbolsPerCase = i.newRecCases/div;//determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//print statement for the single countries
                cout<< "   |"<<endl;//end of graph print statements
            }
            cout<< string(70,'-') <<endl;
            cout << "New Recovered Cases; Each # is approx "<< div <<" cases" <<endl;
        }
        else if (sortVal=="TCC"){//if the value is total confirmed cases
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.totalConfirmedCases < rhs.totalConfirmedCases;
            });
            vector<countryRecord> sorted = getDisplayData(record);//new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) {
                if(i.totalConfirmedCases==0){//checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.totalConfirmedCases/70;
                    divCheck++;
                }
                int symbolsPerCase = i.totalConfirmedCases/div;//determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//determines the number of symbols needed
                cout<< "   |"<<endl;
            }
            cout<< string(70,'-') <<endl;
            cout << "Total Confirmed Cases; Each # is approx "<< div <<" cases" <<endl;//end of graph print statements
        }
        else if (sortVal=="TD"){//if the value is total deaths
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.totalDeaths < rhs.totalDeaths;
            });
            vector<countryRecord> sorted = getDisplayData(record);//new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) {
                if(i.totalDeaths==0){//checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.totalDeaths/70;
                    divCheck++;
                }
                int symbolsPerCase = i.totalDeaths/div;//determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//end of graph print statements
                cout<< "   |"<<endl;
            }
            cout<< string(70,'-') <<endl;
            cout << "Total Deaths; Each # is approx "<< div <<" cases" <<endl;
        }
        else if (sortVal=="TRC"){//if the value is total recovered cases
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.totalRecCases < rhs.totalRecCases;
            });
            vector<countryRecord> sorted = getDisplayData(record);//new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) {
                if(i.totalRecCases==0){//checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.totalRecCases/70;
                    divCheck++;
                }
                int symbolsPerCase = i.totalRecCases/div;//determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//end of graph print statements
                cout<< "   |"<<endl;
            }
            cout<< string(70,'-') <<endl;
            cout << "Total Recovered Cases; Each # is approx "<< div <<" cases" <<endl;
        }
        //exit statement for invalid input
        else {
            cout << "invalid input"<<"\n";
            exit(1);
        }
    }
    else if(order == "D"){//if the order selected in ascending
        //prompts user to select the data field they would like to sort by
        cout << "What data field would you like to sort by: \n\n"
                "new confirmed cases = NCC,\n"
                "new deaths = ND,\n"
                "new recovered cases = NRC,\n"
                "total confirmed cases = TCC,\n"
                "total deaths = TD, \n"
                "total recovered cases = TRC\n";

        cin>>sortVal;//record the sort value to the variable sortVal to allow for checks

        if(sortVal == "NCC"){//if the value is new confirmed cases
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.newConfirmedCases > rhs.newConfirmedCases;
            });
            vector<countryRecord> sorted = getDisplayData(record); //new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) { // iterates through sorted values
                if(i.newConfirmedCases==0){ //checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.newConfirmedCases/70;
                    divCheck++;
                }
                int symbolsPerCase = i.newConfirmedCases/div; //determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//print statement for the single countries
                cout<< "   |"<<endl;
            }
            cout<< string(70,'-') <<endl;
            cout << "New Confirmed Cases; Each # is approx "<< div <<" cases" <<endl;//end of graph print statements
        }
        else if (sortVal=="ND"){//if the value is new deaths
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.newDeaths > rhs.newDeaths;
            });
            vector<countryRecord> sorted = getDisplayData(record);//new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) {// iterates through sorted values
                if(i.newDeaths==0){//checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.newDeaths/70;
                    divCheck++;
                }
                int symbolsPerCase = i.newDeaths/div;//determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//print statement for the single countries
                cout<< "   |"<<endl;
            }
            cout<< string(70,'-') <<endl;
            cout << "New Deaths; Each # is approx "<< div <<" cases" <<endl;//end of graph print statements
        }
        else if (sortVal=="NRC"){//if the value is new recovered cases
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.newRecCases > rhs.newRecCases;
            });
            vector<countryRecord> sorted = getDisplayData(record);//new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) {
                if(i.newRecCases==0){//checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.newRecCases/70;
                    divCheck++;
                }
                int symbolsPerCase = i.newRecCases/div;//determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//print statement for the single countries
                cout<< "   |"<<endl;//end of graph print statements
            }
            cout<< string(70,'-') <<endl;
            cout << "New Recovered Cases; Each # is approx "<< div <<" cases" <<endl;
        }
        else if (sortVal=="TCC"){//if the value is total confirmed cases
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.totalConfirmedCases > rhs.totalConfirmedCases;
            });
            vector<countryRecord> sorted = getDisplayData(record);//new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) {
                if(i.totalConfirmedCases==0){//checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.totalConfirmedCases/70;
                    divCheck++;
                }
                int symbolsPerCase = i.totalConfirmedCases/div;//determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//determines the number of symbols needed
                cout<< "   |"<<endl;
            }
            cout<< string(70,'-') <<endl;
            cout << "Total Confirmed Cases; Each # is approx "<< div <<" cases" <<endl;//end of graph print statements
        }
        else if (sortVal=="TD"){//if the value is total deaths
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.totalDeaths > rhs.totalDeaths;
            });
            vector<countryRecord> sorted = getDisplayData(record);//new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) {
                if(i.totalDeaths==0){//checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.totalDeaths/70;
                    divCheck++;
                }
                int symbolsPerCase = i.totalDeaths/div;//determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//end of graph print statements
                cout<< "   |"<<endl;
            }
            cout<< string(70,'-') <<endl;
            cout << "Total Deaths; Each # is approx "<< div <<" cases" <<endl;
        }
        else if (sortVal=="TRC"){//if the value is total recovered cases
            //sort function with lambda expression
            sort(record.begin(), record.end(), [](const countryRecord& lhs, const countryRecord& rhs){
                return lhs.totalRecCases > rhs.totalRecCases;
            });
            vector<countryRecord> sorted = getDisplayData(record);//new vector for the sorted 10 values using getDisplayData() function
            for (const auto &i:sorted) {
                if(i.totalRecCases==0){//checks to see if the value is 0
                    divCheck++;
                }
                if(divCheck == 0){//check to see if it is the first field to use as the dividing factor
                    div = i.totalRecCases/70;
                    divCheck++;
                }
                int symbolsPerCase = i.totalRecCases/div;//determines the number of symbols needed
                cout << i.countryCode << " | " << string(symbolsPerCase,'#') <<  endl;//end of graph print statements
                cout<< "   |"<<endl;
            }
            cout<< string(70,'-') <<endl;
            cout << "Total Recovered Cases; Each # is approx "<< div <<" cases" <<endl;
        }
            //exit statement for invalid input
        else {
            cout << "invalid input"<<"\n";
            exit(1);
        }
    }
    //exit statement for invalid input
    else {
        cout << "invalid input"<<"\n";
        exit(1);
    }


}

//main calls upon the other functions inorder to:
//get the data
//sort the data according to user input
//display the data selected
int main() {
    vector<countryRecord> record; // creates a vector to be filled with countryRecord objects
    record = getData(); //calls the getData() function to receive the vector full of objects
    sortData(record);// calls the sortData() function to sort the data based on user input and display the selected data
    return 0;
   }
