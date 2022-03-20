#ifndef CHESSBOARDUTILITIES_H
#define CHESSBOARDUTILITIES_H

#include <QObject>
#include <QColor>

class ChessBoardUtilities : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(short xCordCalculated READ xCordCalculated NOTIFY xCordCalculatedChanged)
    Q_PROPERTY(short yCordCalculated READ yCordCalculated NOTIFY yCordCalculatedChanged)

private:
    // setting tile color variables
    QColor colorValue;
    int counterColor;

    //setting tile cords variables
    short xCounter;
    short yCounter;

public:
    explicit ChessBoardUtilities(QObject *parent = nullptr);

    QColor color();
    void setColor(const QColor &colorGiven);

    short xCordCalculated();
    short yCordCalculated();

signals:
    void colorChanged();
    void xCordCalculatedChanged();
    void yCordCalculatedChanged();
};

#endif // CHESSBOARDUTILITIES_H
