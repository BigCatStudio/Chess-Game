#ifndef CHESSBOARDUTILITIES_H
#define CHESSBOARDUTILITIES_H

#include <QObject>
#include <QColor>
#include "tileback.h"
#include "figureback.h"

class ChessBoardUtilities : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int xCordCalculated READ xCordCalculated NOTIFY xCordCalculatedChanged)
    Q_PROPERTY(int yCordCalculated READ yCordCalculated NOTIFY yCordCalculatedChanged)

private:
    // setting tile color variables
    QColor colorValue;
    int counterColor;

    //setting tile cords variables
    int xCounter;
    int yCounter;

public:
    explicit ChessBoardUtilities(QObject *parent = nullptr);

    QColor color();
    void setColor(const QColor &colorGiven);

    int xCordCalculated();
    int yCordCalculated();

signals:
    void colorChanged();
    void xCordCalculatedChanged();
    void yCordCalculatedChanged();
};

#endif // CHESSBOARDUTILITIES_H
