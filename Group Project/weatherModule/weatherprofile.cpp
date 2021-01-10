#include "weatherprofile.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QObject>
#include <QNetworkReply>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <iostream>

/*!
 * @brief WeatherProfile: constructor for WeatherProfile class creates an object of type WeatherProfile.
 *
 * Creates an object of type WeatherProfile with the input parameters being set as the class attributes
 * @param parent: A nullptr for the Qobject parent to establish it
 * @param displayWeather: A bool to decide if the weather gui will be shown
 * @param location: A int representing the location of the user
 * @param units: A bool to decide if the units will be farenheit or celsius
 * @param details: A bool to decide if additional details for the weather will be shown
 * @param week: A bool to decide if the forecast will be 1 day or 5 day
 * @return object of type weatherProfile
 */
std::WeatherProfile::WeatherProfile(QObject *parent, bool displayweather, int location, bool units,bool details, bool week) : QObject(parent)
{
     /*!< attributes for the weather class*/
    this -> displayWeather= displayweather;
    this -> location = location;
    this -> units= units;
    this -> details = details;
    this -> week = week;
    //this -> position = position;
     /*!<  creates the connection for the Api pull requests*/
    QObject::connect(manager,
                     &QNetworkAccessManager::finished,
                     this,
                     &WeatherProfile::onRestApiFinished);

}

/*!
 * @brief ~WeatherProfile: destructor for WeatherProfile Class.
 *
 * Destructor for the weatherProfile class objects
 */
std::WeatherProfile::~WeatherProfile(){
}

/*!
 * @brief setDisplayWeather: setter method for displayWeather bool.
 *
 * Sets the object displayWeather to the parameter passed in to change weather or not the weather data will be displayed
 * @param displayWeather: A boolean used to change the displayWeather
 */
void std::WeatherProfile::setDisplayWeather(bool displayWeather) {
    this->displayWeather=displayWeather;
}

/*!
 * @brief getDisplayWeather: getter method for the displayWeather bool.
 *
 * Gets the objects displayWeather attribute and returns it to the point at which the method was called
 * @return Boolean of objects displayWeather attribute
 */
bool std::WeatherProfile::getDisplayWeather(){
    return this->displayWeather;
}

/*!
 * @brief getLocation: getter method for the location int.
 *
 * Gets the objects location attribute and returns it to the point at which the method was called
 * @return int of objects location attribute
 */
int std::WeatherProfile::getLocation() {
    return this->location;
}

/*!
 * @brief getLocation: setter method for location int.
 *
 * Sets the object location to the parameter passed in to change the users location
 * @param displayWeather: A int used to change the location
 */
void std::WeatherProfile::setLocation(int location){
    this->location = location;
}

/*!
 * @brief getUnits: getter method for the units bool.
 *
 * Gets the objects units attribute and returns it to the point at which the method was called
 * @return bool of objects units attribute
 */
bool std::WeatherProfile::getUnits() {
    return this->units;
}

/*!
 * @brief setUnits: setter method for location int.
 *
 * Sets the object units to the parameter passed in to change if the units will be celcius or fahrenheit
 * @param units: A bool used to change the unit type
 */
void std::WeatherProfile::setUnits(bool unit) {
    this->units=unit;
}

/*!
 * @brief getDetails: getter method for the detilas bool.
 *
 * Gets the objects details attribute and returns it to the point at which the method was called.
 * @return bool of object details
 */
bool std::WeatherProfile::getDetails() {
    return this->details;
}

/*!
 * @brief setDetails: setter method for the details bool.
 *
 * Sets the objects details attribute if true details will be shown if false details will not be shown.
 * @param details: a bool used to turn on and off the details on the GUI
 */
void std::WeatherProfile::setDetails(bool details) {
     this->details = details;
}

/*!
 * @brief getWeek: getter method for the the week bool.
 *
 * Gets the objects week attribute and returns it to the location it was called from.
 * @return bool of week attribute
 */
bool std::WeatherProfile::getWeek(){
    return this->week;
}
/*!
 * @brief setWeek: setter method for week bool.
 *
 * Sets the objects week attribute if true then the 5day foprcast will be shown if false then
 * the 1 day forcast will be shown.
 * @param week: a bool used the change the forecast from 1 day to 5 day
 */
void std::WeatherProfile::setWeek(bool week){
    this->week = week;
}
/*!
 * @brief JsonData: getter function of myJsonData.
 *
 * function call returns myJsonData of type QJsonObject to where it was called from
 * @return returns myJsonData object
 */
QJsonObject std::WeatherProfile::JsonData() const{
    return myJsonData;
}

/*!
 * @brief setJsonData: setter method for the myJsonData.
 *
 * function call sets the QJsonObject myJsonData to the parameter data
 * @param data: QJsonObject to set the object myJsonData to
 */
void std::WeatherProfile::setJsonData(const QJsonObject &data){
    myJsonData = data;
    emit dataChanged(myJsonData);
}
/*!
 * @brief getUrl: gets the QUrl for the Api call.
 *
 * Gets the QUrl based on the if the units are to be celsius or ferenheit.
 * @see getUnits()
 * @return QUrl object with the proper metric for units
 */
QUrl std::WeatherProfile::getUrl(){

    if (this->getUnits()){ /*!< if celcius */
        QString urlBase = "http://dataservice.accuweather.com/forecasts/v1/daily/5day/";
        QString location = QString::number(this ->getLocation());
        QString det = "?metric=true&details=true&apikey=AiuK1RheAzglUZWO1ppdA2DmGUZL5uXV";
        QString combine = urlBase+location+det;
        QUrl url(combine);
        return url;
    }
    else{/*!< if ferenheit*/
        QString urlBase = "http://dataservice.accuweather.com/forecasts/v1/daily/5day/";
        QString location = QString::number(this ->getLocation());
        QString det = "?details=true&apikey=AiuK1RheAzglUZWO1ppdA2DmGUZL5uXV";
        QString combine = urlBase+location+det;
        QUrl url(combine);
        return url;
    }
};

/*!
 * @brief restApiRequest: creates the api call request.
 *
 * Creates a QNetwork request and calls the getUrl function in order to get the proper url to be used
 * then sets the header and url of the request and uses the manager to finish the request.
 * @see getUrl()
 */void std::WeatherProfile::restApiRequest(){
    QNetworkRequest request;
    QUrl url = getUrl();
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(url);
    manager->get(request);
}

/*!
 * @brief onRestApiFinished: sets the QJsonDocument from the request.
 *
 * Creates a QJsonDocument and reads in the information retrived by the restApiRequest function
 * then calls the setJsonData function to save the information in and object and loads it into a QByteArray.
 *
 * @see restApiRequest()
 * @see setJsonData()
 */void std::WeatherProfile::onRestApiFinished(QNetworkReply *reply){
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    setJsonData(doc.object());
    QByteArray array = doc.toJson(QJsonDocument::Compact);
     /*!<  qDebug() << QLatin1String(array); Used to display the Json data */
}

/*!
 * @brief createWeatherGui: creates the pop up window that displays the weatherProfile Gui.
 *
 * Creates a QCoreApplication, QGuiApplication from the parameterss, a QQmlApplicationEngine that allows for variables
 * to be passed into the qml files to be used to check if elements are to be displayed, a QQmlContext and sets it to the appbridge
 * so that c++ classes are exposed to the qml, creates the connection to the weathGui.qml to load in the
 * Gui window.
 * @param argc: int arg used to create QGuiApplication
 * @param argv: char arg used to create QGuiApplication
 */void std::WeatherProfile::createWeatherGui(int argc, char *argv[]){
     /*!<  only displays if getDisplay weather is true*/
    if(this->getDisplayWeather()==true){
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        QGuiApplication app(argc, argv); /*!< creates QQuiApp*/

        QQmlApplicationEngine engine;

        QQmlContext* ctx = engine.rootContext();  /*!<  cretes the content bridge to exposed c++ to the qml*/
        ctx -> setContextProperty("appBridge", this);

        const QUrl url(QStringLiteral("qrc:/weatherGui.qml")); /*!< defines the qml file where the javascript styling is */
         /*!<  starts the gui */
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl){
            if (!obj && url == objUrl){
                QCoreApplication::exit(-1);
            }
        }, Qt::QueuedConnection);
        engine.load(url);
        app.exec();
    }
}

/*!
 * @brief getUserInput: gets the user input to change parameters from default.
 *
 * Gets the user input to allow for the user to turn on and off features of the weatherProfile Gui,
 * based on user input setter methods are called to change display data.
 */
void std::WeatherProfile::getUserInput(){
     /*!< variables to check displayed data */
    char displayWeather;
    char units;
    char details;
    int weekly;
     /*!<  user input to determine what data is displayed */
    std::cout << "Would you like to see the weather forcast (y/n): \n";
    std::cin >> displayWeather;
    std::cout<< "Would you like Celsius or fahrenheit (c/f): \n";
    std::cin >> units;
    std::cout<<"Would you like to see extra weather details (y/n): \n";
    std::cin>>details;
    std::cout<<"Would you like to see the 5 day or 1 day forecast (5/1): \n";
    std::cin>>weekly;

     /*!< if user inputted n for displayWeather then weather will not be shown */
    if(displayWeather=='n'||displayWeather=='N'){
        this->setDisplayWeather(false);
    }
    else if(displayWeather=='y'||displayWeather=='Y'){
        this->setDisplayWeather(true);
    }
    else {
                std::cout << "invalid input"<<"\n";
                exit(1);
            }
    /*!< if user inputted c then units in Celsius */
    if(units=='c'||units=='C'){
       this->setUnits(true);
    }
    /*!< if user inputted f then units in fahrenheit */
    else if(units=='f'||units=='F'){
        this->setUnits(false);
    }
    else {
        std::cout << "invalid input"<<"\n";
        exit(1);
        }
    /*!< if user inputted n for details then details will not be shown */
    if(details=='n'||details=='N'){
        this->setDetails(false);
    }
    else if(details=='y'||details=='Y'){
        this->setDetails(true);
    }
    else {
        std::cout << "invalid input"<<"\n";
        exit(1);
        }
    /*!< if user inputted 1 then 1day forecast will be shown */
    if(weekly==1||weekly==1){
        this->setWeek(false);
    }
    /*!< if user inputted 5 then 5day forecast will be shown */
    else if(weekly==5||weekly==5){
        this->setWeek(true);
    }
    else {
        std::cout << "invalid input"<<"\n";
        exit(1);
    }

}
