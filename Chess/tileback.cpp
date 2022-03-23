#include "tileback.h"

TileBack::TileBack(QObject *parent)
    : QObject(parent), xCordValue{0}, yCordValue{0}, containsFigureValue{false} {}

void TileBack::setXCord(const unsigned short &xCordGiven) {
    if(xCordGiven != xCordValue) {
        xCordValue = xCordGiven;
        emit xCordChanged();
    }
}

void TileBack::setYCord(const unsigned short &yCordGiven) {
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

unsigned short TileBack::xCord() const {
    return xCordValue;
}

unsigned short TileBack::yCord() const {
    return yCordValue;
}

bool TileBack::containsFigure() const {
    return containsFigureValue;
}
