#ifndef GREETINGS_H
#define GREETINGS_H

#include <string>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

/*!
 * @brief The greetings class: class containing all functions nessisary for the greetings.
 *
 * The greetings class contains a constructor and destructor for making and destorying objects of type greetings
 * as well as the apicall and QtNework information for getting and requesting information from an api.
 * The class also contains the function to create a gui to display
 * the greetings and motivational quote information recieved from the api call
 * @author Seyedehnastaran Ghafouriansahraei
 *
 */
class greetings : public QObject
{
    /*!
     * @breif defines the Q_object and its properties to be used in the qml
     */

    Q_OBJECT
    Q_PROPERTY(QJsonObject JsonData READ JsonData WRITE setJsonData NOTIFY dataChanged)

private:
    QJsonObject m_JsonData; /*!< QJsonObject stores the value of the api call in m_JsonData */

public:
   /*!
    * @brief WeatherProfile: constructor for greetings class creates an object of type greetings.
    *
    * Creates an object of type greetings
    * @return object of type greetings
    */
    explicit greetings(QObject *parent = nullptr);

   /*!
    * @brief ~WeatherProfile: destructor for WeatherProfile Class.
    *
    * Destructor for the weatherProfile class objects
    */
    ~greetings();


   /*!
    * @brief JsonData: getter function of myJsonData.
    *
    * function call returns myJsonData of type QJsonObject to where it was called from
    * @return returns myJsonData object
    */
    QJsonObject JsonData() const;

   /*!
    * @brief setJsonData: setter method for the myJsonData.
    *
    * function call sets the QJsonObject myJsonData to the parameter data
    * @param data: QJsonObject to set the object myJsonData to
    */
    void setJsonData(const QJsonObject& data);

   /*!
    * @brief manager creates a new object manager of type QNetworkManager.
    *
    * manger is used to make and request the api calls used in populating myJsonData.
    * @see dataChanged()
    */
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

   /*!
    * @brief createGreetingsGui: creates the pop up window that displays the Greetings Gui.
    *
    * Creates a QCoreApplication, QGuiApplication from the parameterss, a QQmlApplicationEngine that allows for variables
    * to be passed into the qml files to be used to check if elements are to be displayed, a QQmlContext and sets it to the appbridge
    * so that c++ classes are exposed to the qml, creates the connection to the weathGui.qml to load in the
    * Gui window.
    * @param argc: int arg used to create QGuiApplication
    * @param argv: char arg used to create QGuiApplication
    */
    void createGreetingsGui(int argc, char *argv[]);

    signals:

       /*!
        * @brief dataChanged: singal for if the QJsonObject is changed.
        *
        * if the QJsonObject is changed send the singal to allow for the data to be loaded in again with
        * the updated data.
        */
        void dataChanged(QJsonObject);


    public slots:

       /*!
        * @brief restApiRequest: creates the api call request.
        *
        * Creates a QNetwork request and then sets the header and url of the request and uses the manager to finish the request.
        */
        void restApiRequest();

       /*!
        * @brief onRestApiFinished: sets the QJsonDocument from the request.
        *
        * Creates a QJsonDocument and reads in the information retrived by the restApiRequest function
        * then calls the setJsonData function to save the information in and object and loads it into a QByteArray.
        *
        * @see restApiRequest()
        * @see setJsonData()
        */
        void onRestApiFinished(QNetworkReply*);
};

#endif // GREETINGS_H
