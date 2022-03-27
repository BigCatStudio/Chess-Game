#include "figureback.h"

FigureBack::FigureBack(QObject *parent) : QObject(parent) {}

void FigureBack::setXCord(const int &xCordGiven) {
    if(xCordGiven != xCordValue) {
        xCordValue = xCordGiven;
        emit xCordChanged();
    }
}

void FigureBack::setYCord(const int &yCordGiven) {
    if(yCordGiven != yCordValue) {
        yCordValue = yCordGiven;
        emit yCordChanged();
    }
}

int FigureBack::xCord() const {
    return xCordValue;
}

int FigureBack::yCord() const {
    return yCordValue;
}
