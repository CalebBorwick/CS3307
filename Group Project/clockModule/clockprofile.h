#ifndef CLOCKPROFILE_H
#define CLOCKPROFILE_H
#include <string>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
namespace std {

/*!
 * @brief The clockProfile class: class contains all functions necessary for the clockProfile.
 *
 * The clockProfile class conbtains the getters and setters for all parameters as welll as a constructor
 * and destructor for make and destroying objects of type clockProfile. As well it holds the functions
 * to create and diosplay a gui with the all information as well as the ability to change the
 * deafults using getUserInput()
 * @author Ian Borwick
 */
class clockProfile : public QObject
{
    /*! defines the Qobject and its properties to be used in the qml*/
    Q_OBJECT
    Q_PROPERTY(bool displayAmPm READ getDisplayAmPm)
    Q_PROPERTY(bool display24Hour READ getDisplay24Hour)
    Q_PROPERTY(bool displaySeconds READ getDisplaySeconds)
    Q_PROPERTY(bool displayDate READ getDisplayDate)

    /*! private Class attributes */
    private:
        bool displayClock; /*!< bool stores the value for displayClock to see if it will be displayed */
        bool displayAmPm; /*!< bool stores the value for displayAmPm to see if it will be displayed */
        bool display24Hour; /*!< bool stores the value for display24Hour to see if it will be displayed */
        bool displaySeconds; /*!< bool stores the value for displaySeconds to see if it will be displayed */
        bool displayDate; /*!< bool stores the value for displayDate to see if it will be displayed */

    /*! public Class attributes */
    public:
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
         explicit clockProfile(QObject *parent = nullptr, bool displayClock = true, bool displayAmPm =true,bool display24Hour = false, bool displaySeconds = false, bool displayDate = true);

        /*!
          *@brief ~clockProfile: destructor for the clockProfile
          */
        ~clockProfile();

        /*!
        * @brief getDisplayClock: getter function of displayClock bool.
        *
        * function call returns displayClock of type bool to where it was called from
        * @return returns displayClock bool
        */
        bool getDisplayClock();

        /*!
         * @brief setDisplayClock: setter method for the displayClock bool.
         *
         * function call sets the displayClock to the input parameter
         * if true the clock gui will be shown
         * if false it will not be shown
         * @param displayClock: bool to set the displayClock attribute to
         */
        void setDisplayClock(bool displayClock);

        /*!
        * @brief getDisplayAmPm: getter function of displayClock bool.
        *
        * function call returns displayAmPm of type bool to where it was called from
        * @return returns displayAmPm bool
        */
        bool getDisplayAmPm();

        /*!
         * @brief setDisplayAmPm: setter method for the displayAmPm bool.
         *
         * function call sets the displayAmPm to the input parameter
         * if true the Am Pm in the gui will be shown and 24 hour will not
         * if false it will not be shown and 24 hour will be
         * @param displayAmPm: bool to set the displayAmPm attribute to
         */
        void setDisplayAmPm(bool displayAmPm);

        /*!
        * @brief getDisplay24Hour: getter function of display24Hour bool.
        *
        * function call returns displayAmPm of type bool to where it was called from
        * @return returns display24Hour bool
        */
        bool getDisplay24Hour();

        /*!
         * @brief setDisplay24Hour: setter method for the display24Hour bool.
         *
         * function call sets the display24Hour to the input parameter
         * if true the 24 hour in the gui will be shown and AmPm will not
         * if false it will not be shown and AmPm will be
         * @param display24Hour: bool to set the display24Hour attribute to
         */
        void setDisplay24Hour(bool display24Hour);

        /*!
         * @brief getDisplaySeconds: getter method for the displaySeconds bool.
         *
         * function call returns displaySeconds of type bool to where it was called from
         * @param displaySeconds: bool to set the displaySeconds attribute to
         */
        bool getDisplaySeconds();

        /*!
         * @brief setDisplaySeconds: setter method for the displaySeconds bool.
         *
         * function call will set the displaySeconds attribute to the input parameter
         * if true seconds will be shown in the gui
         * if false they will not
         * @param displaySeconds: bool to set the displaySeconds attribute to
         */
        void setDisplaySeconds(bool displaySeconds);

        /*!
         * @brief getDisplayDate: getter method for the displayDate bool.
         *
         * function call returns displayDate of type bool to where it was called from
         * @param displayDate: bool to set the displayDate attribute to
         */
        bool getDisplayDate();

        /*!
         * @brief setDisplayDate: setter method for the displayDate bool.
         *
         * function call will set the displayDate attribute to the input parameter
         * if true date will be shown in the gui
         * if false they will not
         * @param displayDate: bool to set the displayDate attribute to
         */
        void setDisplayDate(bool displayDate);

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
        void createClockGui(int argc, char *argv[]);


        /*!
         * @brief getUserInput: gets the user input to change parameters from default.
         *
         * Gets the user input to allow for the user to turn on and off features of the clockProfile Gui,
         * based on user input setter methods are called to change display data.
         */
        void getUserInput();


    };


}
#endif // CLOCKPROFILE_H
