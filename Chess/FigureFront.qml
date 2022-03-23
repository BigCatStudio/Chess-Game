import QtQuick

Item {
    id: item
    width: 64; height: 64

    MouseArea {
        id: mouseArea
        width:64; height: 64
        anchors.centerIn: parent

        drag.target: tile

        onReleased: { parent = tile.Drag.target !== null ? tile.Drag.target : mouseArea.parent }

        onParentChanged: {
            console.log("figure is on tile")
        }

        Rectangle {
            id: tile
            width: 64; height: 64
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Drag.active: mouseArea.drag.active

            Image {
                id: figureImage
                source: "qrc:/Images/Images/figure2.png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }

            states: State {
                when: mouseArea.drag.active
                AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                PropertyChanges { target: tile; parent: item }
            }
        }
    }
}
