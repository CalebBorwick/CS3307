import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.6

Window {
    id: window
    visible: true
    width: 900
    height: 400
    title: qsTr("Greetings")

    Timer {
           id: textTimer
           interval: 50000000
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
                id: quote
                x: 233
                y: 150
                width: 435
                height: 77
                text: qsTr("Text")
                horizontalAlignment: Text.AlignHCenter
                opacity: 1
                font.pixelSize: 17
                font.bold: true
            }

            Text {
                id: author
                x: 639
                y: 233
                width: 127
                height: 38
                text: qsTr("Text")
                font.pixelSize: 14
                font.bold: true
            }

            Text {
                id: name
                x: 333
                y: 37
                width: 235
                height: 76
                text: qsTr("Text")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 20
                font.bold: true
            }
        }
    }

    Connections {
            target: appBridge
            onDataChanged:
            {
                quote.text = appBridge.JsonData.quotes[0].q;
                author.text = "-"+appBridge.JsonData.quotes[0].a;
                name.text = "Hello, "+appBridge.JsonData.name;


            }
        }
}
