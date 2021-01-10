#ifndef LUNARPROFILE_H
#define LUNARPROFILE_H
#include <string>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

namespace std {

/*!
 * @brief The LunarProfile class: class containing all functions nessisary for the LunarProfile.
 *
 * The LunarProfile class contains the getters and setters for all parameters as well as a constructor and destructor
 * for making and destorying objects of type LunarProfile as well as the apicall and QtNework information for
 * getting and requesting information from an api. The class also contains the function to create a gui to display
 * the lunar phase information recieved from the api call
 * @author Ian Borwick
 *
 */
class LunarProfile : public QObject
{
    /*!
    * @breif defines the Q_object and its properties to be used in the qml
    */
    Q_OBJECT
    Q_PROPERTY(QJsonObject JsonData READ JsonData WRITE setJsonData NOTIFY dataChanged)
private:
    /*!
     * @brief class attributes for objects of type LunarProfile
     */
    QJsonObject myJsonData;
    bool displayLunarPhase;
    int location;

public:
    /*!
     * @brief LunarProfile: constructor for LunarProfile class creates an object of type LunarProfile.
     *
     * Creates an object of type LunarProfile with the input parameters being set as the class attributes
     * @param parent: A nullptr for the Qobject parent to establish it
     * @param displayLunar: a bool to decide if the lunarphase gui will be displayed
     * @param location: an int representing the location to be used in the api call
     */
    explicit LunarProfile(QObject *parent = nullptr, bool displayLunar =true, int location =55489);

    /*!
    * @brief ~LunarProfile: destructor for LunarProfile Class.
    *
    * Destructor for the LunarProfile class objects
    */
    ~LunarProfile();

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
     * @brief getDisplayLunarPhase: getter method for the displayLunarPhase bool.
     *
     * Gets the objects displayLunarPhase attribute and returns it to the location it was called from
     * @return boolean of objects displayLunarPhase attribute
     */
    bool getDisplayLunarPhase();

    /*!
     * @brief setDisplayLunarPhase: setter method for displayLunarPhase bool.
     *
     * Sets the objects displayLunarPhase attribute
     * if true the lunarPhase Gui will be shown
     * if false it will not be
     * @param lunarPhase: a boolean used to change the value of displayLunarPhase
     */
    void setDisplayLunarPhase(bool lunarPhase);

    /*!
     * @brief getLocation: getter method for the location int.
     *
     * Gets the objects location attribute and returns it to the location it was called from
     * @return int of objects location attribute
     */
    int getLocation();

    /*!
     * @brief setLocation: setter method for location int.
     *
     * Sets the objects location attribute
     * used in the api call
     * @param loc: an int used to change the value of location
     */
    void setLocation(int loc);

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
    void createLunarPhaseGui(int argc, char *argv[]);

    /*!
    * @brief getUserInput: gets the user input to change parameters from default.
    *
    * Gets the user input to allow for the user to turn on and off features of the lunarProfile Gui,
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
         * @param QNetworkReply*: network reply object used to get the api information
         */
        void onRestApiFinished(QNetworkReply*);

};
}

#endif // LUNARPROFILE_H
