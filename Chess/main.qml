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
    minimumWidth: frameLayout.Layout.minimumWidth
    maximumWidth: frameLayout.Layout.maximumWidth //Screen.desktopAvailableWidth
    minimumHeight: frameLayout.Layout.minimumHeight
    maximumHeight: frameLayout.Layout.maximumHeight //Screen.desktopAvailableHeight

    width: frameLayout.implicitWidth
    height: frameLayout.implicitHeight

    // frame instance must be in layout so it can be resizeable along with the content inside
    GridLayout {
        id: frameLayout
        anchors.fill: parent

        FrameFront {
            id: frame

            GridLayout {
                id: tilesLayout
                anchors.fill: parent
                anchors.margins: frame.minimalScreenSide / 20
                columnSpacing: 0
                rowSpacing: 0
                columns: 8
                rows: 8

                Repeater {
                    id: tilesRepeater
                    model: 64

                    TileFront {}
                }
            }
        }
    }

    RowLayout {
        id: figuresLayout

        Repeater {
            id: figuresRepeater
            model: 5

            FigureFront {}
        }
    }
}
