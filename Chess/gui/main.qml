import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import Cpp.Classes

ApplicationWindow {
    id: root

    // comment test
    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth
    width: Math.floor((minimalScreenSide - 100) / 9) * 9
    height: Math.floor((minimalScreenSide - 100) / 9) * 9

    // Sizes must be set that way because of divided sizes of tiles etc. (Otherwise there would be some small white pixels at the edges)
    minimumHeight: Math.floor((minimalScreenSide - 100) / 9) * 9
    maximumHeight: Math.floor((minimalScreenSide - 100) / 9) * 9
    minimumWidth: Math.floor((minimalScreenSide - 100) / 9) * 9
    maximumWidth: Math.floor((minimalScreenSide - 100) / 9) * 9

    visible: true
    title: "Chess Game"

    //Functions and array for managing dynamically created figures
    property var objects: []

    function addObject(object) {
        root.objects.push(object)
    }

    function deleteObject(object) {
        for(var i = 0;i < root.objects.length;i++) {
            if(root.objects[i] === object) {
                root.objects.splice(i, 1)
                root.objects[i].destroy()
            }
        }
    }

    GridLayout {
        id: gridTiles
        anchors.centerIn: parent
        columns: 8
        rows: 8
        columnSpacing: 0
        rowSpacing: 0

        Repeater {
            id: repeaterTiles
            model: 64

            TileFront {}
        }
    }

    VerticalCoordinates {
        id: leftVerticalCoordinates
        anchors.right: gridTiles.left
        anchors.verticalCenter: gridTiles.verticalCenter
    }

    VerticalCoordinates {
        id: rightVerticalCoordinates
        anchors.left: gridTiles.right
        anchors.verticalCenter: gridTiles.verticalCenter
    }

    HorizontalCoordinates {
        id: topHorizontalCoordinates
        anchors.bottom: gridTiles.top
        anchors.horizontalCenter: gridTiles.horizontalCenter
    }

    HorizontalCoordinates {
        id: bottomHorizontalCoordinates
        anchors.top: gridTiles.bottom
        anchors.horizontalCenter: gridTiles.horizontalCenter
    }

    Item {
        id: figuresLayout
        anchors.centerIn: parent

        Component.onCompleted: {
            var figureComponent = Qt.createComponent("FigureFront.qml");

            for(var i = 1;i < 9;i++) {
                var whitePawnObject = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/pawnWhite.png",
                                                                                    "figureType": FigureBack.Pawn, "figureColor": "white",
                                                                                    "xCordStart": i, "yCordStart": 2})
                var blackPawnObject = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/pawnBlack.png",
                                                                                    "figureType": FigureBack.Pawn, "figureColor": "black",
                                                                                    "xCordStart": i, "yCordStart": 7})
                addObject(whitePawnObject)
                addObject(blackPawnObject)
            }

            var blackKnightObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/knightBlack.png",
                                                                                "figureType": FigureBack.Knight, "figureColor": "black",
                                                                                "xCordStart": 2, "yCordStart": 8})

            var blackKnightObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/knightBlack.png",
                                                                                "figureType": FigureBack.Knight, "figureColor": "black",
                                                                                "xCordStart": 7, "yCordStart": 8})

            var whiteKnightObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/knightWhite.png",
                                                                                "figureType": FigureBack.Knight, "figureColor": "white",
                                                                                "xCordStart": 2, "yCordStart": 1})

            var whiteKnightObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/knightWhite.png",
                                                                                "figureType": FigureBack.Knight, "figureColor": "white",
                                                                                "xCordStart": 7, "yCordStart": 1})

            var whiteRookObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/rookWhite.png",
                                                                                "figureType": FigureBack.Rook, "figureColor": "white",
                                                                                "xCordStart": 1, "yCordStart": 1})

            var whiteRookObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/rookWhite.png",
                                                                                "figureType": FigureBack.Rook, "figureColor": "white",
                                                                                "xCordStart": 8, "yCordStart": 1})

            var blackRookObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/rookBlack.png",
                                                                                "figureType": FigureBack.Rook, "figureColor": "black",
                                                                                "xCordStart": 1, "yCordStart": 8})

            var blackRookObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/rookBlack.png",
                                                                                "figureType": FigureBack.Rook, "figureColor": "black",
                                                                                "xCordStart": 8, "yCordStart": 8})

            var blackBishopObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/bishopBlack.png",
                                                                                "figureType": FigureBack.Bishop, "figureColor": "black",
                                                                                "xCordStart": 3, "yCordStart": 8})

            var blackBishopObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/bishopBlack.png",
                                                                                "figureType": FigureBack.Bishop, "figureColor": "black",
                                                                                "xCordStart": 6, "yCordStart": 8})

            var whiteBishopObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/bishopWhite.png",
                                                                                "figureType": FigureBack.Bishop, "figureColor": "white",
                                                                                "xCordStart": 3, "yCordStart": 1})

            var whiteBishopObject2 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/bishopWhite.png",
                                                                                "figureType": FigureBack.Bishop, "figureColor": "white",
                                                                                "xCordStart": 6, "yCordStart": 1})

            var blackKingObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/kingBlack.png",
                                                                                "figureType": FigureBack.King, "figureColor": "black",
                                                                                "xCordStart": 5, "yCordStart": 8})

            var whiteKingObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/kingWhite.png",
                                                                                "figureType": FigureBack.King, "figureColor": "white",
                                                                                "xCordStart": 5, "yCordStart": 1})

            var blackQueenObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/queenBlack.png",
                                                                                "figureType": FigureBack.Queen, "figureColor": "black",
                                                                                "xCordStart": 4, "yCordStart": 8})

            var whiteQueenObject1 = figureComponent.createObject(figuresLayout, { "figureSource": "qrc:/Images/Images/queenWhite.png",
                                                                                "figureType": FigureBack.Queen, "figureColor": "white",
                                                                                "xCordStart": 4, "yCordStart": 1})

            addObject(whiteBishopObject1)
            addObject(whiteBishopObject2)
            addObject(blackBishopObject1)
            addObject(blackBishopObject2)

            addObject(whiteKnightObject1)
            addObject(whiteKnightObject2)
            addObject(blackKnightObject1)
            addObject(blackKnightObject2)

            addObject(whiteRookObject1)
            addObject(whiteRookObject2)
            addObject(blackRookObject1)
            addObject(blackRookObject2)

            addObject(whiteKingObject1)
            addObject(blackKingObject1)

            addObject(whiteQueenObject1)
            addObject(blackQueenObject1)
        }
    }

    // This is Popup that shows up when pawn reaches last line and can be changed to other piece
    Popup {
        id: selectFigurePopup
        anchors.centerIn: parent
        width: Math.floor((minimalScreenSide - 100) / 9) * 4.5
        height: Math.floor((minimalScreenSide - 100) / 9) * 1.5
        modal: true
        focus: true

        property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth
        property bool displayPopup: tilesFiguresHandler.selectFigure;
        property color color: tilesFiguresHandler.getCurrentColorMove()
        property color whiteColor: "white"  // TODO Had to use this not good looking variables because of strange error, might be fixed
        property color blackColor: "black"

        onDisplayPopupChanged: {
            if(displayPopup === true) {
                if(tilesFiguresHandler.getCurrentColorMove() === whiteColor) {
                    queenFigure.figureSource = "qrc:/Images/Images/queenWhite.png"
                    queenFigure.figureType = FigureBack.Queen
                    queenFigure.backgroundColor = "black"

                    rookFigure.figureSource = "qrc:/Images/Images/rookWhite.png"
                    rookFigure.figureType = FigureBack.Rook
                    rookFigure.backgroundColor = "black"

                    bishopFigure.figureSource = "qrc:/Images/Images/bishopWhite.png"
                    bishopFigure.figureType = FigureBack.Bishop
                    bishopFigure.backgroundColor = "black"

                    knightFigure.figureSource = "qrc:/Images/Images/knightWhite.png"
                    knightFigure.figureType = FigureBack.Knight
                    knightFigure.backgroundColor = "black"
                } else {
                    queenFigure.figureSource = "qrc:/Images/Images/queenBlack.png"
                    queenFigure.figureType = FigureBack.Queen
                    queenFigure.backgroundColor = "white"

                    rookFigure.figureSource = "qrc:/Images/Images/rookBlack.png"
                    rookFigure.figureType = FigureBack.Rook
                    rookFigure.backgroundColor = "white"

                    bishopFigure.figureSource = "qrc:/Images/Images/bishopBlack.png"
                    bishopFigure.figureType = FigureBack.Bishop
                    bishopFigure.backgroundColor = "white"

                    knightFigure.figureSource = "qrc:/Images/Images/knightBlack.png"
                    knightFigure.figureType = FigureBack.Knight
                    knightFigure.backgroundColor = "white"
                }
                selectFigurePopup.open()
            } else {
                selectFigurePopup.close()
            }
        }

        // Pawn can change to rook, queen, knight and bishop
        RowLayout {
            id: figuresToSelect
            anchors.centerIn: parent

            Rectangle {
                width: Math.floor((minimalScreenSide - 100) / 9)
                height: Math.floor((minimalScreenSide - 100) / 9)

                FigureSelect {
                    id: queenFigure
                }
            }

            Rectangle {
                width: Math.floor((minimalScreenSide - 100) / 9)
                height: Math.floor((minimalScreenSide - 100) / 9)

                FigureSelect {
                    id: rookFigure
                }
            }

            Rectangle {
                width: Math.floor((minimalScreenSide - 100) / 9)
                height: Math.floor((minimalScreenSide - 100) / 9)

                FigureSelect {
                    id: bishopFigure
                }
            }

            Rectangle {
                width: Math.floor((minimalScreenSide - 100) / 9)
                height: Math.floor((minimalScreenSide - 100) / 9)

                FigureSelect {
                    id: knightFigure
                }
            }
        }
    }

    // This is Popup that shows up when is checkMate
    Popup {
        id: endGamePopup
        anchors.centerIn: parent
        width: Math.floor((minimalScreenSide - 100) / 9) * 3.5
        height: Math.floor((minimalScreenSide - 100) / 9) * 3
        modal: true
        focus: true
        closePolicy: "NoAutoClose"
        property bool checkMate: tilesFiguresHandler.isCheckMate
        property bool draw: tilesFiguresHandler.isDraw

        onCheckMateChanged: {
            if(tilesFiguresHandler.isCheckMate === true) {
                endText.textDisplay = "The game has ended\nThe winner is " + tilesFiguresHandler.winnerColor()
                endGamePopup.open()
            }
        }

        onDrawChanged: {
            if(tilesFiguresHandler.isDraw === true) {
                endText.textDisplay = "The game has ended\nThere is Draw"
                endGamePopup.open()
            }
        }

        Text {
            id: endText
            anchors.centerIn: parent
            property string textDisplay: ""
            text: textDisplay //"The game has ended\nWinner is " + winner
            font.pointSize: 20
        }
    }
}
