import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import "qrc:/JavaScriptFiles/Utilities.js" as DynamicUtilities

ApplicationWindow {
    id: root
    visible: true
    title: qsTr("Chess Board")

    // First option using Repeater and custom type of ChessBoardTile
    minimumWidth: chessBoard.Layout.minimumWidth
    maximumWidth: chessBoard.Layout.maximumWidth //Screen.desktopAvailableWidth
    minimumHeight: chessBoard.Layout.minimumHeight
    maximumHeight: chessBoard.Layout.maximumHeight //Screen.desktopAvailableHeight

    width: chessBoard.implicitWidth
    height: chessBoard.implicitHeight

    onWidthChanged: height = width
    onHeightChanged: height = width

    GridLayout {
        id: chessBoard
        anchors.fill: parent
        columnSpacing: 0
        rowSpacing: 0
        columns: 8
        rows: 8

        Repeater {
            model: 64

            ChessBoardTile {
                color: chessBoardUtilities.color
            }
        }
    }
}
