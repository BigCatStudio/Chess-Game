import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import Cpp.Classes

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

    width: frameLayout.maximumWidth
    height: frameLayout.maximumHeight

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
            // No need to dynamically create figures when pawns reach last row because the pawns can just
            // change its imageSource and figureType
            // When pawn reaches last row display small reactangle with possible figures to choose (maybe popup)

            var figureComponent = Qt.createComponent("FigureFront.qml");

            for(var i = 1;i < 9;i++) {
                var whitePawnObject = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_white_pawn.jpg",
                                                                                    "figureType": FigureBack.Pawn, "figureColor": "white",
                                                                                    "xCordStart": i, "yCordStart": 2})
                var blackPawnObject = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_black_pawn.png",
                                                                                    "figureType": FigureBack.Pawn, "figureColor": "black",
                                                                                    "xCordStart": i, "yCordStart": 7})
            }

            var blackKnightObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_black_knight.jpg",
                                                                                "figureType": FigureBack.Knight, "figureColor": "black",
                                                                                "xCordStart": 2, "yCordStart": 8})

            var blackKnightObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_black_knight.jpg",
                                                                                "figureType": FigureBack.Knight, "figureColor": "black",
                                                                                "xCordStart": 7, "yCordStart": 8})

            var whiteKnightObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_white_knight.jpg",
                                                                                "figureType": FigureBack.Knight, "figureColor": "white",
                                                                                "xCordStart": 2, "yCordStart": 1})

            var whiteKnightObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_white_knight.jpg",
                                                                                "figureType": FigureBack.Knight, "figureColor": "white",
                                                                                "xCordStart": 7, "yCordStart": 1})

            var whiteRookObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_white_rook.jpeg",
                                                                                "figureType": FigureBack.Rook, "figureColor": "white",
                                                                                "xCordStart": 1, "yCordStart": 1})

            var whiteRookObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_white_rook.jpeg",
                                                                                "figureType": FigureBack.Rook, "figureColor": "white",
                                                                                "xCordStart": 8, "yCordStart": 1})

            var blackRookObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_black_rook.jpeg",
                                                                                "figureType": FigureBack.Rook, "figureColor": "black",
                                                                                "xCordStart": 1, "yCordStart": 8})

            var blackRookObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_black_rook.jpeg",
                                                                                "figureType": FigureBack.Rook, "figureColor": "black",
                                                                                "xCordStart": 8, "yCordStart": 8})

            var blackBishopObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_black_bishop.jpg",
                                                                                "figureType": FigureBack.Bishop, "figureColor": "black",
                                                                                "xCordStart": 3, "yCordStart": 8})

            var blackBishopObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_black_bishop.jpg",
                                                                                "figureType": FigureBack.Bishop, "figureColor": "black",
                                                                                "xCordStart": 6, "yCordStart": 8})

            var whiteBishopObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_white_bishop.jpeg",
                                                                                "figureType": FigureBack.Bishop, "figureColor": "white",
                                                                                "xCordStart": 3, "yCordStart": 1})

            var whiteBishopObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_white_bishop.jpeg",
                                                                                "figureType": FigureBack.Bishop, "figureColor": "white",
                                                                                "xCordStart": 6, "yCordStart": 1})

            var blackKingObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_black_king.jpeg",
                                                                                "figureType": FigureBack.King, "figureColor": "black",
                                                                                "xCordStart": 5, "yCordStart": 8})

            var whiteKingObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_white_king.jpeg",
                                                                                "figureType": FigureBack.King, "figureColor": "white",
                                                                                "xCordStart": 5, "yCordStart": 1})

            var blackQueenObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_black_queen.jpeg",
                                                                                "figureType": FigureBack.Queen, "figureColor": "black",
                                                                                "xCordStart": 4, "yCordStart": 8})

            var whiteQueenObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/test_white_queen.jpeg",
                                                                                "figureType": FigureBack.Queen, "figureColor": "white",
                                                                                "xCordStart": 4, "yCordStart": 1})

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
