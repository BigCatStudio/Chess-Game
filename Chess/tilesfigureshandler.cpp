#include "tilesfigureshandler.h"

TilesFiguresHandler::TilesFiguresHandler(QObject *parent)
    : QObject(parent), currentFigure{nullptr}, currentColorMove{"white"} {}

// If tile has one of staring point figures it can contain also figure address
// if not set to nullptr
void TilesFiguresHandler::addTile(TileBack *SourceTile) {
    tileFigurePairs[SourceTile] = nullptr;

    qInfo() << SourceTile << ": " << SourceTile->xCord() << "x" << SourceTile->yCord();
}

void TilesFiguresHandler::addFigure(FigureBack *SourceFigure) {
    for(auto& [key, value] : tileFigurePairs) {
        if(key->xCord() == SourceFigure->xCord() && key->yCord() == SourceFigure->yCord()) {
            value = SourceFigure;
        }
    }

    // Iterates over map and checks if tile without figure has its value set to nullptr
    // It must be checked atfer figure is moved from one tile to another so that instance of that figure will not be
    // on more than one tile
    for(auto& [key, value] : tileFigurePairs) {
        if(!key->containsFigure() && value != nullptr) {
            value = nullptr;
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

TileBack *TilesFiguresHandler::getTile(int xCord, int yCord) const {
    for(auto& [key, value] : tileFigurePairs) {
        if(key->xCord() == xCord && key->yCord() == yCord) {
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

QColor TilesFiguresHandler::getCurrentColorMove() {
    return currentColorMove;
}

void TilesFiguresHandler::setCurrentColorMove() {
    currentColorMove = currentColorMove == "white" ? "black" : "white";
} 

void TilesFiguresHandler::findPawnTiles(int xCord, int yCord, QColor color) {
    if(color == "black") {
        // maybe lambda can be used
        for(auto& [key, value] : tileFigurePairs) {
            // Fix when figure is on last line
            if(key->xCord() == xCord && key->yCord() == yCord - 1) {
                key->setPossible(true);
            } else if((key->xCord() == xCord - 1 || key->xCord() == xCord + 1) && key->yCord() == yCord - 1) {
                if(value != nullptr) {
                    if(value->color() == "white") {
                        key->setPossible(true);
                    }
                }
            }
        }
    } else {
        for(auto& [key, value] : tileFigurePairs) {
            // Fix when figure is on last line
            if(key->xCord() == xCord && key->yCord() == yCord + 1) {
                key->setPossible(true);
            } else if((key->xCord() == xCord - 1 || key->xCord() == xCord + 1) && key->yCord() == yCord + 1) {
                if(value != nullptr) {
                    if(value->color() == "black") {
                        key->setPossible(true);
                    }
                }
            }
        }
    }
}

void TilesFiguresHandler::findBishopTiles(int xCord, int yCord, QColor color) {
    bool exitLoop {false};
    for(int x {xCord}, y {yCord};x < 9 && y < 9;x++, y++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x + 1 && key->yCord() == y + 1) {
                if(value == nullptr) {
                    key->setPossible(true);
                } else if(value->color() != color) {
                    key->setPossible(true);
                    exitLoop = true;
                } else {
                    exitLoop = true;
                }
                break;
            }
        }
        if(exitLoop) {
            break;
        }
    }

    exitLoop = false;
    for(int x {xCord}, y {yCord};x > 0 && y > 0;x--, y--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x - 1 && key->yCord() == y - 1) {
                if(value == nullptr) {
                    key->setPossible(true);
                } else if(value->color() != color) {
                    key->setPossible(true);
                    exitLoop = true;
                } else {
                    exitLoop = true;
                }
                break;
            }
        }
        if(exitLoop) {
            break;
        }
    }

    exitLoop = false;
    for(int x {xCord}, y {yCord};x < 9 && y > 0;x++, y--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x + 1 && key->yCord() == y - 1) {
                if(value == nullptr) {
                    key->setPossible(true);
                } else if(value->color() != color) {
                    key->setPossible(true);
                    exitLoop = true;
                } else {
                    exitLoop = true;
                }
                break;
            }
        }
        if(exitLoop) {
            break;
        }
    }

    exitLoop = false;
    for(int x {xCord}, y {yCord};x > 0 && y < 9;x--, y++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x - 1 && key->yCord() == y + 1) {
                if(value == nullptr) {
                    key->setPossible(true);
                } else if(value->color() != color) {
                    key->setPossible(true);
                    exitLoop = true;
                } else {
                    exitLoop = true;
                }
                break;
            }
        }
        if(exitLoop) {
            break;
        }
    }
}

void TilesFiguresHandler::findKnightiles(int xCord, int yCord, QColor color) {
    std::vector<std::pair<int, int>> possibleCords;

    // Improve searching and delete pairs that are not available before searching

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

    // Whole rook functionality can be for sure improved much more - think about it !!!

    bool exitLoop {false};
    for(int i {yCord};i < 9;i++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == xCord && key->yCord() == i + 1) {
                if(value == nullptr) {
                    key->setPossible(true);
                } else if(value->color() != color) {
                    key->setPossible(true);
                    exitLoop = true;
                } else {
                    exitLoop = true;
                }
                break;
            }
        }
        if(exitLoop) {
            break;
        }
    }

    exitLoop = false;
    for(int i {yCord};i > 0;i--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == xCord && key->yCord() == i - 1) {
                if(value == nullptr) {
                    key->setPossible(true);
                } else if(value->color() != color) {
                    key->setPossible(true);
                    exitLoop = true;
                } else {
                    exitLoop = true;
                }
                break;
            }
        }
        if(exitLoop) {
            break;
        }
    }

    exitLoop = false;
    for(int i {xCord};i < 9;i++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == i + 1 && key->yCord() == yCord) {
                if(value == nullptr) {
                    key->setPossible(true);
                } else if(value->color() != color) {
                    key->setPossible(true);
                    exitLoop = true;
                } else {
                    exitLoop = true;
                }
                break;
            }
        }
        if(exitLoop) {
            break;
        }
    }

    exitLoop = false;
    for(int i {xCord};i > 0;i--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == i - 1 && key->yCord() == yCord) {
                if(value == nullptr) {
                    key->setPossible(true);
                } else if(value->color() != color) {
                    key->setPossible(true);
                    exitLoop = true;
                } else {
                    exitLoop = true;
                }
                break;
            }
        }
        if(exitLoop) {
            break;
        }
    }
}

void TilesFiguresHandler::findQueenTiles(int xCord, int yCord, QColor color) {
    findKingTiles(xCord, yCord, color);
    findRookTiles(xCord, yCord, color);
    findBishopTiles(xCord, yCord, color);
}

void TilesFiguresHandler::findKingTiles(int xCord, int yCord, QColor color) {
    for(auto& [key, value] : tileFigurePairs) {
        if((key->xCord() == xCord || key->xCord() == xCord + 1 || key->xCord() == xCord - 1) && (key->yCord() == yCord || key->yCord() == yCord + 1 || key->yCord() == yCord - 1)) {
            if(value == nullptr || value->color() != color) {
                key->setPossible(true);
            }
        }
    }
}
