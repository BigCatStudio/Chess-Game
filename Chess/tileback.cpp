#include "tileback.h"

TileBack::TileBack(QObject *parent)
    : QObject(parent), xCordValue{0}, yCordValue{0}, containsFigureValue{false} {}

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

        // Emits signal to the figure with tile's cords
        if(containsFigureValue) {
            emit setFigureCords(xCordValue, yCordValue);
        }
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
