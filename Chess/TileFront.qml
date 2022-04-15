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
        id: coordinatesTile
        anchors.centerIn: parent
        text: tileBackend.xCord + "x" + tileBackend.yCord
        color: "black"
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
        //keys: ["yellow"]
    }
}
