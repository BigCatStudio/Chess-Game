#include "chessboardutilities.h"

ChessBoardUtilities::ChessBoardUtilities(QObject *parent)
    : QObject{parent}, colorValue{"white"}, counterColor {0}, xCounter{0}, yCounter{63} {}

QColor ChessBoardUtilities::color(){
    counterColor++;
    QColor additionalColor = colorValue;

    if(counterColor % 8) {
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

int ChessBoardUtilities::xCordCalculated() {
    //emit xCordCalculatedChanged();
    return (xCounter++ % 8) + 1;
}

int ChessBoardUtilities::yCordCalculated() {
    //emit yCordCalculatedChanged();
    return (yCounter-- / 8) + 1;
}
