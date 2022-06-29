#include "headers/chessboardutilities.h"

ChessBoardUtilities::ChessBoardUtilities(QObject *parent)
    : QObject{parent}, colorValue{"#ffcc99"}, counterColor {0}, xCounter{0}, yCounter{63} {}

QColor ChessBoardUtilities::color() {
    counterColor++;
    QColor additionalColor = colorValue;

    if(counterColor % 8) {
        colorValue = (colorValue == "#ffcc99") ? "#b35900" : "#ffcc99";
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
