#include "chessboardutilities.h"

ChessBoardUtilities::ChessBoardUtilities(QObject *parent)
    : QObject{parent}, colorValue{"white"}, counter {0} {}

QColor ChessBoardUtilities::color(){
    counter++;
    QColor additionalColor = colorValue;

    if(counter % 8) {
        colorValue = (colorValue == "white") ? "black" : "white";
    }

    return additionalColor;
}

void ChessBoardUtilities::setColor(const QColor &colorGiven) {
    if(colorGiven != colorValue) {
        colorValue = colorGiven;
        emit colorChanged();
    }
}
