import QtQuick

import Cpp.Classes

Item {
    id: root

    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth

    property string figureSource: "qrc:/Images/Images/pawn.png"
    property color figureColor: "transparent"
    property int figureType: FigureBack.Pawn

    // Coordinates where figures at at the begining
    property int xCordStart: 0
    property int yCordStart: 0

    width: Math.floor((minimalScreenSide - 100) / 9)
    height: Math.floor((minimalScreenSide - 100) / 9)

    MouseArea {
        id: mouseArea
        width: root.width
        height: root.height
        anchors.centerIn: parent

        drag.target: figure

        onReleased: {
            if(figure.Drag.target !== null) {
                tilesFiguresHandler.changeFigureCoords(figure.Drag.target.tileBackPointer, figureBackend)
                parent = figure.Drag.target
            }
        }

        onParentChanged: {
            //tilesFiguresHandler.changeFigureCoords(mouseArea.parent.tileBackPointer, figureBackend)
            console.log("Figure changed position " + figureBackend + ":" + figureBackend.xCord + "x" + figureBackend.yCord)
        }

        // remember to delete this signal handler
        onDoubleClicked: {
            console.log("Double Clicked:")
            console.log(root)
            root.destroy()
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

            //Drag.keys: [ "blue" ]
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
