import QtQuick

import Cpp.Classes

Item {
    id: root
    width: 64; height: 64

    MouseArea {
        id: mouseArea
        width:64; height: 64
        anchors.centerIn: parent

        drag.target: tile

        onReleased: {
            if(!tile.Drag.target.children.length) {
                mouseArea.parent = tile.Drag.target
                tilesFiguresHandler.addFigure(mouseArea.parent.figure, figureBackend)
            }
        }

        onParentChanged: {
            console.log("figure is on tile")
        }

        Rectangle {
            id: tile
            width: 64; height: 64
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Drag.active: mouseArea.drag.active

            states: State {
                when: mouseArea.drag.active
                AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                PropertyChanges { target: tile; parent: root }
            }

            Image {
                id: figureImage
                source: "qrc:/Images/Images/figure2.png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: cords
                anchors.fill: parent
                text: figureBackend.xCord + " - " + figureBackend.yCord
            }

            FigureBack {
                id: figureBackend
                xCord: 0
                yCord: 0
            }
        }
    }
}
