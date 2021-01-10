import QtQuick 2.9
import QtQuick.Window 2.2
//creates window
Window {
    visible: true
    width: 800
    height: 500
    //creates basic clock at top
    Timer{
        interval: 100
        running: true
        repeat: true
        onTriggered: {
            var time = Qt.formatDateTime(new Date(), "h:mm a")
            var date = Qt.formatDateTime(new Date(), "dddd dd MMMM")
        }
    }
    //creates box and styling for the date and time
    Rectangle{
        id:rectDateTime
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        color: "#008ADE"
        //styling for the time
        Rectangle{
            id:rectTime
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 30
            height: 100
            width: parent.width
            color: "transparent"
            //fills in default time

        }
        //creates box and styling for the date
        Rectangle{
            id:rectDate
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: rectTime.bottom
            width: parent.width
            height: 60
            color: "transparent"

        }
       //styling for weather today
        ItemWeather{
            id:weather0
            height: 130
            width:150
            anchors.top: rectDate.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            scaleFactor: 1.8
            lineVisable: false

        }
        //creates and styles box to hold week weather data
        Rectangle{
            width: parent.width *0.9
            height:140
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            color: "transparent"

            //creates a horizontal divider line between todays weather and weeks weather
            Rectangle{
                id:horizontalLine
                height:1
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                border.width: 1
                border.color: "white"
            }
            //styling for weather day 1
            ItemWeather{
                id:weather1
                width: parent.width*0.25
                height: parent.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                dayOfWeek: qsTr("Monday")
                lineVisable: false
            }
            //styling for weather day 1
            ItemWeather{
                id:weather2
                width: parent.width*0.25
                height: parent.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: weather1.right
                dayOfWeek: qsTr("Tuesday")
                lineVisable: false
            }
            //styling for weather day 1
            ItemWeather{
                id:weather3
                width: parent.width*0.25
                height: parent.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: weather2.right
                dayOfWeek: qsTr("Wednesday")
                lineVisable: false
            }
            //styling for weather day 1
            ItemWeather{
                id:weather4
                width: parent.width*0.25
                height: parent.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: weather3.right
                dayOfWeek: qsTr("Thursday")
                lineVisable: false
            }
        }

    }
    //invisable button to do the http request
    Rectangle
    {
        id: btnrequest
        width:parent.width
        height:parent.height
        anchors.top:parent.top
        anchors.right: parent.right
        color:"transparent"

        MouseArea{
            anchors.fill: parent
            onClicked: {
                appBridge.restApiRequest();
            }
        }
    }
    //establishes connection to c++ variables
    Connections{
        target: appBridge
        onDataChanged:
        {
            //pulls in the variables for details and week to see if they will be displayed
            var details = appBridge.details;
            var week = appBridge.week;


            //fills in the day of week, units, temp min and max for weather 0
            var date = new Date(appBridge.JsonData.DailyForecasts[0].EpochDate *1000);
            weather0.dayOfWeek = Qt.formatDate(date, "dddd");
            weather0.tempMin=appBridge.JsonData.DailyForecasts[0].Temperature.Minimum.Value + " °" + appBridge.JsonData.DailyForecasts[0].Temperature.Maximum.Unit;
            weather0.tempMax=appBridge.JsonData.DailyForecasts[0].Temperature.Maximum.Value + " °" + appBridge.JsonData.DailyForecasts[0].Temperature.Maximum.Unit;

            if(week){//if week is true then display 5 day
                //fills in the day of week, units, temp min and max for weather 1
                date = new Date(appBridge.JsonData.DailyForecasts[1].EpochDate *1000);
                weather1.dayOfWeek = Qt.formatDate(date, "dddd");
                weather1.tempMin=appBridge.JsonData.DailyForecasts[1].Temperature.Minimum.Value + " °" + appBridge.JsonData.DailyForecasts[1].Temperature.Minimum.Unit;
                weather1.tempMax=appBridge.JsonData.DailyForecasts[1].Temperature.Maximum.Value + " °" + appBridge.JsonData.DailyForecasts[1].Temperature.Maximum.Unit;

                //fills in the day of week, units, temp min and max for weather 2
                date = new Date(appBridge.JsonData.DailyForecasts[2].EpochDate *1000);
                weather2.dayOfWeek = Qt.formatDate(date, "dddd");
                weather2.tempMin=appBridge.JsonData.DailyForecasts[2].Temperature.Minimum.Value + " °" + appBridge.JsonData.DailyForecasts[2].Temperature.Maximum.Unit;
                weather2.tempMax=appBridge.JsonData.DailyForecasts[2].Temperature.Maximum.Value + " °" + appBridge.JsonData.DailyForecasts[2].Temperature.Maximum.Unit;

                //fills in the day of week, units, temp min and max for weather 3
                date = new Date(appBridge.JsonData.DailyForecasts[3].EpochDate *1000);
                weather3.dayOfWeek = Qt.formatDate(date, "dddd");
                weather3.tempMin=appBridge.JsonData.DailyForecasts[3].Temperature.Minimum.Value + " °" + appBridge.JsonData.DailyForecasts[3].Temperature.Maximum.Unit;
                weather3.tempMax=appBridge.JsonData.DailyForecasts[3].Temperature.Maximum.Value + " °" + appBridge.JsonData.DailyForecasts[3].Temperature.Maximum.Unit;

                //fills in the day of week, units, temp min and max for weather 4
                date = new Date(appBridge.JsonData.DailyForecasts[4].EpochDate *1000);
                weather4.dayOfWeek = Qt.formatDate(date, "dddd");
                weather4.tempMin=appBridge.JsonData.DailyForecasts[4].Temperature.Minimum.Value + " °" + appBridge.JsonData.DailyForecasts[4].Temperature.Minimum.Unit;
                weather4.tempMax=appBridge.JsonData.DailyForecasts[4].Temperature.Maximum.Value + " °" + appBridge.JsonData.DailyForecasts[4].Temperature.Maximum.Unit;
            }
            else{ //if week is false changes styling to make it better for single day
                weather0.scale=2;
                weather0.anchors.topMargin=30;
                horizontalLine.height=0;
                //removes day of week text, and sets the image to a blank png
                weather1.dayOfWeek="";
                weather2.dayOfWeek="";
                weather3.dayOfWeek="";
                weather4.dayOfWeek="";
                weather1.setIcon("none");
                weather2.setIcon("none");
                weather3.setIcon("none");
                weather4.setIcon("none");


            }

            //finds current time, sun rise and sun set for given day to see if it is day or night
            var curTime=Qt.formatDateTime(new Date(), "hh:mm")
            var sunrise = new Date(appBridge.JsonData.DailyForecasts[0].Sun.Rise);
            sunrise= Qt.formatDateTime(sunrise, "hh:mm");
            var sunset = new Date(appBridge.JsonData.DailyForecasts[0].Sun.Set);
            sunset = Qt.formatDateTime(sunset, "hh:mm");
            //if it is after sunrise but before sunset to display day time logos
            if(sunrise < curTime & curTime<sunset){
                weather0.setIcon(appBridge.JsonData.DailyForecasts[0].Day.Icon);
                if(week){//if week is true then display 5 day
                    weather1.setIcon(appBridge.JsonData.DailyForecasts[1].Day.Icon);
                    weather2.setIcon(appBridge.JsonData.DailyForecasts[2].Day.Icon);
                    weather3.setIcon(appBridge.JsonData.DailyForecasts[3].Day.Icon);
                    weather4.setIcon(appBridge.JsonData.DailyForecasts[4].Day.Icon);
                }
                if(details){//if details are true to display
                    //displays the wind and precipitation for weather 0
                    weather0.wind = "Wind "+appBridge.JsonData.DailyForecasts[0].Day.Wind.Speed.Value + " km/h"
                    weather0.precip= appBridge.JsonData.DailyForecasts[0].Day.PrecipitationProbability+ "% chance of precipitation"

                    if(week){//if week is true then display 5 day
                        //styles and displayes the weather1 with wind
                        weather1.wind = "Wind "+appBridge.JsonData.DailyForecasts[1].Day.Wind.Speed.Value + " km/h";
                        //styles and displayes the weather2 with wind
                        weather2.wind = "Wind "+appBridge.JsonData.DailyForecasts[2].Day.Wind.Speed.Value + " km/h";
                        //styles and displayes the weather3 with wind
                        weather3.wind = "Wind "+appBridge.JsonData.DailyForecasts[3].Day.Wind.Speed.Value + " km/h";
                        //styles and displayes the weather4 with wind
                        weather4.wind = "Wind "+appBridge.JsonData.DailyForecasts[4].Day.Wind.Speed.Value + " km/h";
                        }
                }

            }
            //adds in night logos if its after sun set
            else{
                weather0.setIcon(appBridge.JsonData.DailyForecasts[0].Night.Icon);
                if(week){//if week is true then display 5 day
                    weather1.setIcon(appBridge.JsonData.DailyForecasts[1].Night.Icon);
                    weather2.setIcon(appBridge.JsonData.DailyForecasts[2].Night.Icon);
                    weather3.setIcon(appBridge.JsonData.DailyForecasts[3].Night.Icon);
                    weather4.setIcon(appBridge.JsonData.DailyForecasts[4].Night.Icon);
                }
                if(details){//if details are true to display
                    //displays the wind and precipitation for weather 0
                        weather0.wind = "Wind "+appBridge.JsonData.DailyForecasts[0].Night.Wind.Speed.Value + " km/h";
                        weather0.precip= appBridge.JsonData.DailyForecasts[0].Night.PrecipitationProbability+ "% chance of precipitation"
                    if(week){//if week is true then display 5 day
                        //styles and displayes the weather1 with wind
                        weather1.wind = "Wind "+appBridge.JsonData.DailyForecasts[1].Night.Wind.Speed.Value + " km/h";
                        //styles and displayes the weather2 with wind
                        weather2.wind = "Wind "+appBridge.JsonData.DailyForecasts[2].Night.Wind.Speed.Value + " km/h";
                        //styles and displayes the weather3 with wind
                        weather3.wind = "Wind "+appBridge.JsonData.DailyForecasts[3].Night.Wind.Speed.Value + " km/h";
                        //styles and displayes the weather4 with wind
                        weather4.wind = "Wind "+appBridge.JsonData.DailyForecasts[4].Night.Wind.Speed.Value + " km/h";
                    }
                }
            }
        }

    }
}
