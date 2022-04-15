import QtQuick
import QtQuick.Layouts

import Cpp.Classes

Rectangle {
    id: root

    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth
    width: Math.floor((minimalScreenSide - 100) / 9)
    height: Math.floor((minimalScreenSide - 100) / 9)

    property color normalColor: chessBoardUtilities.color
    property int xCord: chessBoardUtilities.xCordCalculated
    property int yCord: chessBoardUtilities.yCordCalculated

    color: dropArea.containsDrag ? "grey" : normalColor
    border {
        width: 1
        color: "black"
    }

    Text {
        id: coordinatesTile
        anchors.centerIn: parent
        text: root.xCord + "x" + root.yCord
        color: "black"
    }

    DropArea {
        id: dropArea
        anchors.fill: parent
    }
}
