#ifndef TILESFIGURESHANDLER_H
#define TILESFIGURESHANDLER_H

#include <QObject>
#include <QDebug>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "headers/tileback.h"
#include "headers/figureback.h"
#include "headers/writer.h"

// This class contains hash map with pairs: key [TileBack*] - value [FigureBack*]
// It provides possibility to:
//      -update very fast current location of figure on chess board
//      -check which tiles can be accessed by selected figure
//      -overcome nasty code in UI section by implementing desired functionality with clear code in C++

class TilesFiguresHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool selectFigure READ selectFigure WRITE setSelectFigure NOTIFY selectFigureChanged)        // Parameter used to choose new figure for pawn
    Q_PROPERTY(bool isCheckMate READ isCheckMate WRITE setIsCheckMate NOTIFY isCheckMateChanged)
    Q_PROPERTY(bool isDraw READ isDraw WRITE setIsDraw NOTIFY isDrawChanged)
private:
    bool selectFigureValue;
    bool isCheckMateValue;
    bool isDrawValue;
    std::unordered_map<TileBack*, FigureBack*> tileFigurePairs;     // Contains pairs of tiles and figures that are on these tiles
    QColor currentColorMove;                // Contains current color to make move
    FigureBack* currentFigure;
    FigureBack* blackKing;                  // Pointers to kings - useful when checking for checks after and before move
    FigureBack* whiteKing;
    Writer movesWriter;                     // TODO This class will be used to save games moves

public:
    explicit TilesFiguresHandler(QObject *parent = nullptr);

    bool selectFigure();
    void setSelectFigure(const bool &selectFigureGiven);
    bool isCheckMate() const;
    void setIsCheckMate(const bool &isCheckMateGiven);
    bool isDraw() const;
    void setIsDraw(const bool &isDrawGiven);

    Q_INVOKABLE void addTile(TileBack* SourceTile);
    Q_INVOKABLE void addFigure(FigureBack* SourceFigure);
    Q_INVOKABLE void changeFigureCoords(TileBack* SourceTile, FigureBack* SourceFigure);
    Q_INVOKABLE TileBack* getTile(const FigureBack* SourceFigure) const;
    Q_INVOKABLE TileBack* getTile(int xCord, int yCord);
    Q_INVOKABLE FigureBack* getFigure(int xCord, int yCord);
    Q_INVOKABLE void clearPossibleTiles();
    Q_INVOKABLE void clearCastledTiles();
    Q_INVOKABLE void setCurrentFigure(FigureBack* SourceFigure);
    Q_INVOKABLE FigureBack* getCurrentFigure() const;
    Q_INVOKABLE bool getPossible(TileBack* SourceTile);
    Q_INVOKABLE QColor getCurrentColorMove();
    Q_INVOKABLE void setCurrentColorMove();
    Q_INVOKABLE int findValidTiles(FigureBack* SourceFigure);
    Q_INVOKABLE bool findCheckBeforeMove(int xCord, int yCord, QColor color, TileBack * SourceTile, FigureBack* SourceFigure);
    Q_INVOKABLE void findCheckAfterMove();
    Q_INVOKABLE void findCheckMate();
    Q_INVOKABLE QString winnerColor() const;
    Q_INVOKABLE void setSelectedFigure(int typeGiven, QString sourceGiven);

    int findPawnTiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure);
    int findBishopTiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure);
    int findKnightiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure);
    int findRookTiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure);
    int findQueenTiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure);
    int findKingTiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure);

signals:
    void selectFigureChanged();
    void isCheckMateChanged();
    void isDrawChanged();
};

#endif // TILESFIGURESHANDLER_H
