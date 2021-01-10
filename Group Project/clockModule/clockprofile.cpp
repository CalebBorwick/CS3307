#include "clockprofile.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QObject>
#include <QNetworkReply>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>

/*!
  * @brief clockProfile: constructor for clockProfile class creating an object of type clockProfile.
  *
  * Creates an object of type clockProfile with the input parameters being asigned to the class attributes
  * @param parent: A nullptr for the Qobject parent to establish it
  * @param displayClock: bool to decide if the gui will be shown
  * @param displayAmPm: bool to decide if AmPm will be shown
  * @param display24Hour: bool to decide if clock will be in 24 hr format
  * @param displaySeconds: bool to decide if seconds will be shown
  * @param displayDate: bool to decide if date will be shown
  */
std::clockProfile::clockProfile(QObject *parent, bool displayClock, bool displayAmPm,
                                bool display24Hour, bool displaySeconds , bool displayDate):QObject(parent)
{
    /*!< attributes for the clockProfile class*/
    this->displayClock = displayClock;
    this->displayAmPm = displayAmPm;
    this->display24Hour = display24Hour;
    this->displaySeconds = displaySeconds;
    this->displayDate = displayDate;

}

/*!
*@brief ~clockProfile: destructor for the clockProfile
*/
std::clockProfile::~clockProfile(){

}

/*!
* @brief getDisplayClock: getter function of displayClock bool.
*
* function call returns displayClock of type bool to where it was called from
* @return returns displayClock bool
*/
bool std::clockProfile::getDisplayClock(){
    return this->displayClock;
}

/*!
 * @brief setDisplayClock: setter method for the displayClock bool.
 *
 * function call sets the displayClock to the input parameter
 * if true the clock gui will be shown
 * if false it will not be shown
 * @param displayClock: bool to set the displayClock attribute to
 */
void std::clockProfile::setDisplayClock(bool displayClock){
    this->displayClock = displayClock;
}

/*!
* @brief getDisplayAmPm: getter function of displayClock bool.
*
* function call returns displayAmPm of type bool to where it was called from
* @return returns displayAmPm bool
*/
bool std::clockProfile::getDisplayAmPm(){
    return this->displayAmPm;
}

/*!
 * @brief setDisplayAmPm: setter method for the displayAmPm bool.
 *
 * function call sets the displayAmPm to the input parameter
 * if true the Am Pm in the gui will be shown and 24 hour will not
 * if false it will not be shown and 24 hour will be
 * @param displayAmPm: bool to set the displayAmPm attribute to
 */
void std::clockProfile::setDisplayAmPm(bool displayAmPm){
    this->displayAmPm = displayAmPm;
    if(displayAmPm){
        this->setDisplay24Hour(false);
    }
}

/*!
* @brief getDisplay24Hour: getter function of display24Hour bool.
*
* function call returns displayAmPm of type bool to where it was called from
* @return returns display24Hour bool
*/
bool std::clockProfile::getDisplay24Hour(){
    return this->display24Hour;
}

/*!
 * @brief setDisplay24Hour: setter method for the display24Hour bool.
 *
 * function call sets the display24Hour to the input parameter
 * if true the 24 hour in the gui will be shown and AmPm will not
 * if false it will not be shown and AmPm will be
 * @param display24Hour: bool to set the display24Hour attribute to
 */
void std::clockProfile::setDisplay24Hour(bool display24Hour){
    this->display24Hour = display24Hour;
    if(display24Hour){
        this->setDisplayAmPm(false);
    }
}

/*!
 * @brief getDisplaySeconds: getter method for the displaySeconds bool.
 *
 * function call returns displaySeconds of type bool to where it was called from
 * @param displaySeconds: bool to set the displaySeconds attribute to
 */
bool std::clockProfile::getDisplaySeconds(){
    return this->displaySeconds;
}

/*!
 * @brief setDisplaySeconds: setter method for the displaySeconds bool.
 *
 * function call will set the displaySeconds attribute to the input parameter
 * if true seconds will be shown in the gui
 * if false they will not
 * @param displaySeconds: bool to set the displaySeconds attribute to
 */
void std::clockProfile::setDisplaySeconds(bool displaySeconds){
    this->displaySeconds = displaySeconds;
}

/*!
 * @brief getDisplayDate: getter method for the displayDate bool.
 *
 * function call returns displayDate of type bool to where it was called from
 * @param displayDate: bool to set the displayDate attribute to
 */
bool std::clockProfile::getDisplayDate(){
    return this->displayDate;
}

/*!
 * @brief setDisplayDate: setter method for the displayDate bool.
 *
 * function call will set the displayDate attribute to the input parameter
 * if true date will be shown in the gui
 * if false they will not
 * @param displayDate: bool to set the displayDate attribute to
 */
void std::clockProfile::setDisplayDate(bool displayDate){
    this->displayDate = displayDate;
}

/*!
* @brief createClockGui: creates the pop up window that displays the weatherProfile Gui.
*
* Creates a QCoreApplication, QGuiApplication from the parameterss, a QQmlApplicationEngine that allows for variables
* to be passed into the qml files to be used to check if elements are to be displayed, a QQmlContext and sets it to the appbridge
* so that c++ classes are exposed to the qml, creates the connection to the weathGui.qml to load in the
* Gui window.
* @param argc: int arg used to create QGuiApplication
* @param argv: char arg used to create QGuiApplication
*/
void std::clockProfile::createClockGui(int argc, char *argv[]){
    if(this->getDisplayClock()){
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        QGuiApplication app(argc, argv);/*!< creates QQuiApp*/

       QQmlApplicationEngine engine;

       QQmlContext* ctx = engine.rootContext();/*!< cretes the content bridge to exposed c++ to the qml*/
       ctx -> setContextProperty("appBridge", this);

       const QUrl url(QStringLiteral("qrc:/clockGui.qml"));/*!< defines the qml file where the javascript styling is */
       /*!< starts the gui*/
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
 * Gets the user input to allow for the user to turn on and off features of the clockProfile Gui,
 * based on user input setter methods are called to change display data.
 */
void std::clockProfile::getUserInput(){
    char displayClock;
    char displayAmPm;
    char display24Hour;
    char displaySeconds;
    char displayDate;

    /*!< user input to see what will be displayed */
   std::cout << "Would you like to see a clock (y/n): \n";
   std::cin >> displayClock;
   std::cout<< "Would you like tos see ApPm *cannot do 24hour and ampm* (y/n) : \n";
   std::cin >> displayAmPm;
   std::cout<<"Would you like to see 24 clock *cannot do 24hour and ampm* (y/n): \n";
   std::cin>>display24Hour;
   std::cout<<"Would you like to see the second (y/n): \n";
   std::cin>>displaySeconds;
   std::cout<<"Would you like to see the date (y/n)): \n";
   std::cin>>displayDate;

   if(displayClock =='y'|| displayClock =='Y'){
       this->setDisplayClock(true);
   }
   else if(displayClock =='N'|| displayClock =='N'){
       this->setDisplayClock(false);
   }
   else {
       std::cout << "invalid input"<<"\n";
       exit(1);
   }
   if(displayAmPm=='y'|| displayAmPm=='Y'){
       this->setDisplayAmPm(true);
   }
   else if(displayAmPm=='n'|| displayAmPm=='N'){
       this->setDisplayAmPm(false);
   }
   else {
       std::cout << "invalid input"<<"\n";
       exit(1);
   }
   if(display24Hour=='y'|| display24Hour=='Y'){
       this->setDisplay24Hour(true);
   }
   else if(display24Hour=='n'|| display24Hour=='N'){
       this->setDisplay24Hour(false);
   }
   else {
       std::cout << "invalid input"<<"\n";
       exit(1);
   }
   if(displaySeconds=='y'|| displaySeconds=='Y'){
       this->setDisplaySeconds(true);
   }
   else if(displaySeconds=='n'|| displaySeconds=='Y'){
       this->setDisplaySeconds(false);
   }
   else {
       std::cout << "invalid input"<<"\n";
       exit(1);
   }
   if(displayDate=='y'|| displayDate=='Y'){
       this->setDisplayDate(true);
   }
   else if(displayDate=='n'|| displayDate=='N'){
       this->setDisplayDate(false);
   }
   else {
       std::cout << "invalid input"<<"\n";
       exit(1);
   }
}
