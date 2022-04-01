import QtQuick

import Cpp.Classes

Item {
    id: root
    width: 64; height: 64

    property string figureSource: "qrc:/Images/Images/pawn.png"
    property color figureColor: "transparent"
    property int figureType: FigureBack.Pawn
    property var parentId: null     // Thisproperty holds styarting point parent when chessboard is created

    // Cords of the tile that is first parent for figure
    property int xCordStart: 0
    property int yCordStart: 0

    MouseArea {
        id: mouseArea
        width:64;
        height: 64
        parent: tilesFiguresHandler.getTile(root.xCordStart, root.yCordStart, figureBackend).dropAreaPointer
        anchors.centerIn: parent
        drag.target: tile

        onReleased: {
            if(tile.Drag.target !== null) {
                console.log("Action done on figure !!!")
                if(mouseArea.parent.tile !== tile.Drag.target.tile) {
                    tilesFiguresHandler.clearPossibleTiles()
                }

                // This condition will be changed, it needs to check if tile has 0 children
                // or if it contains figure of different color

                // I can make some research in the future if more often are figures taken down
                // or figures moved on empty tiles - probability

                if(!tile.Drag.target.children.length) {
                    // Think if changing parent from Item to tiles is not source of problem with
                    // DropAreas not being compatible with graphical versions
                    mouseArea.parent = tile.Drag.target
                    tilesFiguresHandler.addFigure(mouseArea.parent.tile, figureBackend)

                } else if(tilesFiguresHandler.getFigure(tile.Drag.target.tile).color !== figureBackend.color) {
                    // Add functionality of deleting dynamically created figures !!!
                    mouseArea.parent = tile.Drag.target
                    tilesFiguresHandler.addFigure(mouseArea.parent.tile, figureBackend)
                }
            }
        }

        Component.onCompleted: {
            // This line is performed to add figure on tile to backend std::unordered_map<TileBack*, FigureBack*> tileFigurePairs
            tilesFiguresHandler.addFigure(mouseArea.parent.tile, figureBackend)
        }

        onPressed: {
            // Rethink if it can be done better but for now it is working
            if(tilesFiguresHandler.getCurrentFigure() !== figureBackend) {
                console.log("Detected new figure pressed")
                tilesFiguresHandler.clearPossibleTiles()
            }

            console.log("Figure moved or clicked")
            tilesFiguresHandler.setCurrentFigure(figureBackend)
            console.log(figureBackend)
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
