import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    //creates basic clock at top
       Timer{
           interval: 100
           running: true
           repeat: true
           onTriggered: {
               //set up variables
               var displayDate = appBridge.displayDate;
               var display24Hour = appBridge.display24Hour;
               var displaySeconds =appBridge.displaySeconds;
               var displayAmPm = appBridge.displayAmPm;
               date.text = Qt.formatDateTime(new Date(), "dddd dd MMMM")

               if(displayDate ==false){
                   date.color="transparent"

               }

               if(display24Hour){
                   if(displaySeconds){
                       time.text = Qt.formatDateTime(new Date(), "hh:mm:ss");
                   }
                   else{
                     time.text = Qt.formatDateTime(new Date(), "hh:mm");
                   }

               }
               else{
                   if(displaySeconds){
                       time.text = Qt.formatDateTime(new Date(), "hh:mm:ss");
                   }
                   else{
                     time.text = Qt.formatDateTime(new Date(), "hh:mm");
                   }
               }

               if(displayAmPm){
                   if(displaySeconds){
                       time.text = Qt.formatDateTime(new Date(), "h:mm:ss a");

                   }
                   else {
                     time.text = Qt.formatDateTime(new Date(), "h:mm a");
                   }
               }
               else{
                   if(displaySeconds){
                       time.text = Qt.formatDateTime(new Date(), "h:mm:ss");

                   }
                   else {
                     time.text = Qt.formatDateTime(new Date(), "h:mm");
                   }
               }

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
               Text{
                   id:time
                   text:qsTr("10:20")
                   anchors.centerIn: parent
                   color:"white"
                   font.pointSize: 80
               }
           }
           //creates box and styling for the date
           Rectangle{
               id:rectDate
               anchors.horizontalCenter: parent.horizontalCenter
               anchors.top: rectTime.bottom
               width: parent.width
               height: 60
               color: "transparent"
               //fills in default date
               Text{
                   id:date
                   text:qsTr("April 12 2020")
                   anchors.centerIn: parent
                   color: "white"
                   font.pointSize: 25
               }

           }
       }
}
