import QtQuick

import Cpp.Classes

Item {
    id: root

    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth

    // Default parameters
    property string figureSource: "qrc:/Images/Images/pawnWhite.png"
    property color figureColor: "transparent"
    property int figureType: FigureBack.Pawn

    // Default coordinates where figures at at the begining
    property int xCordStart: 0
    property int yCordStart: 0

    width: Math.floor((minimalScreenSide - 100) / 9)
    height: Math.floor((minimalScreenSide - 100) / 9)

    MouseArea {
        id: mouseArea
        width: root.width
        height: root.height
        anchors.centerIn: parent
        hoverEnabled: true

        // Determines which color is to move at the beginning
        drag.target: tilesFiguresHandler.getCurrentColorMove() === figureBackend.color ? figure : null

        onEntered: {
            // Not so good because the parameter changes only when enetered - but there is no need for more computations
            drag.target = tilesFiguresHandler.getCurrentColorMove() === figureBackend.color ? figure : null
        }

        // In this step possible moves with pressed figure are being found, also possible check should be found
        onPressed: {
            if(mouseArea.drag.target != null) {
                tilesFiguresHandler.findValidTiles(figureBackend)
            }
        }

        // In this step the chessboard is cleared and new state is updated, also checks are detected
        onReleased: {
            if(figure.Drag.target !== null) {
                tilesFiguresHandler.changeFigureCoords(figure.Drag.target.tileBackPointer, figureBackend)
                tilesFiguresHandler.clearPossibleTiles()
                tilesFiguresHandler.findCheckAfterMove()    //looking for  check to king of opposite color
                tilesFiguresHandler.setCurrentColorMove()
                tilesFiguresHandler.findCheckMate()
                parent = figure.Drag.target
            }
        }

        onParentChanged: {
            console.log("Figure changed position " + figureBackend + ":" + figureBackend.xCord + "x" + figureBackend.yCord)
        }

        FigureBack {
            id: figureBackend
            imageSource: root.figureSource
            type: root.figureType
            color: root.figureColor
            xCord: root.xCordStart
            yCord: root.yCordStart

            Component.onCompleted: {
                tilesFiguresHandler.addFigure(figureBackend)
                mouseArea.parent = tilesFiguresHandler.getTile(xCord, yCord).dropAreaPointer
            }

            onDeleteFigureChanged: {
                if(figureBackend.deleteFigure) {
                    root.destroy()
                }
            }
        }

        Rectangle {
            id: figure
            width: root.width
            height: root.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"

            Drag.keys: [ (figureBackend.xCord).toString() + (figureBackend.yCord).toString() ]
            Drag.active: mouseArea.drag.active

            // This sets dragging to the center of figure so the feeling of where figure will be dropped is more accurate
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2

            states: State {
                when: mouseArea.drag.active
                AnchorChanges { target: figure; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                PropertyChanges { target: figure; parent: root }
            }

            Image {
                id: figureImage
                source: figureBackend.imageSource
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }
        }
    }
}
