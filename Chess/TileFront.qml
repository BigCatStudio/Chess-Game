import QtQuick
import QtQuick.Layouts

import Cpp.Classes

Item {
    id: rootChessBoardTile

    // Color of the tile is defined by chessBoardUtilities color getter
    property color color: chessBoardUtilities.color

    // Getting which side of the display device is smaller, to scale board
    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth

    // Defining tile cords
    property int xCord: chessBoardUtilities.xCordCalculated
    property int yCord: chessBoardUtilities.yCordCalculated

    // Specifying width & height behaviour
    Layout.fillWidth: true
    Layout.minimumWidth: minimalScreenSide / 14
    Layout.maximumWidth: minimalScreenSide / 10
    Layout.preferredWidth: minimalScreenSide / 12
    Layout.fillHeight: true
    Layout.minimumHeight: minimalScreenSide / 14
    Layout.maximumHeight: minimalScreenSide / 10
    Layout.preferredHeight: minimalScreenSide / 12

    Rectangle {
        id: tile
        anchors.fill: parent
        color: dropArea.containsDrag ? "grey" : rootChessBoardTile.color

        Rectangle {
            id: tileHovered
            anchors.fill: parent
            color: "blue"
            opacity: 0.0
        }

        Text {
            id: tileCords
            anchors.centerIn: parent
            text: rootChessBoardTile.xCord + " - " + rootChessBoardTile.yCord
            color: "green"
        }

        TileBack {
            id: tileBackend
            xCord: rootChessBoardTile.xCord
            yCord: rootChessBoardTile.yCord
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                if(!dropArea.containsDrag) {
                    tileHovered.opacity = 0.5
                }
            }

            onExited: {
                tileHovered.opacity = 0.0
            }
        }
    }

    DropArea {
        id: dropArea
        anchors.fill: parent
    }
}
