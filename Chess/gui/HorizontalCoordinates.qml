import QtQuick
import QtQuick.Window
import QtQuick.Layouts

Item {
    id: root
    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth

    width: Math.floor((minimalScreenSide - 100) / 9) * 9
    height: Math.floor((minimalScreenSide - 100) / 9) / 2

    RowLayout {
        spacing: 0

        // rectangle to fill left corner between coordinates bars
        Rectangle {
            width: root.width / 18
            height: root.height
            color: "#663300"
            border {
                color: "black"
                width: 1
            }
        }

        // Horizontal coordinates
        Repeater {
            id: coordinatesRepeater
            model: 8

            Rectangle {
                width: root.width / 9
                height: root.height
                color: "#663300"
                border {
                    color: "black"
                    width: 1
                }

                Text {
                    id: coordinateText
                    anchors.centerIn: parent
                    text: String.fromCharCode(65 + index)   // changing index to appropriate letter on chess board
                    color: "white"
                    font.pointSize: 15
                }
            }
        }

        // rectangle to fill right corner between coordinates bars
        Rectangle {
            width: root.width / 18
            height: root.height
            color: "#663300"
            border {
                color: "black"
                width: 1
            }
        }
    }
}
