import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import Cpp.Classes

Window {
    id: root

    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth
    width: minimalScreenSide - 100
    height: minimalScreenSide - 100
    visible: true
    title: "Chess Game"

    property var objects: []

    function addObject(object) {
        root.objects.push(object)
    }

    function displayObjects() {
        for(var i = 0;i < root.objects.length;i++) {
            console.log(root.objects[i])
        }
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

    GridLayout {
        id: gridFigures
        anchors.centerIn: parent
        columnSpacing: 10
        rowSpacing: 10

        Component.onCompleted: {
            var figureComponent = Qt.createComponent("FigureFront.qml");
            var figureObject1 = figureComponent.createObject(gridFigures, {})
            var figureObject2 = figureComponent.createObject(gridFigures, {})
            var figureObject3 = figureComponent.createObject(gridFigures, {})
            var figureObject4 = figureComponent.createObject(gridFigures, {})
            var figureObject5 = figureComponent.createObject(gridFigures, {})
            var figureObject6 = figureComponent.createObject(gridFigures, {})

            console.log("Direct reference")
            console.log(figureObject1)
            console.log(figureObject2)
            console.log(figureObject3)
            console.log(figureObject4)
            console.log(figureObject5)
            console.log(figureObject6)

            addObject(figureObject1)
            addObject(figureObject2)
            addObject(figureObject3)
            addObject(figureObject4)
            addObject(figureObject5)
            addObject(figureObject6)

            console.log("Array reference")
            displayObjects()

//            console.log("deleting object4")
//            deleteObject(figureObject4)

//            console.log("Array reference")
//            displayObjects()

//            console.log("4-th object")
//            console.log(figureObject4)

//            console.log("4-th object")
//            figureObject4.destroy()
//            console.log(figureObject4)
        }
    }
}
