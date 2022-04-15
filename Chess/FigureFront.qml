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

        drag.target: tile

        onReleased: {
            parent = tile.Drag.target !== null ? tile.Drag.target : mouseArea.parent
        }

        // remember to delete this signal handler
        onDoubleClicked: {
            console.log("Double Clicked:")
            console.log(root)
            root.destroy()
        }

        Rectangle {
            id: tile
            width: root.width
            height: root.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"

            Image {
                id: figureImage
                source: figureSource
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }

            Drag.keys: [ "blue" ]
            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: 32
            Drag.hotSpot.y: 32
            states: State {
                when: mouseArea.drag.active
                AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                PropertyChanges { target: tile; parent: root }
            }
        }
    }
}
