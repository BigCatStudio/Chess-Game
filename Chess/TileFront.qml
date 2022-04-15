import QtQuick
import QtQuick.Layouts

import Cpp.Classes

Rectangle {
    color: dropArea.containsDrag ? "grey" : "blue"
    width: 90
    height: 90
    border {
        width: 1
        color: "black"
    }

    DropArea {
        id: dropArea
        anchors.fill: parent
    }
}
