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
    QML_ELEMENT

private:
    int xCordValue;
    int yCordValue;
    bool containsFigureValue;

public:
    explicit TileBack(QObject *parent = nullptr);

    void setXCord(const int &xCordGiven);
    void setYCord(const int &yCordGiven);
    void setContainsFigure(const bool &containsFigureGiven);

    int xCord() const;
    int yCord() const;
    bool containsFigure() const;

signals:
    void xCordChanged();
    void yCordChanged();
    void containsFigureChanged();
    void setFigureCords(int x, int y);
};

#endif // TILEBACK_H
