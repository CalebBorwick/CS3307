import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.6

Window {
    id: window
    visible: true
    width: 900
    height: 400
    title: qsTr("News")

    Timer {
           id: textTimer
           interval: 50000
           repeat: true
           running: true
           triggeredOnStart: true
           onTriggered: appBridge.restApiRequest();
    }

    Rectangle {
        id: btnrequest
        width:parent.width
        height:parent.height
        anchors.top:parent.top
        anchors.right: parent.right
        color:"transparent"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                appBridge.restApiRequest();
            }

            Text {
                id: news0
                x: 133
                y: 161
                width: 435
                height: 77
                text: qsTr("Text")
                opacity: 1
                font.pixelSize: 14
                font.bold: true
            }

            Text {
                id: news1
                x: 133
                y: 71
                width: 435
                height: 76
                text: qsTr("Text")
                font.pixelSize: 14
                font.bold: true
            }

            Text {
                id: news2
                x: 133
                y: 267
                width: 435
                height: 71
                text: qsTr("Text")
                font.pixelSize: 14
                font.bold: true
            }
        }
    }

    Connections {
            target: appBridge
            onDataChanged:
            {
                if(appBridge.JsonData.message){
                    news0.text = "You have reached your maximum limit of requests to news API.";
                    news1.text = "";
                    news2.text = "";

                }
                else{
                    news0.text = appBridge.JsonData.articles[0].title;
                    news1.text = appBridge.JsonData.articles[1].title;
                    news2.text = appBridge.JsonData.articles[2].title;
                }
            }
        }
}
