import QtQuick
import QtQuick.Layouts

Item {
    id: rootChessBoardFrame

    // Getting which side of the display device is smaller, to scale board
    property int minimalScreenSide: (Screen.desktopAvailableWidth > Screen.desktopAvailableHeight) ? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth

    // Specifying width & height behaviour
    Layout.fillWidth: true
    Layout.minimumWidth: (minimalScreenSide / 14) * 8 + (minimalScreenSide / 20) * 2
    Layout.maximumWidth: (minimalScreenSide / 10) * 8 + (minimalScreenSide / 20) * 2
    Layout.preferredWidth: (minimalScreenSide / 12) * 8 + (minimalScreenSide / 20) * 2
    Layout.fillHeight: true
    Layout.minimumHeight: (minimalScreenSide / 14) * 8 + (minimalScreenSide / 20) * 2
    Layout.maximumHeight: (minimalScreenSide / 10) * 8 + (minimalScreenSide / 20) * 2
    Layout.preferredHeight: (minimalScreenSide / 12) * 8 + (minimalScreenSide / 20) * 2

    width: (minimalScreenSide / 12) * 8 + (minimalScreenSide / 20) * 2
    height: (minimalScreenSide / 12) * 8 + (minimalScreenSide / 20) * 2

    Rectangle {
        id: frame
        anchors.fill: parent
        color: "#802b00"
    }
}
