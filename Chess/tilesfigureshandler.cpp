#include "tilesfigureshandler.h"

TilesFiguresHandler::TilesFiguresHandler(QObject *parent)
    : QObject(parent), currentFigure{nullptr}, currentColorMove{"white"}, blackKing{nullptr}, whiteKing{nullptr} {}

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
            key->setContainsFigure(true);
            if(SourceFigure->type() == FigureBack::King) {
                if(SourceFigure->color() == "white") {
                    whiteKing = SourceFigure;
                } else {
                    blackKing = SourceFigure;
                }
            }
        }
    }
}

void TilesFiguresHandler::changeFigureCoords(TileBack *SourceTile, FigureBack *SourceFigure) {
    TileBack* previousTile = getTile(SourceFigure);
    previousTile->setContainsFigure(false);
    tileFigurePairs[previousTile] = nullptr;


    if(SourceTile->containsFigure()) {
        // When handler determines possible tiles it should only choose good tiles so this if condition might not be necessary
        if(tileFigurePairs[SourceTile]->color() != SourceFigure->color()) {
            tileFigurePairs[SourceTile]->setDeleteFigure(true);
        }
    }

    tileFigurePairs[SourceTile] = SourceFigure;
    SourceFigure->setXCord(SourceTile->xCord());
    SourceFigure->setYCord(SourceTile->yCord());
    SourceTile->setContainsFigure(true);
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

void TilesFiguresHandler::clearPossibleTiles() {
    for(auto& [key, value] : tileFigurePairs) {
        if(key->possible()) {
            key->setPossible(false);
            key->setKey("");
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

QColor TilesFiguresHandler::getCurrentColorMove() {
    return currentColorMove;
}

void TilesFiguresHandler::setCurrentColorMove() {
    currentColorMove = currentColorMove == "white" ? "black" : "white";
}

void TilesFiguresHandler::findValidTiles(FigureBack *SourceFigure) {

    if(SourceFigure != currentFigure) {
        clearPossibleTiles();
    }

    setCurrentFigure(SourceFigure);

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
        default: {
            // throw InvalidFigureException();  //// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
    }
}

// Function checks which figures can be moved and there won't be a check
// Rethink these two functions - maybe it can be written smarter much more smarter
// for example set two variables i and j and check both directions left and right etc
void TilesFiguresHandler::findCheckBeforeMove() {

    std::vector<FigureBack*> figuresToBlock;    // here will be stored figures that can't be moved

    if(getCurrentColorMove() == "white") {
        bool exitLoop {false};
        bool figureBlocks {false};

        for(int i {whiteKing->yCord()};i < 9;i++) {
            for(auto& [key, value] : tileFigurePairs) {
                if(key->xCord() == whiteKing->xCord() && key->yCord() == i + 1) {
                    if(value != nullptr) {
                        if(figureBlocks) {
                            if(value->color() == "black" && value->type() == FigureBack::Queen || value->type() == FigureBack::Rook) {

                            }
                        } else if(value->color() == "white") {
                            figureBlocks = true;
                            figuresToBlock.push_back(value);
                        } else {
                            // figureBlocks = true;
                            if(value->type() == FigureBack::Queen || value->type() == FigureBack::Rook) {
                                // There is already check - this situation can't happen because findCheckAfterMove() should catch it
                                // throw UnexpectedCheckException();
                            }
                            exitLoop = true;
                            break;
                        }
                    } else if(value->color() != whiteKing->color()) {
                        key->setPossible(true);
                        key->setKey(QString::number(whiteKing->xCord()) + QString::number(whiteKing->yCord()));
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
    } else {

    }
}

//Maybe the function should be executed from qml and have some variable that will unable drag when the function sets check possible
void TilesFiguresHandler::findCheckAfterMove() {
    if(getCurrentColorMove() == "white") {

    } else {

    }
}


void TilesFiguresHandler::findPawnTiles(int xCord, int yCord, QColor color) {
    if(color == "black") {
        // maybe lambda can be used
        for(auto& [key, value] : tileFigurePairs) {
            // Fix when figure is on last line
            if(key->xCord() == xCord && key->yCord() == yCord - 1 && !key->containsFigure()) {
                key->setPossible(true);
                key->setKey(QString::number(xCord) + QString::number(yCord));
            } else if((key->xCord() == xCord - 1 || key->xCord() == xCord + 1) && key->yCord() == yCord - 1) {
                if(value != nullptr) {
                    if(value->color() == "white") {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                    }
                }
            }
        }
    } else {
        for(auto& [key, value] : tileFigurePairs) {
            // Fix when figure is on last line
            if(key->xCord() == xCord && key->yCord() == yCord + 1 && !key->containsFigure()) {
                key->setPossible(true);
                key->setKey(QString::number(xCord) + QString::number(yCord));
            } else if((key->xCord() == xCord - 1 || key->xCord() == xCord + 1) && key->yCord() == yCord + 1) {
                if(value != nullptr) {
                    if(value->color() == "black") {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
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
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                } else if(value->color() != color) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
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
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                } else if(value->color() != color) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
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
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                } else if(value->color() != color) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
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
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                } else if(value->color() != color) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
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
                    key->setKey(QString::number(xCord) + QString::number(yCord));
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
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                } else if(value->color() != color) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
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
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                } else if(value->color() != color) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
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
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                } else if(value->color() != color) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
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
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                } else if(value->color() != color) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
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
                key->setKey(QString::number(xCord) + QString::number(yCord));
            }
        }
    }
}
