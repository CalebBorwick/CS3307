#include "greetings.h"
#include <QJsonArray>
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
 * @brief greetings: constructor for greetings class creates an object of type greetings.
 *
 * Creates an object of type greetings
 * @param parent: A nullptr for the Qobject parent to establish it
 * @return object of type greetings
 */
greetings::greetings(QObject *parent) : QObject(parent) {

    QObject::connect(manager, &QNetworkAccessManager::finished, this, &greetings::onRestApiFinished);
}

/*!
 * @brief ~greetings: destructor for greetings Class.
 *
 * Destructor for the greetings class objects
 */
greetings::~greetings() {}

/*!
 * @brief JsonData: getter function of myJsonData.
 *
 * function call returns myJsonData of type QJsonObject to where it was called from
 * @return returns myJsonData object
 */
QJsonObject greetings::JsonData() const{
    return m_JsonData;
}

/*!
 * @brief setJsonData: setter method for the myJsonData.
 *
 * function call sets the QJsonObject myJsonData to the parameter data
 * @param data: QJsonObject to set the object myJsonData to
 */
void greetings::setJsonData(const QJsonObject &data){
    m_JsonData = data;
    emit dataChanged(m_JsonData);
}

/*!
 * @brief restApiRequest: creates the api call request.
 *
 * Creates a QNetwork request using a given url for motivational quotes API
 * then sets the header and url of the request and uses the manager to finish the request.
 */
void greetings::restApiRequest(){

    QNetworkRequest request;
    QUrl url;
    url = ("https://zenquotes.io/api/random");
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
void greetings::onRestApiFinished(QNetworkReply *reply){
    QJsonDocument jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonArray arr = jsdoc.array();
    QJsonObject obj{
        {"quotes", arr},
        {"name", "Bob"}
    };
    setJsonData(obj);
    QByteArray docByteArray = jsdoc.toJson(QJsonDocument::Compact);
    qDebug() << QLatin1String(docByteArray);
}


/*!
 * @brief createGreetingsGui: creates the pop up window that displays the Greetings Gui.
 *
 * Creates a QCoreApplication, QGuiApplication from the parameterss, a QQmlApplicationEngine that allows for variables
 * to be passed into the qml files to be used to check if elements are to be displayed, a QQmlContext and sets it to the appbridge
 * so that c++ classes are exposed to the qml, creates the connection to the greetings.qml to load in the
 * Gui window.
 * @param argc: int arg used to create QGuiApplication
 * @param argv: char arg used to create QGuiApplication
 */
void greetings::createGreetingsGui(int argc, char *argv[]) {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;
        QQmlContext* ctx = engine.rootContext();
        ctx -> setContextProperty("appBridge", this);

        const QUrl url(QStringLiteral("qrc:/greetings.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl){
            if (!obj && url == objUrl){
                QCoreApplication::exit(-1);
            }
        }, Qt::QueuedConnection);
        engine.load(url);
        app.exec();

}
