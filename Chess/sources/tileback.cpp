#include "headers/tileback.h"

TileBack::TileBack(QObject *parent)
    : QObject(parent), xCordValue{0}, yCordValue{0}, containsFigureValue{false},
      possibleValue{false}, keyValue{""}, isCheckedValue{false}, isCastledValue{false}, isRookCastledValue{""} {}

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

void TileBack::setColor(const QColor &colorGiven) {
    if(colorGiven != colorValue) {
        colorValue = colorGiven;
        emit colorChanged();
    }
}

void TileBack::setPossible(const bool &possibleGiven) {
    if(possibleGiven != possibleValue) {
        possibleValue = possibleGiven;
        emit possibleChanged();
    }
}

void TileBack::setKey(QString keyGiven) {
    if(keyGiven != keyValue) {
        keyValue = keyGiven;
        emit keyChanged();
    }
}

void TileBack::setIsChecked(const bool &isCheckedGiven) {
    if(isCheckedGiven != isCheckedValue) {
        isCheckedValue = isCheckedGiven;
        emit isCheckedChanged();
    }
}

void TileBack::setIsRookCastled(const QString &isRookCastledGiven) {
    if(isRookCastledGiven != isRookCastledValue) {
        isRookCastledValue = isRookCastledGiven;
        emit isRookCastledChanged();
    }
}

void TileBack::setIsCastled(const bool &isCastledGiven) {
    isCastledValue = isCastledGiven;
    // It is not function used from QML so no need for emitting etc
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

QColor TileBack::color() const {
    return colorValue;
}

bool TileBack::possible() const {
    return possibleValue;
}

QString TileBack::key() const {
    return keyValue;
}

bool TileBack::isChecked() const {
    return isCheckedValue;
}

bool TileBack::isCastled() const {
    return isCastledValue;
}

QString TileBack::isRookCastled() const {
    return isRookCastledValue;
}
