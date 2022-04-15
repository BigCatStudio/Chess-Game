#ifndef TILESFIGURESHANDLER_H
#define TILESFIGURESHANDLER_H

#include <QObject>
#include <QDebug>
#include <unordered_map>

#include "tileback.h"
#include "figureback.h"

// This class contains hashed map with pairs: key [TileBack*] - value [FigureBack*]
// It provides possibility to:
//      -update very fast current location of figure on chess board
//      -check which tiles can be accessed by selected figure
//      -overcome nasty code in UI section by implementing desired functionality with clear code in C++

class TilesFiguresHandler : public QObject
{
    Q_OBJECT
private:
    std::unordered_map<TileBack*, FigureBack*> tileFigurePairs;
    FigureBack* currentFigure;
    QColor currentColorMove;
    //std::vector<T> figureObjects;

public:
    explicit TilesFiguresHandler(QObject *parent = nullptr);

    Q_INVOKABLE void addTile(TileBack* SourceTile);
    Q_INVOKABLE void addFigure(FigureBack* SourceFigure);
    Q_INVOKABLE TileBack* getTile(const FigureBack* SourceFigure) const;
    Q_INVOKABLE TileBack* getTile(int xCord, int yCord) const;
    Q_INVOKABLE FigureBack* getFigure(const TileBack* SourceTile) const;
    Q_INVOKABLE void clearPossibleTiles();
    Q_INVOKABLE void setCurrentFigure(FigureBack* SourceFigure);
    Q_INVOKABLE FigureBack* getCurrentFigure() const;
    Q_INVOKABLE bool getPossible(TileBack* SourceTile);
    Q_INVOKABLE void findValidTiles(FigureBack* SourceFigure);
    Q_INVOKABLE QColor getCurrentColorMove();
    Q_INVOKABLE void setCurrentColorMove();


    void findPawnTiles(int xCord, int yCord, QColor color);
    void findBishopTiles(int xCord, int yCord, QColor color);
    void findKnightiles(int xCord, int yCord, QColor color);
    void findRookTiles(int xCord, int yCord, QColor color);
    void findQueenTiles(int xCord, int yCord, QColor color);
    void findKingTiles(int xCord, int yCord, QColor color);

signals:

};

#endif // TILESFIGURESHANDLER_H
