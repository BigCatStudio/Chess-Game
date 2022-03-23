import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import "qrc:/JavaScriptFiles/Utilities.js" as DynamicUtilities

// Think about Window or ApplicationWindow
ApplicationWindow {
    id: root
    visible: true
    title: qsTr("Chess Board")

    // First option using Repeater and custom type of ChessBoardTile
    minimumWidth: chessBoardFrameArea.Layout.minimumWidth
    maximumWidth: chessBoardFrameArea.Layout.maximumWidth //Screen.desktopAvailableWidth
    minimumHeight: chessBoardFrameArea.Layout.minimumHeight
    maximumHeight: chessBoardFrameArea.Layout.maximumHeight //Screen.desktopAvailableHeight

    width: chessBoardFrameArea.implicitWidth
    height: chessBoardFrameArea.implicitHeight

    GridLayout {
        id: chessBoardFrameArea
        anchors.fill: parent

        FrameFront {
            id: frame

            GridLayout {
                id: chessBoardTilesArea
                anchors.fill: parent
                anchors.margins: frame.minimalScreenSide / 20
                columnSpacing: 0
                rowSpacing: 0
                columns: 8
                rows: 8

                Repeater {
                    id: tileRepeater
                    model: 64

                    TileFront {
//                        FigureFront {
//                            anchors.fill: parent
//                        }
                    }
                }
            }
        }
    }

    Item {
        id: item

        property string colorKey: "yellow"

        width: 64; height: 64

        MouseArea {
            id: mouseArea
            width: 50; height: 50
            anchors.centerIn: parent

            drag.target: tile

            onReleased: { parent = tile.Drag.target !== null ? tile.Drag.target : item }

            Rectangle {
                id: tile
                width: 64; height: 64
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: item.colorKey

                Drag.active: mouseArea.drag.active

                states: State {
                    when: mouseArea.drag.active
                    AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                    PropertyChanges { target: tile; parent: item }
                }
            }
        }
    }
}
