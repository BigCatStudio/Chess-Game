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

void FigureBack::setImageSource(const QUrl &imageSourceGiven) {
    if(imageSourceGiven != imageSourceValue) {
        imageSourceValue = imageSourceGiven;
        emit imageSourceChanged();
    }
}

void FigureBack::setType(const int &typeGiven) {
    if(typeGiven != typeValue) {
        typeValue = typeGiven;
        emit typeChanged();
    }
}

int FigureBack::xCord() const {
    return xCordValue;
}

int FigureBack::yCord() const {
    return yCordValue;
}

QUrl FigureBack::imageSource() const {
    return imageSourceValue;
}

int FigureBack::type() const {
    return typeValue;
}
