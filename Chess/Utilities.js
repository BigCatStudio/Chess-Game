var component;
var sprite;

function createChessBoardTile() {
    component = Qt.createComponent("qrc:/ChessBoardTile.qml");
    sprite = component.createObject(root);

    if (sprite == null) {
        // Error Handling
        console.log("Error creating object");
    }
}
