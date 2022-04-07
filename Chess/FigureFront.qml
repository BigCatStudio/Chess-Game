import QtQuick

import Cpp.Classes

Item {
    id: root
    width: 64; height: 64

    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth

    property string figureSource: "qrc:/Images/Images/pawn.png"
    property color figureColor: "transparent"
    property int figureType: FigureBack.Pawn

    // Cords of the tile that is first parent for figure
    property int xCordStart: 0
    property int yCordStart: 0

    MouseArea {
        id: mouseArea
        width: parent.width
        height: parent.height
        // parent is DropArea type - check TileFront
        parent: tilesFiguresHandler.getTile(root.xCordStart, root.yCordStart, figureBackend).dropAreaPointer
        anchors.centerIn: parent

        // The tile can not be moved because the target of drag is null but MouseArea can be clicked
        // so that is why the possible moved are shown - it might be possible to change somehow rethink!!!
        drag.target: tilesFiguresHandler.getCurrentColorMove() === figureBackend.color ? tile : null

        Component.onCompleted: {
            // This line is performed to add figure on tile to backend std::unordered_map<TileBack*, FigureBack*> tileFigurePairs
            tilesFiguresHandler.addFigure(mouseArea.parent.tile, figureBackend)
        }

        // Checks if figure can be moved - might be changed to just deactivate MouseArea for move rethink!!!
        onEntered: {
            mouseArea.drag.target = tilesFiguresHandler.getCurrentColorMove() === figureBackend.color ? tile : null
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

        // I can make some research in the future if more often figures are taken down
        // or moved on empty tiles - propability
        onReleased: {
            if(tile.Drag.target !== null) {
                console.log("Tile's possible " + tile.Drag.target.tile + ":  " + tilesFiguresHandler.getPossible(tile.Drag.target.tile))

                if(tile.Drag.target.tile.possible === true) {
                    // Think it the if condition is necessary here
                    if(mouseArea.parent.tile !== tile.Drag.target.tile) {
                        tilesFiguresHandler.clearPossibleTiles()
                    }

                    if(!tile.Drag.target.children.length) {
                        // Think if changing parent from Item to tiles is not source of problem with
                        // DropAreas not being compatible with graphical versions
                        mouseArea.parent = tile.Drag.target
                        tilesFiguresHandler.addFigure(mouseArea.parent.tile, figureBackend)
                        tilesFiguresHandler.setCurrentColorMove();

                    }else if(tilesFiguresHandler.getFigure(tile.Drag.target.tile).color !== figureBackend.color) {
                        //There will be error with anchors because object is destroyed in wrong order and anchors alias becomes undefined

                        // here is the problem - first destroy object properly - then change pointer in map

                        tile.Drag.target.children[0].destroy()
                        //tile.Drag.target.children[0] = mouseArea.parent
                        mouseArea.parent = tile.Drag.target
                        tilesFiguresHandler.addFigure(mouseArea.parent.tile, figureBackend)
                        tilesFiguresHandler.setCurrentColorMove();
                    }
                }
            }
        }

        onParentChanged: {
            console.log("figure " + figureBackend + " " + figureBackend.xCord + "x" + figureBackend.yCord + " changed tile")
        }

        Rectangle {
            id: tile
            width: parent.width
            height: parent.height
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
