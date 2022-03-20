import QtQuick
import QtQuick.Layouts
import QtQuick.Window

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
    Layout.minimumWidth: minimalScreenSide / 13
    Layout.maximumWidth: minimalScreenSide / 9
    Layout.preferredWidth: minimalScreenSide / 11
    Layout.fillHeight: true
    Layout.minimumHeight: minimalScreenSide / 13
    Layout.maximumHeight: minimalScreenSide / 9
    Layout.preferredHeight: minimalScreenSide / 11

    width: minimalScreenSide / 9
    height: minimalScreenSide / 9

    Rectangle {
        id: tile
        anchors.fill: parent
        color: rootChessBoardTile.color
        border {
            color: "black"
            width: 1
        }

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
                tileHovered.opacity = 0.5
            }

            onExited: {
                tileHovered.opacity = 0.0
            }
        }
    }
}
