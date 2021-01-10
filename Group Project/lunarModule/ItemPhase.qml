import QtQuick 2.0

Rectangle{
    //default
    property string phase: "New"
    property real scale: .5

    //sets the icon to be used
    function setIcon(value){
        if(value === "Full"){
            imgPhase.source = "qrc:/LunarPhaseIcons/full.png"

        }
        else if (value === "New"){
            imgPhase.source = "qrc:/LunarPhaseIcons//new.png"

        }
        else if (value === "WaningGibbous"){
            imgPhase.source = "qrc:/LunarPhaseIcons//WanGib.png"

        }
        else if (value === "WaningQuarter"){
            imgPhase.source = "qrc:/LunarPhaseIcons//WanQuar.png"

        }
        else if (value === "WaningCresent"){
            imgPhase.source = "qrc:/LunarPhaseIcons//WanCres.png"

        }
        else if (value === "WaxingCresent"){
            imgPhase.source = "qrc:/LunarPhaseIcons//WaxCres.png"

        }
        else if (value === "WaxingGibbous"){
            imgPhase.source = "qrc:/LunarPhaseIcons//WaxGib.png"

        }
        else if (value === "WaxingQuarter"){
            imgPhase.source = "qrc:/LunarPhaseIcons//WaxQuar.png"
        }

    }
    Text {
        id: txtPhase
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: imgPhase.bottom
        anchors.bottomMargin: 100
        color: "black"
        font.bold: true
        font.pointSize: 16
        text: phase
    }
    Image{
        id: imgPhase
        anchors.centerIn: parent
        source: "qrc:/LunarPhaseIcons//full.png"
        scale: 0.5
    }
}
