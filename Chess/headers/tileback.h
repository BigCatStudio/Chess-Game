#ifndef TILEBACK_H
#define TILEBACK_H

#include <QObject>
#include <QColor>
#include <QtQml/qqmlregistration.h>
#include <QString>

class TileBack : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int xCord READ xCord WRITE setXCord NOTIFY xCordChanged)
    Q_PROPERTY(int yCord READ yCord WRITE setYCord NOTIFY yCordChanged)
    Q_PROPERTY(bool containsFigure READ containsFigure WRITE setContainsFigure NOTIFY containsFigureChanged)
    Q_PROPERTY(bool possible READ possible WRITE setPossible NOTIFY possibleChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(bool isChecked READ isChecked WRITE setIsChecked NOTIFY isCheckedChanged)
    Q_PROPERTY(QString isRookCastled READ isRookCastled WRITE setIsRookCastled NOTIFY isRookCastledChanged)
    QML_ELEMENT

private:
    int xCordValue;
    int yCordValue;
    bool containsFigureValue;
    QColor colorValue;
    bool possibleValue;         // Determines whether it is valid tile for currently selected figure in play
    QString keyValue;           // Used in dropArea in TileFront to determine which figure can access the tile
    bool isCheckedValue;        // Determines if tile is currently under check
    bool isCastledValue;        // Determines if tile is possible for king as castling
    QString isRookCastledValue; // Determines if tile is possible for rook as castling

public:
    explicit TileBack(QObject *parent = nullptr);

    void setXCord(const int &xCordGiven);
    void setYCord(const int &yCordGiven);
    void setContainsFigure(const bool &containsFigureGiven);
    void setColor(const QColor &colorGiven);
    void setPossible(const bool &possibleGiven);
    void setKey(QString keyGiven);
    void setIsChecked(const bool &isCheckedGiven);
    void setIsCastled(const bool &isCastledGiven);
    void setIsRookCastled(const QString &isRookCastledGiven);

    int xCord() const;
    int yCord() const;
    bool containsFigure() const;
    QColor color() const;
    bool possible() const;
    QString key() const;
    bool isChecked() const;
    bool isCastled() const;
    QString isRookCastled() const;

signals:
    void xCordChanged();
    void yCordChanged();
    void containsFigureChanged();
    void colorChanged();
    void possibleChanged();
    void keyChanged();
    void isCheckedChanged();
    void isRookCastledChanged();
};

#endif // TILEBACK_H
