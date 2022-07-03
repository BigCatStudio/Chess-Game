import QtQuick
import QtQuick.Window
import QtQuick.Layouts

Item {
    id: root
    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth

    width: Math.floor((minimalScreenSide - 100) / 9) / 2
    height: Math.floor((minimalScreenSide - 100) / 9) * 8

    ColumnLayout {
        spacing: 0

        Repeater {
            id: coordinatesRepeater
            model: 8

            Rectangle {
                width: root.width
                height: root.height / 8
                color: "#663300"
                border {
                    color: "black"
                    width: 1
                }

                Text {
                    id: coordinateText
                    anchors.centerIn: parent
                    text: 8 - index
                    color: "white"
                    font.pointSize: 15
                }
            }
        }
    }
}
