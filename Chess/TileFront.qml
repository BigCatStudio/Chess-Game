import QtQuick
import QtQuick.Layouts

import Cpp.Classes

Rectangle {
    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth
    width: Math.floor((minimalScreenSide - 100) / 9)
    height: Math.floor((minimalScreenSide - 100) / 9)

    color: dropArea.containsDrag ? "grey" : "blue"
    border {
        width: 1
        color: "black"
    }

    DropArea {
        id: dropArea
        anchors.fill: parent
    }
}
