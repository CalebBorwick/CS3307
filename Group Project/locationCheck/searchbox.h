#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <string>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QString>
#include <QJsonValue>

namespace Ui {
    class searchBox;
}

namespace std {
    /*!
    * @brief The searchBox class: class containing all functions necessary for the searchBox window.
    *
    * The searchBox class contains the getters and setters for all parameters as well as a constructor and destructor
    * for making and destorying objects of type searchBox as well as the API call and QtNework information for
    * getting and requesting information from an API. The class also contains a parser to process the json file
    * received from the API call.
    * @author Ethan Biswurm
    *
    */
    class searchBox : public QMainWindow {
        /*!
        * @brief defines the object and the properties to be used in the qml
        */

        Q_OBJECT

    signals:

    public:
        /*!
         * @brief searchBox: constructor for searchBox class creates an object of type searchBox.
         *
         * Creates an object of type searchBox with the input parameters being set as the class attributes
         * @param parent: A nullptr for the QWidget parent to establish it
         * @param query: A string that stores the users search query
         * @param location: A string containing a key that represents the location of the user
         * @return object of type searchBox
         */
        explicit searchBox(QWidget *parent = nullptr, QString query = "", QString location = "");
        /*!
         * @brief ~searchBox: destructor for searchBox Class.
         *
         * Destructor for the searchBox class objects
         */
        ~searchBox();

        /*!
         * @brief setLocation: setter method for location string.
         *
         * Sets the object location to the parameter passed in to change the users location
         * @param displayWeather: A string used to change the location
         */
        void setLocation(QString location);

        /*!
         * @brief getLocation: getter method for the location string.
         *
         * Gets the objects location attribute and returns it to the point at which the method was called
         * @return string of objects location attribute
         */
        QString getLocation();
        /*!
         * @brief JsonData: getter function of resultJsonData.
         *
         * function call returns resultJsonData of type QJsonObject to where it was called from
         * @return returns resultJsonData object
         */
        QJsonObject JsonData() const;

        /*!
         * @brief setJsonData: setter method for the resultJsonData.
         *
         * function call sets the QJsonObject resultJsonData to the parameter data
         * @param data: QJsonObject to set the object resultJsonData to
         */
        void setJsonData(const QJsonObject& data);

        /*!
         * @brief getDocJsonData: getter function of DocJsonData.
         *
         * function call returns resultJsonData in document form of type QJsonDocument to where it was called from
         * @return returns resultJsonData object in as document type
         */
        QJsonDocument getDocJsonData() const;

        /*!
         * @brief setDocJsonData: setter method for the Json Data in document form.
         *
         * function call sets the QJsonDocument from resultJsonData to the parameter data
         * @param data: QJsonDocument to set the document of the Json Data
         */
        void setDocJsonData(QJsonDocument data);

        /*!
         * @brief manager: creates a new object manager of type QNetworkManager.
         *
         * manager is used to make and request the api calls used in populating resultJsonData.
         * @see dataChanged()
         */
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        /*!
         * @brief getUrl: gets the QUrl for the Api call.
         *
         * Gets the QUrl based on the users search query.
         * @param text: users search query to send to API.
         * @return QUrl object with the search results
         */
        QUrl getUrl(QString text);

        /*!
         * @brief sprintJson: uses the json document for the json parser
         *
         * Formats the json document to feed to the json parser to allow
         * for it to be read as a string.
         * @param jsonValue: the jsonValue from the API's returned json file.
         * @return Full QString of the jsonValue it received.
         */
        QString sprintJson(const QJsonValue& jsonValue);

        /*!
         * @brief jsonParser: parses jsonValue objects into QStrings
         *
         * Parses the jsonValue merging both items of object and string type
         * into one string.
         * @param stream: the character stream that the parser appends characters to
         * @param entry: the jsonValue received from the sprintJson method.
         * @param indentLevel: the current level of indentation for an iteration. Used for recursion.
         */
        template <typename T>
        void jsonParser(T& stream, const QJsonValue& entry, int indentLevel);

    public slots:
        /*!
         * @brief setApiFinished: sets the QJsonDocument from the request.
         *
         * Creates a QJsonDocument and reads in the information retrieved by the API call
         * then reads from document and appends results to list in window.
         *
         * @see setDocJsonData()
         * @see setJsonData()
         */
        void setApiFinished(QNetworkReply*);

    private slots:
        /*!
         * @brief on_searchButton_clicked: on click of search button sends API call
         *
         * Using the users input search query, sends completed API call to retrieve
         * resutls.
         *
         */
        void on_searchButton_clicked();

        /*!
         * @brief on_lineEdit_returnPressed: on press of return key sends API call
         *
         * Using the users input search query, sends completed API call to retrieve
         * resutls.
         *
         */
        void on_lineEdit_returnPressed();

        /*!
         * @brief on_confirmButton_clicked: sets the location key from user selection.
         *
         * Allows user to confirm selection for location choice.
         */
        void on_confirmButton_clicked();

        /*!
         * @brief on_cancelButton_pressed: destructor for searchBox class
         */
        void on_cancelButton_pressed();

    private:
        QJsonDocument docJsonData; /*!< QJsonDocument stores the document of the api call in docJsonData */
        QJsonObject resultJsonData; /*!< QJsonObject stores the value of the api call in resultJsonData */
        QString location; /*!< String stores the key value of the users city to be used in api call */
        QString query; /*!< String that stores the search query */
        Ui::searchBox *ui;

    };
}

#endif // SEARCHBOX_H
