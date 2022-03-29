#include "tilesfigureshandler.h"

TilesFiguresHandler::TilesFiguresHandler(QObject *parent) : QObject(parent) {}

void TilesFiguresHandler::addTile(TileBack *SourceTile) {
    tileFigurePairs[SourceTile] = nullptr;
}

void TilesFiguresHandler::addFigure(TileBack *SourceTile, FigureBack *SourceFigure) {
    tileFigurePairs[SourceTile] = SourceFigure;

    SourceFigure->setXCord(SourceTile->xCord());
    SourceFigure->setYCord(SourceTile->yCord());

    // Iterates over map and checks if tile without figure has its value set to nullptr
    // It must be checked atfer figure is moved from one tile to another so that instance of that figure will not be
    // on more than one tile
    for(auto& [key, value] : tileFigurePairs) {
        if(!key->containsFigure() && value != nullptr) {
            value = nullptr;
        }
        // qInfo() << key << "    " << value;
    }
}

void TilesFiguresHandler::findValidTiles(FigureBack *SourceFigure) {
    int xCord = SourceFigure->xCord();
    int yCord = SourceFigure->yCord();
    int type = SourceFigure->type();

    // Tiles calculated for black
    for(auto& [key, value] : tileFigurePairs) {
        // Fix when figure is on last line
        if(key->xCord() == xCord && key->yCord() == (yCord - 1)) {
            key->setPossible(true);
        }
    }
}

TileBack *TilesFiguresHandler::getTile(const FigureBack *Source) const {
    for(auto& [key, value] : tileFigurePairs) {
        if(value == Source) {
            return key;
        }
    }
    // It never happens but added to remove warning
    return nullptr;
}
