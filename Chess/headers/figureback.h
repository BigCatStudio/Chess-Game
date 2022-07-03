#ifndef FIGUREBACK_H
#define FIGUREBACK_H

#include <QObject>
#include <QDebug>
#include <QUrl>
#include <QColor>
#include <QtQml/qqmlregistration.h>

class FigureBack : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int xCord READ xCord WRITE setXCord NOTIFY xCordChanged)
    Q_PROPERTY(int yCord READ yCord WRITE setYCord NOTIFY yCordChanged)
    Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)     // Type enum is accessed as int from QML
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool deleteFigure READ deleteFigure WRITE setDeleteFigure NOTIFY deleteFigureChanged)
    Q_PROPERTY(bool canMove READ canMove WRITE setCanMove NOTIFY canMoveChanged)
    Q_PROPERTY(bool wasMoved READ wasMoved WRITE setWasMoved NOTIFY wasMovedChanged)
    Q_PROPERTY(bool checkBlock READ checkBlock WRITE setCheckBlock NOTIFY checkBlockChanged)
    Q_PROPERTY(bool isChecked READ isChecked WRITE setIsChecked NOTIFY isCheckedChanged)
    QML_ELEMENT

private:
    int xCordValue;
    int yCordValue;
    QUrl imageSourceValue;
    int typeValue;
    QColor colorValue;
    bool deleteFigureValue;     // This variable determines if piece has been taken and must be destroyed
    bool canMoveValue;          // This variable determines if piece can be moved - calculating check and other possibilities
    bool wasMovedValue;         // This variable tells if figure was already moved - useful when making castling or long move by pawn
    bool checkBlockValue;
    bool isCheckedValue;

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
    void setColor(const QColor &colorGiven);
    void setDeleteFigure(const bool &deleteFigureGiven);
    void setCanMove(const bool &canMoveGiven);
    void setWasMoved(const bool &wasMovedGiven);
    void setCheckBlock(const bool &checkBlockGiven);
    void setIsChecked(const bool &isCheckedGiven);

    int xCord() const;
    int yCord() const;
    QUrl imageSource() const;
    int type() const;
    QColor color() const;
    bool deleteFigure() const;
    bool canMove() const;
    bool wasMoved() const;
    bool checkBlock() const;
    bool isChecked() const;

signals:
    void xCordChanged();
    void yCordChanged();
    void imageSourceChanged();
    void typeChanged();
    void colorChanged();
    void deleteFigureChanged();
    void canMoveChanged();
    void wasMovedChanged();
    void checkBlockChanged();
    void isCheckedChanged();
};

#endif // FIGUREBACK_H
