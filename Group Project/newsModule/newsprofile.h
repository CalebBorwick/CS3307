#ifndef NEWSPROFILE_H
#define NEWSPROFILE_H

#include <string>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

/*!
 * @brief The newsprofile class: class containing all functions nessisary for the newsprofile.
 *
 * The newsprofile class contains the getters and setters for all parameters as well as a constructor and destructor
 * for making and destorying objects of type weatherProfile as well as the apicall and QtNework information for
 * getting and requesting information from an api. The class also contains the function to create a gui to display
 * the weather information recieved from the api call
 * @author Seyedehnastaran Ghafouriansahraei
 *
 */
class newsprofile : public QObject
{
   /*!
    * @breif defines the Q_object and its properties to be used in the qml
    */
    Q_OBJECT
    Q_PROPERTY(QJsonObject JsonData READ JsonData WRITE setJsonData NOTIFY dataChanged)

private:

   /*!
    * @brief class attributes for objects of type WeatherProfile
    */
    QJsonObject m_JsonData;


    std::string category; /*!< string stores the string value of the news category to be used in api call */
    std::string country; /*!< string stores the string value of the news country to be used in api call */
    bool displayNews; /*!< bool stores the value of displayNews if true */

public:

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
    explicit newsprofile(QObject *parent = nullptr, bool displayNews=true, std::string c="ca", std::string ctg="business");

   /*!
    * @brief ~newsprofile: destructor for newsprofile Class.
    *
    * Destructor for the newsprofile class objects
    */
    ~newsprofile();


   /*!
    * @brief setCategory: setter method for category string.
    *
    * Sets the object category to the parameter passed in to use in news API
    * @param ctg: A string used to change the category
    */
    void setCategory(std::string ctg);


   /*!
    * @brief setCountry: setter method for country string.
    *
    * Sets the object country to the parameter passed in to use in news API
    * @param c: A string used to change the country
    */
    void setCountry(std::string c);


   /*!
    * @brief setdisplayNews: setter method for displayNews bool.
    *
    * Sets the object displayNews to the parameter passed in to change weather or not the news data will be displayed
    * @param d: A boolean used to change the displayNews
    */
    void setdisplayNews(bool d);


   /*!
    * @brief getCategory: getter method for the category string.
    *
    * Gets the objects category attribute and returns it to the point at which the method was called
    * @return string of objects category attribute
    */
    std::string getCategory();

    /*!
    * @brief getCountry: getter method for the country string.
    *
    * Gets the objects country attribute and returns it to the point at which the method was called
    * @return string of objects country attribute
    */
    std::string getCountry();

   /*!
    * @brief getdisplayNews: getter method for the displayNews bool.
    *
    * Gets the objects displayNews attribute and returns it to the point at which the method was called
    * @return Boolean of objects displayNews attribute
    */
    bool getdisplayNews();

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
    * @brief createNewsGui: creates the pop up window that displays the NewsProfile Gui.
    *
    * Creates a QCoreApplication, QGuiApplication from the parameterss, a QQmlApplicationEngine that allows for variables
    * to be passed into the qml files to be used to check if elements are to be displayed, a QQmlContext and sets it to the appbridge
    * so that c++ classes are exposed to the qml, creates the connection to the newsprofile.qml to load in the
    * Gui window.
    * @param argc: int arg used to create QGuiApplication
    * @param argv: char arg used to create QGuiApplication
    */
    void createNewsGui(int argc, char *argv[]);


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

#endif // NEWSPROFILE_H
