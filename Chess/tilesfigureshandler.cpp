#include "tilesfigureshandler.h"

TilesFiguresHandler::TilesFiguresHandler(QObject *parent) : QObject(parent), currentFigure{nullptr} {}

// If tile has one of staring point figures it can contain also figure address
// if not set to nullptr
void TilesFiguresHandler::addTile(TileBack *SourceTile, FigureBack* SourceFigure) {
    tileFigurePairs[SourceTile] = nullptr;
    // tileFigurePairs[SourceTile] = SourceFigure;  Add when ready to implement starting point
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

    // Tiles calculated for black pawn
    for(auto& [key, value] : tileFigurePairs) {
        // Fix when figure is on last line
        if(key->xCord() == xCord && key->yCord() == (yCord - 1)) {
            key->setPossible(true);
        }
    }
}

TileBack *TilesFiguresHandler::getTile(const FigureBack* SourceFigure) const {
    for(auto& [key, value] : tileFigurePairs) {
        if(value == SourceFigure) {
            return key;
        }
    }
    return nullptr;
}

TileBack *TilesFiguresHandler::getTile(int xCord, int yCord, FigureBack *SourceFigure) const {
    for(auto& [key, value] : tileFigurePairs) {
        if(key->xCord() == xCord && key->yCord() == yCord) {
            // value = SourceFigure;
            return key;
        }
    }
    return nullptr;
}

FigureBack *TilesFiguresHandler::getFigure(const TileBack* SourceTile) const{
    for(auto& [key, value] : tileFigurePairs) {
        if(key == SourceTile) {
            return value;
        }
    }
    return nullptr;
}

void TilesFiguresHandler::clearPossibleTiles() {
    for(auto& [key, value] : tileFigurePairs) {
        if(key->possible()) {
            key->setPossible(false);
        }
    }
}

void TilesFiguresHandler::setCurrentFigure(FigureBack *SourceFigure) {
    if(SourceFigure != currentFigure) {
        currentFigure = SourceFigure;
    }
}

FigureBack *TilesFiguresHandler::getCurrentFigure() const {
    return currentFigure;
}
