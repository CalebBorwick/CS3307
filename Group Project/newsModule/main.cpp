#include "newsprofile.h"
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
    //getting user input for testing:
    string category, country_code;
    vector<string> c ={"ae", "ar", "at", "au", "be", "bg", "br", "ca","ch", "cn", "co", "cu", "cz",
                      "de", "eg", "fr", "gb", "gr", "hk", "hu", "id", "ie", "il", "in", "it", "jp",
                      "kr", "lt", "lv", "ma", "mx", "my", "ng", "nl", "no", "nz", "ph", "pl", "pt",
                      "ro", "rs", "ru", "sa", "se", "sg" "si", "sk", "th", "tr", "tw", "ua", "us", "ve", "za"}; //vector of available country codes fro news

    while (1){ //input checking for news category
        cout << "From the menue below, " << endl;
        cout << "> business" << endl;
        cout << "> entertainment" << endl;
        cout << "> general" << endl;
        cout << "> health" << endl;
        cout << "> science" << endl;
        cout << "> sports" << endl;
        cout << "> technology" << endl;
        cout << "Type the news category you are interested in: ";
        cin >> category;
        std::transform(category.begin(), category.end(), category.begin(),
            [](unsigned char c){ return std::tolower(c); });
        if(category!="business" && category!="entertainment" && category!="general" && category!="health" && category!="science" && category!="sports" && category!="technology"){
            cout << "INVALID NEWS CATEGORY." << endl;
        }
        else{
            break;
        }
     }

    bool found;
    while (1){ //input checking for country code
        found = false;
        cout << "Type the lowercase 2-letter ISO 3166-1 code of the country you want to get headlines for: ";
        cin >> country_code;
        std::transform(country_code.begin(), country_code.end(), country_code.begin(),
            [](unsigned char c){ return std::tolower(c); });


         for(unsigned i=0; i<c.size(); i++){
             if(country_code == c[i]){
               found = true;
               break;
             }
          }
          if (found == true){
              break;
          }
          else{
            cout << "INVALID COUNTRY CODE." << endl;
          }
    }

    //now that category and country code are entered, create newsprofile obj:
    newsprofile news(nullptr, true, country_code, category);
    news.createNewsGui(argc, argv);
    return 0;
}
