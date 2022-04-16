import QtQuick
import QtQuick.Layouts

import Cpp.Classes

Rectangle {
    id: root

    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth
    width: Math.floor((minimalScreenSide - 100) / 9)
    height: Math.floor((minimalScreenSide - 100) / 9)

    color: dropArea.containsDrag ? "grey" : tileBackend.color
    border {
        width: 1
        color: "black"
    }

    Text {
        id: hasFigure
        anchors.bottom: parent.bottom
        text: tileBackend.containsFigure
    }

    Text {
        id: childrenCount
        anchors.top: parent.top
        text: dropArea.children.length
    }

    Text {
        id: possible
        anchors.right: parent.right
        text: tileBackend.possible
    }

    Rectangle {
        id: possibleMark
        width: parent.width / 3
        height: parent.height / 3
        radius: width / 2
        color: "blue"
        anchors.centerIn: parent
        visible: tileBackend.possible
    }

    TileBack {
        id: tileBackend
        xCord: chessBoardUtilities.xCordCalculated
        yCord: chessBoardUtilities.yCordCalculated
        color: chessBoardUtilities.color

        property alias dropAreaPointer: dropArea

        // Adds tile to the container of pairs tile-figure in TilesFiguresHandler class
        Component.onCompleted: {
            tilesFiguresHandler.addTile(tileBackend)
        }
    }

    DropArea {
        id: dropArea
        anchors.fill: parent

        property alias tileBackPointer: tileBackend

        keys: [tileBackend.key]
    }
}
