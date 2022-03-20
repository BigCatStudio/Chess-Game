import QtQuick
import QtQuick.Layouts
import QtQuick.Window

Item {
    id: rootChessBoardTile

    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth
    property color tileColor: rootChessBoardTile.color

    // Specifying width & height
    Layout.fillWidth: true
    Layout.minimumWidth: minimalScreenSide / 13
    Layout.maximumWidth: minimalScreenSide / 9
    Layout.preferredWidth: minimalScreenSide / 11
    Layout.fillHeight: true
    Layout.minimumHeight: minimalScreenSide / 13
    Layout.maximumHeight: minimalScreenSide / 9
    Layout.preferredHeight: minimalScreenSide / 11

    // Helpful properties
    property color color: "red"
    width: minimalScreenSide / 9
    height: minimalScreenSide / 9

    Rectangle {
        id: tile
        anchors.fill: parent
        color: tileColor
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
