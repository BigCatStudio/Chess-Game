#ifndef FIGUREBACK_H
#define FIGUREBACK_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

#include <QDebug>

class FigureBack : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int xCord READ xCord WRITE setXCord NOTIFY xCordChanged)
    Q_PROPERTY(int yCord READ yCord WRITE setYCord NOTIFY yCordChanged)
    QML_ELEMENT

private:
    int xCordValue;
    int yCordValue;

public:
    explicit FigureBack(QObject *parent = nullptr);

    void setXCord(const int &xCordGiven);
    void setYCord(const int &yCordGiven);

    int xCord() const;
    int yCord() const;

signals:
    void xCordChanged();
    void yCordChanged();
};

#endif // FIGUREBACK_H
