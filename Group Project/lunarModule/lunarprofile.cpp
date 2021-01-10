#include "lunarprofile.h"
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
 * @brief LunarProfile: constructor for LunarProfile class creates an object of type LunarProfile.
 *
 * Creates an object of type LunarProfile with the input parameters being set as the class attributes
 * @param parent: A nullptr for the Qobject parent to establish it
 * @param displayLunar: a bool to decide if the lunarphase gui will be displayed
 * @param location: an int representing the location to be used in the api call
 */
std::LunarProfile::LunarProfile(QObject *parent, bool displayLunar, int location){
     /*!< attributes for the weather class*/
    this -> displayLunarPhase= displayLunar;
    this -> location = location;
     /*!< creates the connection for the Api pull requests*/
    QObject::connect(manager,
                     &QNetworkAccessManager::finished,
                     this,
                     &LunarProfile::onRestApiFinished);

}

/*!
* @brief ~LunarProfile: destructor for LunarProfile Class.
*
* Destructor for the LunarProfile class objects
*/
std::LunarProfile::~LunarProfile(){}

/*!
 * @brief getDisplayLunarPhase: getter method for the displayLunarPhase bool.
 *
 * Gets the objects displayLunarPhase attribute and returns it to the location it was called from
 * @return boolean of objects displayLunarPhase attribute
 */
bool std::LunarProfile::getDisplayLunarPhase(){
    return this->displayLunarPhase;
}

/*!
 * @brief setDisplayLunarPhase: setter method for displayLunarPhase bool.
 *
 * Sets the objects displayLunarPhase attribute
 * if true the lunarPhase Gui will be shown
 * if false it will not be
 * @param lunarPhase: a boolean used to change the value of displayLunarPhase
 */
void std::LunarProfile::setDisplayLunarPhase(bool lunarPhase){
    this->displayLunarPhase = lunarPhase;
}

/*!
 * @brief getLocation: getter method for the location int.
 *
 * Gets the objects location attribute and returns it to the location it was called from
 * @return int of objects location attribute
 */
int std::LunarProfile::getLocation(){
    return this->location;
}

/*!
 * @brief setLocation: setter method for location int.
 *
 * Sets the objects location attribute
 * used in the api call
 * @param loc: an int used to change the value of location
 */
void std::LunarProfile::setLocation(int loc){
    this->location=loc;
}

/*!
 * @brief JsonData: getter function of myJsonData.
 *
 * function call returns myJsonData of type QJsonObject to where it was called from
 * @return returns myJsonData object
 */
QJsonObject std::LunarProfile::JsonData() const{
    return myJsonData;
}

/*!
 * @brief setJsonData: setter method for the myJsonData.
 *
 * function call sets the QJsonObject myJsonData to the parameter data
 * @param data: QJsonObject to set the object myJsonData to
 */
void std::LunarProfile::setJsonData(const QJsonObject &data){
    myJsonData = data;
    emit dataChanged(myJsonData);
}

/*!
 * @brief restApiRequest: creates the api call request.
 *
 * Creates a QNetwork request and calls the getLocation() function in order to get the proper location to be used
 * then sets the header and url of the request and uses the manager to finish the request.
 * @see getUrl()
 */
void std::LunarProfile::restApiRequest(){
    QNetworkRequest request;
    QString urlBase = "http://dataservice.accuweather.com/forecasts/v1/daily/1day/";
    QString location = QString::number(this ->getLocation());
    QString det = "?metric=true&details=true&apikey=AiuK1RheAzglUZWO1ppdA2DmGUZL5uXV";
    QString combine = urlBase+location+det;
    QUrl url(combine);
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
 * @param QNetworkReply*: network reply object used to get the api information
 */
void std::LunarProfile::onRestApiFinished(QNetworkReply *reply){
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    setJsonData(doc.object());
    QByteArray array = doc.toJson(QJsonDocument::Compact);
}

/*!
* @brief createLunarPhaseGui: creates the pop up window that displays the lunarProfile Gui.
*
* Creates a QCoreApplication, QGuiApplication from the parameterss, a QQmlApplicationEngine that allows for variables
* to be passed into the qml files to be used to check if elements are to be displayed, a QQmlContext and sets it to the appbridge
* so that c++ classes are exposed to the qml, creates the connection to the lunarPhaseGui.qml to load in the
* Gui window.
* @param argc: int arg used to create QGuiApplication
* @param argv: char arg used to create QGuiApplication
*/
void std::LunarProfile::createLunarPhaseGui(int argc, char *argv[]){
     /*!< only displays if getDisplay weather is true*/
    if(this->getDisplayLunarPhase()==true){
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        QGuiApplication app(argc, argv); /*!< creates QQuiApp*/

        QQmlApplicationEngine engine;

        QQmlContext* ctx = engine.rootContext();  /*!< cretes the content bridge to exposed c++ to the qml*/
        ctx -> setContextProperty("appConnect", this);

        const QUrl url(QStringLiteral("qrc:/lunarPhaseGui.qml")); /*!< defines the qml file where the javascript styling is*/
         /*!< starts the gui */
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
* Gets the user input to allow for the user to turn on and off features of the lunarProfile Gui,
* based on user input setter methods are called to change display data.
*/
void std::LunarProfile::getUserInput(){
     /*!< variables to check displayed data*/
    char displayLunar;

     /*!<  user input to determine what data is displayed*/
    std::cout << "Would you like to see the moons phase (y/n): \n";
    std::cin >> displayLunar;
     /*!<  if user inputted y then Lunar Phase will be shown*/
    if(displayLunar=='y'||displayLunar=='Y'){
        this->setDisplayLunarPhase(true);
    }
     /*!< if user inputted n then Lunar Phase will be shown*/
    else if(displayLunar=='n'||displayLunar=='N'){
        this->setDisplayLunarPhase(false);
    }
    else {
        std::cout << "invalid input"<<"\n";
        exit(1);
    }

}
