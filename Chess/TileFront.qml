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
    property alias xCord: tileBackend.xCord
    property alias yCord: tileBackend.yCord

    // Deciding if tile contains any figure
    property bool containsFigure: false

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

        // Think about it if its is needed!!!
        Rectangle {
            id: tileHovered
            anchors.fill: parent
            color: "blue"
            opacity: 0.0
        }

        Text {
            id: tileCords
            anchors.centerIn: parent
            text: tileBackend.xCord + " - " + tileBackend.yCord + "\n" + tileBackend.containsFigure + "\n" + dropArea.children.length
            color: "green"
        }

        TileBack {
            id: tileBackend
            xCord: chessBoardUtilities.xCordCalculated
            yCord: chessBoardUtilities.yCordCalculated
            containsFigure: rootChessBoardTile.containsFigure

            Component.onCompleted: {
                tilesFiguresHandler.addTile(tileBackend);
            }
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

        DropArea {
            id: dropArea
            anchors.fill: parent

            // This alias is used, when the new figure is on tile, to send TileBackend addres to TilesFiguresHandler
            property alias figure: tileBackend

            // If the figure is dropped on tile the length of children<Item> changes
            // it helps to track if we can drop new figure on tile or if the figure can be taken
            onChildrenChanged: {
                console.log("Tile has figure")
                rootChessBoardTile.containsFigure = rootChessBoardTile.containsFigure ? false : true
            }
        }
    }
}
