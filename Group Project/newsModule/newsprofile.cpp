#include "newsprofile.h"
#include <iostream>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QObject>
#include <QNetworkReply>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QMouseEvent>
#include <QCoreApplication>

/*!
 * @brief newsprofile: constructor for newsprofile class creates an object of type newsprofile.
 *
 * Creates an object of type WeatherProfile with the input parameters being set as the class attributes
 * @param parent: A nullptr for the Qobject parent to establish it
 * @param displayNews: A bool to decide if the news gui will be shown
 * @param c: A string representing the country code for news api
 * @param ctg: A string representing the news category for news api
 * @return object of type newsprofile
 */
newsprofile::newsprofile(QObject *parent, bool displayNews, std::string c, std::string ctg) : QObject(parent) {
    this->displayNews = displayNews;
    this->category = ctg;
    this->country = c;
    QObject::connect(manager, &QNetworkAccessManager::finished, this, &newsprofile::onRestApiFinished);
}


/*!
 * @brief ~newsprofile: destructor for newsprofile Class.
 *
 * Destructor for the newsprofile class objects
 */
newsprofile::~newsprofile() {

}

/*!
 * @brief setCategory: setter method for category string.
 *
 * Sets the object category to the parameter passed in to use in news API
 * @param ctg: A string used to change the category
 */
void newsprofile::setCategory(std::string ctg){
    this->category = ctg;
}

/*!
 * @brief setCountry: setter method for country string.
 *
 * Sets the object country to the parameter passed in to use in news API
 * @param c: A string used to change the country
 */
void newsprofile::setCountry(std::string c){
    this->country = c;
}

/*!
 * @brief setdisplayNews: setter method for displayNews bool.
 *
 * Sets the object displayNews to the parameter passed in to change weather or not the news data will be displayed
 * @param d: A boolean used to change the displayNews
 */
void newsprofile::setdisplayNews(bool d){
    this->displayNews = d;
}

/*!
 * @brief getCategory: getter method for the category string.
 *
 * Gets the objects category attribute and returns it to the point at which the method was called
 * @return string of objects category attribute
 */
std::string newsprofile::getCategory(){
    return this->category;
}

/*!
* @brief getCountry: getter method for the country string.
*
* Gets the objects country attribute and returns it to the point at which the method was called
* @return string of objects country attribute
*/
std::string newsprofile::getCountry(){
    return this->country;
}

/*!
 * @brief getdisplayNews: getter method for the displayNews bool.
 *
 * Gets the objects displayNews attribute and returns it to the point at which the method was called
 * @return Boolean of objects displayNews attribute
 */
bool newsprofile::getdisplayNews(){
    return this->displayNews;
}

/*!
 * @brief JsonData: getter function of myJsonData.
 *
 * function call returns myJsonData of type QJsonObject to where it was called from
 * @return returns myJsonData object
 */
QJsonObject newsprofile::JsonData() const{
    return m_JsonData;
}

/*!
 * @brief setJsonData: setter method for the myJsonData.
 *
 * function call sets the QJsonObject myJsonData to the parameter data
 * @param data: QJsonObject to set the object myJsonData to
 */
void newsprofile::setJsonData(const QJsonObject &data){
    m_JsonData = data;
    emit dataChanged(m_JsonData);
}


/*!
 * @brief restApiRequest: creates the api call request.
 *
 * Creates a QNetwork request and then sets the header and url of the request and uses the manager to finish the request.
 */
void newsprofile::restApiRequest(){

    std::string c = getCountry();
    std::string ctg = getCategory();

    std::cout << c << ctg << std::endl;
    std::string u1 = "http://newsapi.org/v2/top-headlines?country=";
    u1 += c;
    u1 += "&category=";
    u1 += ctg;
    u1 += "&apiKey=49f16836a5bd4e9597f06c723c8a8f9f";
    std::cout << u1 << std::endl;

    QString qstr = QString::fromStdString(u1);
    QNetworkRequest request;
    QUrl url;
    url = (qstr);

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
 */
void newsprofile::onRestApiFinished(QNetworkReply *reply){
    QJsonDocument jsdoc = QJsonDocument::fromJson(reply->readAll());
    setJsonData(jsdoc.object());
    QByteArray docByteArray = jsdoc.toJson(QJsonDocument::Compact);
    qDebug() << QLatin1String(docByteArray);
}


/*!
 * @brief createNewsGui: creates the pop up window that displays the NewsProfile Gui.
 *
 * Creates a QCoreApplication, QGuiApplication from the parameterss, a QQmlApplicationEngine that allows for variables
 * to be passed into the qml files to be used to check if elements are to be displayed, a QQmlContext and sets it to the appbridge
 * so that c++ classes are exposed to the qml, creates the connection to the newsprofile.qml to load in the
 * Gui window.
 * @param argc: int arg used to create QGuiApplication
 * @param argv: char arg used to create QGuiApplication
 */
void newsprofile::createNewsGui(int argc, char *argv[]) {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;
        QQmlContext* ctx = engine.rootContext();
        ctx -> setContextProperty("appBridge", this);

        const QUrl url(QStringLiteral("qrc:/newsprofile.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl){
            if (!obj && url == objUrl){
                QCoreApplication::exit(-1);
            }
        }, Qt::QueuedConnection);
        engine.load(url);
        app.exec();

}
