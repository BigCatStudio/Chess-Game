import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import Cpp.Classes

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


        Component.onCompleted: {
            var component1 = Qt.createComponent("FigureFront.qml");
            var object1 = component1.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_white_pawn.jpg", "figureType": FigureBack.Pawn, "figureColor": "white" })

            var component2 = Qt.createComponent("FigureFront.qml");
            var object2 = component2.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_black_pawn.png", "figureType": FigureBack.Pawn, "figureColor": "black" })
        }



//        FigureFront { figureSource: "qrc:/Images/Images/test_white_pawn.jpg"; figureType: FigureBack.Pawn; figureColor: "white" }
//        FigureFront { figureSource: "qrc:/Images/Images/bishop.png"; figureType: FigureBack.Bishop; figureColor: "white" }
//        FigureFront { figureSource: "qrc:/Images/Images/knight.png"; figureType: FigureBack.Knight; figureColor: "white" }
//        FigureFront { figureSource: "qrc:/Images/Images/rook.png"; figureType: FigureBack.Rook; figureColor: "white" }
//        FigureFront { figureSource: "qrc:/Images/Images/queen.png"; figureType: FigureBack.Queen; figureColor: "white" }
//        FigureFront { figureSource: "qrc:/Images/Images/king.png"; figureType: FigureBack.King; figureColor: "white" }

//        FigureFront { figureSource: "qrc:/Images/Images/test_black_pawn.png"; figureType: FigureBack.Pawn; figureColor: "black" }
//        FigureFront { figureSource: "qrc:/Images/Images/bishop.png"; figureType: FigureBack.Bishop; figureColor: "black" }
//        FigureFront { figureSource: "qrc:/Images/Images/knight.png"; figureType: FigureBack.Knight; figureColor: "black" }
//        FigureFront { figureSource: "qrc:/Images/Images/rook.png"; figureType: FigureBack.Rook; figureColor: "black" }
//        FigureFront { figureSource: "qrc:/Images/Images/queen.png"; figureType: FigureBack.Queen; figureColor: "black" }
//        FigureFront { figureSource: "qrc:/Images/Images/king.png"; figureType: FigureBack.King; figureColor: "black" }
    }
}
