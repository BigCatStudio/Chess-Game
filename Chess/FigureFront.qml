import QtQuick

import Cpp.Classes

Item {
    id: root

    property string colorKey: "yellow"
    property var previousTile: root

    width: 60
    height: 60

    MouseArea {
        id: mouseArea
        width: 64; height: 64
        anchors.centerIn: parent

        drag.target: tile

        onReleased: {
            parent = tile.Drag.target !== null ? tile.Drag.target : mouseArea.parent
        }

        onDoubleClicked: {
            console.log("Double Clicked:")
            console.log(root)
            root.destroy()
        }

        Rectangle {
            id: tile

            width: 64; height: 64
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            color: root.colorKey

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
