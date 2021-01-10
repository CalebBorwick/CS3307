#include "searchbox.h"
#include "ui_searchbox.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QObject>
#include <QGuiApplication>
#include <QtNetwork/QNetworkReply>
#include <QObject>
#include <QVariant>
#include <QTextStream>
#include <QRegularExpression>
#include <QJsonValue>
#include <iostream>


/*!
 * @brief searchBox: constructor for searchBox class creates an object of type searchBox.
 *
 * Creates an object of type searchBox with the input parameters being set as the class attributes
 * @param parent: A nullptr for the QWidget parent to establish it
 * @param query: A string that stores the users search query
 * @param location: A string containing a key that represents the location of the user
 * @return object of type searchBox
 */
std::searchBox::searchBox(QWidget *parent, QString query, QString location) : QMainWindow(parent), ui(new Ui::searchBox)
{
    ui->setupUi(this);
    /*!< attributes for the location class*/
    this -> location = location;
    this -> query= query;

}

/*!
 * @brief ~searchBox: destructor for searchBox Class.
 *
 * Destructor for the searchBox class objects
 */
std::searchBox::~searchBox()
{
    delete ui;
}

/*!
 * @brief on_searchButton_clicked: on click of search button sends API call
 *
 * Using the users input search query, sends completed API call to retrieve
 * resutls.
 *
 */
void std::searchBox::on_searchButton_clicked()
{
    ui->listWidget->clear();
    QString entry = ui->lineEdit->text();
    QUrl url = getUrl(entry);
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    connect(man, &QNetworkAccessManager::finished, this, &searchBox::setApiFinished);
    QNetworkRequest request(url);
    man->get(request);

}

/*!
 * @brief on_lineEdit_returnPressed: on press of return key sends API call
 *
 * Using the users input search query, sends completed API call to retrieve
 * resutls.
 *
 */
void std::searchBox::on_lineEdit_returnPressed()
{
    ui->listWidget->clear();
    QString entry = ui->lineEdit->text();
    QUrl url = getUrl(entry);
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    connect(man, &QNetworkAccessManager::finished, this, &searchBox::setApiFinished);
    QNetworkRequest request(url);
    man->get(request);
}


/*!
 * @brief setApiFinished: sets the QJsonDocument from the request.
 *
 * Creates a QJsonDocument and reads in the information retrieved by the API call
 * then reads from document and appends results to list in window.
 *
 * @see setDocJsonData()
 * @see setJsonData()
 */
void std::searchBox::setApiFinished(QNetworkReply *reply){
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    setDocJsonData(doc);

    /*!< beginning of loop to iterate through each json entry, each iteration having its own values for the same variables */
    for (int i = 0; i < 5; ++i) {
        QJsonValue out = doc[i];
        QString asString = sprintJson(out);
        QString city = "";
        QString country = "";
        QString region = "";
        int hits = 0;

        /*!< search through full string for city, country, and region names */
        for (int j = 0; j < asString.length(); ++j) {
            if (asString[j] == "a") {
                if (asString[j+1] == "m"){
                    if (asString[j+2] == "e"){
                        int n = j+7;
                        while (asString[n] != "\"") {
                            if (hits == 0){
                                region = region + asString[n];
                            }
                            if (hits == 1){
                                country = country + asString[n];
                            }
                            if (hits == 2){
                                city = city + asString[n];
                            }
                            n++;
                        }
                        hits = hits + 1;
                        if (hits == 3)break;
                    }
                }
            }
        }
    ui->listWidget->addItem(QString::number(i+1) + ". " + city + ", " + country + ", " + region);
    }

}

/*!
 * @brief getUrl: gets the QUrl for the Api call.
 *
 * Gets the QUrl based on the users search query.
 * @param text: users search query to send to API.
 * @return QUrl object with the search results
 */
QUrl std::searchBox::getUrl(QString text){
    QString urlBase = "http://dataservice.accuweather.com/locations/v1/cities/autocomplete";
    QString query = "?q=";
    QString key = "&apikey=GGLtqaMaaToS7PHYbWjBPibNwhT6OAOa";
    QString combine = urlBase+query+text+key;
    QUrl url(combine);
    return url;
};


/*!
 * @brief sprintJson: uses the json document for the json parser
 *
 * Formats the json document to feed to the json parser to allow
 * for it to be read as a string.
 * @param jsonValue: the jsonValue from the API's returned json file.
 * @return Full QString of the jsonValue it received.
 */
QString std::searchBox::sprintJson(const QJsonValue& jsonValue) {
    QString jsonString;

    QTextStream out(&jsonString);
    jsonParser(out, jsonValue, 0);
    return jsonString;
}


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
void std::searchBox::jsonParser(T& stream, const QJsonValue& entry, int indentLevel)    {
    /*!< establishing the various types of punctuation and symbols in the json file >*/
    static const QString indent{QStringLiteral("  ")};
    static const QString slashN{QStringLiteral("\n")};
    static const QString commaSlashN{QStringLiteral(",\n")};
    static const QString openBraceSlashN{QStringLiteral("{\n")};
    static const QString openSquareSlashN{QStringLiteral("[\n")};
    static const QString closeBrace{QStringLiteral("}")};
    static const QString closeSquare{QStringLiteral("]")};
    static const QString doubleQuote{QStringLiteral("\"")};
    static const QString doubleQuoteColon{QStringLiteral("\": ")};
    static const QString null{QStringLiteral("null")};

    QString whiteSpace(indent.repeated(indentLevel));

    /*!< cases to allow for parser to switch between data types >*/
    switch(entry.type()) {
        case QJsonValue::Object:
        {
            stream << openBraceSlashN;
            QJsonObject o = entry.toObject();
            const QStringList& keys = o.keys();
            int lastIndex = keys.count() - 1;
            for(int i = 0; i <= lastIndex; ++i) {
                stream << whiteSpace << indent << doubleQuote << keys.at(i) << doubleQuoteColon;
                jsonParser(stream, o.value(keys.at(i)), indentLevel + 1);
                stream << (Q_UNLIKELY(i == lastIndex) ? slashN : commaSlashN);
            }
            stream << whiteSpace << closeBrace;
            return;
        }

        case QJsonValue::String:
        {
            QString s = entry.toVariant().toString();
                // check for control characters inside string using this regex : [\b\f\n\r\t\"\\]*
                if(s.contains(QRegularExpression("[\\b\\f\\n\\r\\t\\\"\\\\]*"))) { // to-do: this is gonna be real slow. find an optimal solution
                    // escape the control characters inside the string
                    s.replace('\\', "\\\\")
                            .replace('\b', "\\b")
                            .replace('\f', "\\f")
                            .replace('\n', "\\n")
                            .replace('\r', "\\r")
                            .replace('\t', "\\t")
                            .replace('\"', "\\\"")
                            ;

                }
                stream << doubleQuote << s << doubleQuote;
            }
            return;
        }

}


/*!
 * @brief JsonData: getter function of resultJsonData.
 *
 * function call returns resultJsonData of type QJsonObject to where it was called from
 * @return returns resultJsonData object
 */
QJsonObject std::searchBox::JsonData() const{
    return resultJsonData;
}

/*!
 * @brief setJsonData: setter method for the resultJsonData.
 *
 * function call sets the QJsonObject resultJsonData to the parameter data
 * @param data: QJsonObject to set the object resultJsonData to
 */
void std::searchBox::setJsonData(const QJsonObject &data){
    resultJsonData = data;
}

/*!
 * @brief getDocJsonData: getter function of DocJsonData.
 *
 * function call returns resultJsonData in document form of type QJsonDocument to where it was called from
 * @return returns resultJsonData object in as document type
 */
QJsonDocument std::searchBox::getDocJsonData() const{
    return docJsonData;
}

/*!
 * @brief setDocJsonData: setter method for the Json Data in document form.
 *
 * function call sets the QJsonDocument from resultJsonData to the parameter data
 * @param data: QJsonDocument to set the document of the Json Data
 */
void std::searchBox::setDocJsonData(QJsonDocument data){
    docJsonData = data;
}

/*!
 * @brief on_cancelButton_pressed: destructor for searchBox class
 */
void std::searchBox::on_cancelButton_pressed()
{
    delete ui;
}

/*!
 * @brief on_confirmButton_clicked: sets the location key from user selection.
 *
 * Allows user to confirm selection for location choice.
 */
void std::searchBox::on_confirmButton_clicked()
{
    /*!< variables to allow for the location value to be changed */
    int row = ui->listWidget->currentRow();
    QJsonDocument doc = getDocJsonData();
    QString key = "";
    QJsonValue out = doc[row];
    QString asString = sprintJson(out);

    /*!< search through full string for city key */
    for (int j = 0; j < asString.length(); ++j) {
        if (asString[j] == "K") {
            if (asString[j+1] == "e"){
                if (asString[j+2] == "y"){
                    int n = j+7;
                    while (asString[n] != "\"") {
                        key = key + asString[n];
                        n++;
                    }
                }
            }
        }
    }


    setLocation(key);
}

/*!
 * @brief getLocation: getter method for the location string.
 *
 * Gets the objects location attribute and returns it to the point at which the method was called
 * @return string of objects location attribute
 */
QString std::searchBox::getLocation() {
    return this->location;
}

/*!
 * @brief setLocation: setter method for location string.
 *
 * Sets the object location to the parameter passed in to change the users location
 * @param displayWeather: A string used to change the location
 */
void std::searchBox::setLocation(QString location){
    this->location = location;
}
