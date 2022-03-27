#ifndef TILESFIGURESHANDLER_H
#define TILESFIGURESHANDLER_H

#include <QObject>
#include <QDebug>
#include <unordered_map>

#include "tileback.h"
#include "figureback.h"

class TilesFiguresHandler : public QObject
{
    Q_OBJECT

private:
    std::unordered_map<TileBack*, FigureBack*> tileFigurePairs;
public:
    explicit TilesFiguresHandler(QObject *parent = nullptr);

    Q_INVOKABLE void addTile(TileBack* SourceTile);
    Q_INVOKABLE void addFigure(TileBack* SourceTile, FigureBack* SourceFigure);

signals:

};

#endif // TILESFIGURESHANDLER_H
