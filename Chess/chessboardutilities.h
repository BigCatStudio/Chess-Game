#ifndef CHESSBOARDUTILITIES_H
#define CHESSBOARDUTILITIES_H

#include <QObject>
#include <QColor>

class ChessBoardUtilities : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

private:
    QColor colorValue;
    int counter;

public:
    explicit ChessBoardUtilities(QObject *parent = nullptr);

    QColor color();
    void setColor(const QColor &colorGiven);

signals:
    void colorChanged();
};

#endif // CHESSBOARDUTILITIES_H
