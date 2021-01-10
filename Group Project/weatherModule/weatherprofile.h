#ifndef WEATHERPROFILE_H
#define WEATHERPROFILE_H

#include <string>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
namespace std {

/*!
 * @brief The WeatherProfile class: class containing all functions nessisary for the weatherProfile.
 *
 * The weatherProfile class contains the getters and setters for all parameters as well as a constructor and destructor
 * for making and destorying objects of type weatherProfile as well as the apicall and QtNework information for
 * getting and requesting information from an api. The class also contains the function to create a gui to display
 * the weather information recieved from the api call
 * @author Ian Borwick
 *
 */
class WeatherProfile : public QObject
{
    /*!
     * @brief defines the Q_object and its properties to be used in the qml
     */

    Q_OBJECT
    Q_PROPERTY(QJsonObject JsonData READ JsonData WRITE setJsonData NOTIFY dataChanged)
    Q_PROPERTY(bool units READ getUnits)
    Q_PROPERTY(bool week READ getWeek)
    Q_PROPERTY(bool details READ getDetails)

private:

    /*!
     * @brief class attributes for objects of type WeatherProfile
     */
    QJsonObject myJsonData; /*!< QJsonObject stores the value of the api call in myJsonData */
    bool displayWeather; /*!< bool stores the value of displayWeather if true */
    int location; /*!< int stores the integer value of the users city to be used in api call */
    bool units;/*!< bool stores the value for the type opf unit to be displayed */
    bool details; /*!< bool stores the value of details if they are to be displayed */
    bool week; /*!< bool stores the value of week if the forecast is 1day or 5day*/
    //Position position;

public:

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
    explicit WeatherProfile(QObject *parent = nullptr, bool displayWeather =true, int location =55489,
            bool units = true, bool details=true, bool week=true);
    
    /*!
     * @brief ~WeatherProfile: destructor for WeatherProfile Class.
     *
     * Destructor for the weatherProfile class objects
     */
    ~WeatherProfile();

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
     * @brief setDisplayWeather: setter method for displayWeather bool.
     *
     * Sets the object displayWeather to the parameter passed in to change weather or not the weather data will be displayed
     * @param displayWeather: A boolean used to change the displayWeather
     */
    void setDisplayWeather(bool displayWeather);

    /*!
     * @brief getDisplayWeather: getter method for the displayWeather bool.
     *
     * Gets the objects displayWeather attribute and returns it to the point at which the method was called
     * @return Boolean of objects displayWeather attribute
     */
    bool getDisplayWeather();

    /*!
     * @brief getLocation: setter method for location int.
     *
     * Sets the object location to the parameter passed in to change the users location
     * @param displayWeather: A int used to change the location
     */
    void setLocation(int location);

    /*!
     * @brief getLocation: getter method for the location int.
     *
     * Gets the objects location attribute and returns it to the point at which the method was called
     * @return int of objects location attribute
     */
    int getLocation();

    /*!
     * @brief getUnits: getter method for the units bool.
     *
     * Gets the objects units attribute and returns it to the point at which the method was called
     * @return bool of objects units attribute
     */
    bool getUnits();


    /*!
     * @brief setUnits: setter method for location int.
     *
     * Sets the object units to the parameter passed in to change if the units will be celcius or fahrenheit
     * @param units: A bool used to change the unit type
     */
    void setUnits(bool unit);

    /*!
     * @brief getDetails: getter method for the detilas bool.
     *
     * Gets the objects details attribute and returns it to the point at which the method was called.
     * @return bool of object details
     */
    bool getDetails();

    /*!
     * @brief setDetails: setter method for the details bool.
     *
     * Sets the objects details attribute if true details will be shown if false details will not be shown.
     * @param details: a bool used to turn on and off the details on the GUI
     */
    void setDetails(bool details);

    /*!
     * @brief getWeek: getter method for the the week bool.
     *
     * Gets the objects week attribute and returns it to the location it was called from.
     * @return bool of week attribute
     */
    bool getWeek();

    /*!
     * @brief setWeek: setter method for week bool.
     *
     * Sets the objects week attribute if true then the 5day foprcast will be shown if false then
     * the 1 day forcast will be shown.
     * @param week: a bool used the change the forecast from 1 day to 5 day
     */
    void setWeek(bool week);

    /*!
     * @brief getUrl: gets the QUrl for the Api call.
     *
     * Gets the QUrl based on the if the units are to be celsius or ferenheit.
     * @see getUnits()
     * @return QUrl object with the proper metric for units
     */
    QUrl getUrl();

    /*!
     * @brief createWeatherGui: creates the pop up window that displays the weatherProfile Gui.
     *
     * Creates a QCoreApplication, QGuiApplication from the parameterss, a QQmlApplicationEngine that allows for variables
     * to be passed into the qml files to be used to check if elements are to be displayed, a QQmlContext and sets it to the appbridge
     * so that c++ classes are exposed to the qml, creates the connection to the weathGui.qml to load in the
     * Gui window.
     * @param argc: int arg used to create QGuiApplication
     * @param argv: char arg used to create QGuiApplication
     */
    void createWeatherGui(int argc, char *argv[]);

    /*!
     * @brief getUserInput: gets the user input to change parameters from default.
     *
     * Gets the user input to allow for the user to turn on and off features of the weatherProfile Gui,
     * based on user input setter methods are called to change display data.
     */
    void getUserInput();

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
         * Creates a QNetwork request and calls the getUrl function in order to get the proper url to be used
         * then sets the header and url of the request and uses the manager to finish the request.
         * @see getUrl()
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


}

#endif // WeatherProfile_H
