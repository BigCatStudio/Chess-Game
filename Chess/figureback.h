#ifndef FIGUREBACK_H
#define FIGUREBACK_H

#include <QObject>
#include <QDebug>
#include <QUrl>
#include <QtQml/qqmlregistration.h>

class FigureBack : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int xCord READ xCord WRITE setXCord NOTIFY xCordChanged)
    Q_PROPERTY(int yCord READ yCord WRITE setYCord NOTIFY yCordChanged)
    Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    QML_ELEMENT

private:
    int xCordValue;
    int yCordValue;
    QUrl imageSourceValue;
    int typeValue;

public:
    enum FigureType {
        King,
        Queen,
        Rook,
        Bishop,
        Knight,
        Pawn
    };

    Q_ENUMS(FigureType)

public:
    explicit FigureBack(QObject *parent = nullptr);

    void setXCord(const int &xCordGiven);
    void setYCord(const int &yCordGiven);
    void setImageSource(const QUrl &imageSourceGiven);
    void setType(const int &typeGiven);

    int xCord() const;
    int yCord() const;
    QUrl imageSource() const;
    int type() const;

signals:
    void xCordChanged();
    void yCordChanged();
    void imageSourceChanged();
    void typeChanged();
};

#endif // FIGUREBACK_H
