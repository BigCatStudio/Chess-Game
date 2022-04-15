#include "figureback.h"

FigureBack::FigureBack(QObject *parent)
    : QObject(parent), deleteFigureValue{false}, xCordValue{0}, yCordValue{0}, colorValue{""}, imageSourceValue{""} {}

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

void FigureBack::setColor(const QColor &colorGiven) {
    if(colorGiven != colorValue) {
        colorValue = colorGiven;
        emit colorChanged();
    }
}

void FigureBack::setDeleteFigure(const bool &deleteFigureGiven) {
    if(deleteFigureGiven != deleteFigureValue) {
        deleteFigureValue = deleteFigureGiven;
        emit deleteFigureChanged();
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

QColor FigureBack::color() const {
    return colorValue;
}

bool FigureBack::deleteFigure() const {
    return deleteFigureValue;
}
