import QtQuick

import Cpp.Classes

Item {
    id: root
    width: 64; height: 64

    property string figureSource: "qrc:/Images/Images/pawn.png"
    property color figureColor: "transparent"
    property int figureType: FigureBack.Pawn

    MouseArea {
        id: mouseArea
        width:64; height: 64
        anchors.centerIn: parent

        drag.target: tile

        onReleased: {
            // Fix the Error that occurs when the figure is dropped outside the board!!!!
            if(tile.Drag.target !== null) {
                if(!tile.Drag.target.children.length) {
                    mouseArea.parent = tile.Drag.target
                    tilesFiguresHandler.addFigure(mouseArea.parent.figure, figureBackend)
                }
            }
        }

        onPressed: {
            tilesFiguresHandler.findValidTiles(figureBackend)
        }

        onParentChanged: {
            console.log("figure is on tile")
        }

        Rectangle {
            id: tile
            width: 64; height: 64
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: "transparent"

            Drag.active: mouseArea.drag.active

            states: State {
                when: mouseArea.drag.active
                AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                PropertyChanges { target: tile; parent: root }
            }

            Image {
                id: figureImage
                source: figureBackend.imageSource
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: cords
                anchors.centerIn: parent
                text: figureBackend.xCord + " - " + figureBackend.yCord + "\n" + figureBackend.type
            }

            FigureBack {
                id: figureBackend
                xCord: 0
                yCord: 0
                imageSource: root.figureSource
                color: root.figureColor
                type: root.figureType
            }
        }
    }
}
