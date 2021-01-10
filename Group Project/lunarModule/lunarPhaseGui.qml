import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480

    Rectangle{
        id:rectIcon
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
        height: 100
        width: parent.width
        color: "transparent"

        ItemPhase{
            id:lunarPhase0
            height: 130
            width:150
            anchors.top: rectIcon.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            scale: 0.5

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
                   appConnect.restApiRequest();
               }
           }
       }
       //establishes connection to c++ variables
       Connections{
           target: appConnect
           onDataChanged:
           {
               lunarPhase0.setIcon(appConnect.JsonData.DailyForecasts[0].Moon.Phase);
               lunarPhase0.phase = appConnect.JsonData.DailyForecasts[0].Moon.Phase;
           }
       }
}
