#include "tileback.h"

TileBack::TileBack(QObject *parent)
    : QObject(parent), xCordValue{0}, yCordValue{0}, containsFigureValue{false}, possibleValue{false} {}

void TileBack::setXCord(const int &xCordGiven) {
    if(xCordGiven != xCordValue) {
        xCordValue = xCordGiven;
        emit xCordChanged();
    }
}

void TileBack::setYCord(const int &yCordGiven) {
    if(yCordGiven != yCordValue) {
        yCordValue = yCordGiven;
        emit yCordChanged();
    }
}

void TileBack::setContainsFigure(const bool &containsFigureGiven) {
    if(containsFigureGiven != containsFigureValue) {
        containsFigureValue = containsFigureGiven;
        emit containsFigureChanged();
    }
}

void TileBack::setPossible(const bool &possibleGiven) {
    if(possibleGiven != possibleValue) {
        possibleValue = possibleGiven;
        emit possibleChanged();
    }
}

int TileBack::xCord() const {
    return xCordValue;
}

int TileBack::yCord() const {
    return yCordValue;
}

bool TileBack::containsFigure() const {
    return containsFigureValue;
}

bool TileBack::possible() const {
    return possibleValue;
}
