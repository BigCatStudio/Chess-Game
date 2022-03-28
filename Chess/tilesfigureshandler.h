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
public:
    explicit TilesFiguresHandler(QObject *parent = nullptr);

    Q_INVOKABLE void addTile(TileBack* SourceTile);
    Q_INVOKABLE void addFigure(TileBack* SourceTile, FigureBack* SourceFigure);
    Q_INVOKABLE void findValidTiles(FigureBack* SourceFigure);

signals:

};

#endif // TILESFIGURESHANDLER_H
