#ifndef TILEBACK_H
#define TILEBACK_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

class TileBack : public QObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned short xCord READ xCord WRITE setXCord NOTIFY xCordChanged)
    Q_PROPERTY(unsigned short yCord READ yCord WRITE setYCord NOTIFY yCordChanged)
    QML_ELEMENT

private:
    unsigned short xCordValue;
    unsigned short yCordValue;

public:
    explicit TileBack(QObject *parent = nullptr);

    void setXCord(const unsigned short &xCordGiven);
    void setYCord(const unsigned short &yCordGiven);

    unsigned short xCord() const;
    unsigned short yCord() const;

signals:
    void xCordChanged();
    void yCordChanged();
};

#endif // TILEBACK_H
