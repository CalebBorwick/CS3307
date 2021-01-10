import QtQuick 2.0

Rectangle {
    //defualt properties
    property string dayOfWeek: " "
    property string tempMin: ""
    property string tempMax: ""
    property string wind: null
    property string precip: null
    property bool lineVisable: true
    property real scaleFactor: 1.0

    color: "transparent"

    //sets the icon to be used
    function setIcon(value){
        imgWeather.source = "qrc:/weatherModuleImages/"+value+".png"
    }
    //text styling for the day of the week
    Text {
        id: txtDayOfWeek
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: imgWeather.top
        anchors.bottomMargin: 10
        color: "white"
        font.bold: true
        font.pointSize: 12
        text: dayOfWeek
    }
    //styling for the images used
    Image{
        id:imgWeather
        anchors.centerIn: parent
        source: "qrc:/weatherModuleImages/1.png"
        scale: scaleFactor
    }
    //styling for the temperature
    Rectangle{
        id:rectTemperature
        height: 35
        width: parent.width
        anchors.top: imgWeather.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"
        //styling for the min temperature
        Text{
            id: txtTempMin
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            color:"#3ECDFD"
            font.bold: true
            font.pointSize: 13
            text: tempMin
        }
        //styling for the max temperature
        Text{
            id: txtTempMax
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            color:"#FB5255"
            font.bold: true
            font.pointSize: 13
            text: tempMax
        }
        //styling for the wind information
        Text{
            id:txtwind
            anchors.top: txtTempMax.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            font.pointSize: 10
            text: wind
        }
        //styling for the precipitation information
        Text{
            id:txtPrecipe
            anchors.top: txtwind.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            font.pointSize: 10
            text: precip
        }

    }
    //styling for spacer
    Rectangle{
        id:verticleLine
        height: parent.height - 30
        width:1
        anchors.right: parent.right
        border.width: 1
        border.color: "white"
        visible: lineVisable
    }

}
