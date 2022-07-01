import QtQuick

import Cpp.Classes

Item {
    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth

    // Default parameters
    property string figureSource: "qrc:/Images/Images/pawn.png"
    property color figureColor: "transparent"
    property int figureType: FigureBack.Pawn
    property color backgroundColor: "white"

    width: Math.floor((minimalScreenSide - 100) / 9)
    height: Math.floor((minimalScreenSide - 100) / 9)

    Rectangle {
        anchors.fill: parent
        color: backgroundColor

        Image {
            id: figureImage
            source: figureSource
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("------- Call before setSelectedFigure ---------")
                    console.log(tilesFiguresHandler.winnerColor())
                    tilesFiguresHandler.setSelectedFigure(figureType, figureSource)
                }
            }
        }
    }
}
