#ifndef TILEBACK_H
#define TILEBACK_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

class TileBack : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int xCord READ xCord WRITE setXCord NOTIFY xCordChanged)
    Q_PROPERTY(int yCord READ yCord WRITE setYCord NOTIFY yCordChanged)
    Q_PROPERTY(bool containsFigure READ containsFigure WRITE setContainsFigure NOTIFY containsFigureChanged)
    Q_PROPERTY(bool possible READ possible WRITE setPossible NOTIFY possibleChanged)
    QML_ELEMENT

private:
    int xCordValue;
    int yCordValue;
    bool containsFigureValue;
    bool possibleValue;

public:
    explicit TileBack(QObject *parent = nullptr);

    void setXCord(const int &xCordGiven);
    void setYCord(const int &yCordGiven);
    void setContainsFigure(const bool &containsFigureGiven);
    void setPossible(const bool &possibleGiven);

    int xCord() const;
    int yCord() const;
    bool containsFigure() const;
    bool possible() const;

signals:
    void xCordChanged();
    void yCordChanged();
    void containsFigureChanged();
    void setFigureCords(int x, int y);
    void possibleChanged();
};

#endif // TILEBACK_H
