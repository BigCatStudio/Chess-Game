#include "tilesfigureshandler.h"

TilesFiguresHandler::TilesFiguresHandler(QObject *parent) : QObject(parent) {}

void TilesFiguresHandler::addTile(TileBack *SourceTile) {
    tileFigurePairs[SourceTile] = nullptr;
}

void TilesFiguresHandler::addFigure(TileBack *SourceTile, FigureBack *SourceFigure) {
    tileFigurePairs[SourceTile] = SourceFigure;

    SourceFigure->setXCord(SourceTile->xCord());
    SourceFigure->setYCord(SourceTile->yCord());

//    for(const auto& [key, value] : tileFigurePairs) {
//            qInfo() << key << "    " << value;
//    }
}
