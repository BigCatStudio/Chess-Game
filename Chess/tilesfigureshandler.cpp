#include "tilesfigureshandler.h"

TilesFiguresHandler::TilesFiguresHandler(QObject *parent) : QObject(parent), currentFigure{nullptr} {}

// If tile has one of staring point figures it can contain also figure address
// if not set to nullptr
void TilesFiguresHandler::addTile(TileBack *SourceTile, FigureBack* SourceFigure) {
    tileFigurePairs[SourceTile] = nullptr;

    qInfo() << SourceTile << ": " << SourceTile->xCord() << "x" << SourceTile->yCord();

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

bool TilesFiguresHandler::getPossible(TileBack *SourceTile) {
    return SourceTile->possible();
}

void TilesFiguresHandler::findValidTiles(FigureBack *SourceFigure) {
    switch(SourceFigure->type()) {
        case FigureBack::Pawn: {
            findPawnTiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color());
            break;
        }
        case FigureBack::Bishop: {
            findBishopTiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color());
            break;
        }
        case FigureBack::Knight: {
            findKnightiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color());
            break;
        }
        case FigureBack::Rook: {
            findRookTiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color());
            break;
        }
        case FigureBack::Queen: {
            findQueenTiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color());
            break;
        }
        case FigureBack::King: {
            findKingTiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color());
            break;
        }
    }
}

void TilesFiguresHandler::findPawnTiles(int xCord, int yCord, QColor color) {
    if(color == "black") {
        // maybe lambda can be used
        for(auto& [key, value] : tileFigurePairs) {
            // Fix when figure is on last line
            if(key->xCord() == xCord && key->yCord() == (yCord - 1)) {
                key->setPossible(true);
            }
        }
    } else {
        for(auto& [key, value] : tileFigurePairs) {
            // Fix when figure is on last line
            if(key->xCord() == xCord && key->yCord() == (yCord + 1)) {
                key->setPossible(true);
            }
        }
    }
}

void TilesFiguresHandler::findBishopTiles(int xCord, int yCord, QColor color) {
    if(color == "black") {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == xCord && key->yCord() == (yCord - 1)) {
                key->setPossible(true);
            }
        }
    } else {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == xCord && key->yCord() == (yCord + 1)) {
                key->setPossible(true);
            }
        }
    }
}

void TilesFiguresHandler::findKnightiles(int xCord, int yCord, QColor color) {
    std::vector<std::pair<int, int>> possibleCords;

    possibleCords.push_back(std::pair<int,int> {xCord - 2, yCord + 1});
    possibleCords.push_back(std::pair<int,int> {xCord - 2, yCord - 1});
    possibleCords.push_back(std::pair<int,int> {xCord - 1, yCord + 2});
    possibleCords.push_back(std::pair<int,int> {xCord - 1, yCord - 2});
    possibleCords.push_back(std::pair<int,int> {xCord + 1, yCord + 2});
    possibleCords.push_back(std::pair<int,int> {xCord + 1, yCord - 2});
    possibleCords.push_back(std::pair<int,int> {xCord + 2, yCord + 1});
    possibleCords.push_back(std::pair<int,int> {xCord + 2, yCord - 1});

    // Error when placing horse on horse more than one time does not get place during real game

    for(auto& [key, value] : tileFigurePairs) {
        for(auto &pair : possibleCords) {
            if(key->xCord() == pair.first && key->yCord() == pair.second) {
                if(value == nullptr || value->color() != color) {
                    key->setPossible(true);
                }
                break;
            }
        }
    }
}

void TilesFiguresHandler::findRookTiles(int xCord, int yCord, QColor color) {
    for(auto& [key, value] : tileFigurePairs) {
        if(key->xCord() == xCord || key->yCord() == yCord) {
            key->setPossible(true);
        }
    }
}

void TilesFiguresHandler::findQueenTiles(int xCord, int yCord, QColor color) {

}

void TilesFiguresHandler::findKingTiles(int xCord, int yCord, QColor color) {

}
