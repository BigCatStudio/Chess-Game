#include "headers/tilesfigureshandler.h"

TilesFiguresHandler::TilesFiguresHandler(QObject *parent)
    : QObject(parent), currentFigure{nullptr}, currentColorMove{"white"}, blackKing{nullptr},
      whiteKing{nullptr}, selectFigureValue{false}, isCheckMateValue{false}, isDrawValue{false} {}

bool TilesFiguresHandler::selectFigure() {
    return selectFigureValue;
}

void TilesFiguresHandler::setSelectFigure(const bool &selectFigureGiven) {
    if(selectFigureGiven != selectFigureValue) {
        selectFigureValue = selectFigureGiven;
        emit selectFigureChanged();
    }
}

bool TilesFiguresHandler::isCheckMate() const {
    return isCheckMateValue;
}

void TilesFiguresHandler::setIsCheckMate(const bool &isCheckMateGiven) {
    if(isCheckMateGiven != isCheckMateValue) {
        isCheckMateValue = isCheckMateGiven;
        emit isCheckMateChanged();
    }
}

bool TilesFiguresHandler::isDraw() const {
    return isDrawValue;
}

void TilesFiguresHandler::setIsDraw(const bool &isDrawGiven) {
    if(isDrawGiven != isDrawValue) {
        isDrawValue = isDrawGiven;
        emit isDrawChanged();
    }
}

// If tile has one of staring point figures it can contain also figure address, if not set to nullptr
void TilesFiguresHandler::addTile(TileBack *SourceTile) {
    tileFigurePairs[SourceTile] = nullptr;
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
    SourceFigure->setWasMoved(true);
    SourceTile->setContainsFigure(true);

    // TODO castling changing tile for rook
//    if(SourceTile->isCastled() && SourceTile->xCord() == 7) {
//        qInfo() << "++++++++++++ About to castle +++++++++++++";
//        qInfo() << "++++++++++++ Tile: " << getTile(6, 1) << " +++++++++++++";
//        qInfo() << "++++++++++++ Figure: " << getFigure(8, 1) << " +++++++++++++";
//        changeFigureCoords(getTile(6, 1), getFigure(8, 1));
//        qInfo() << "++++++++++++ XCord:" << getFigure(6, 1)->xCord() << " YCord: " << getFigure(6, 1)->yCord();
//        SourceTile->setIsCastled(false);
//    }

    if((SourceTile->yCord() == 1 || SourceTile->yCord() == 8) && SourceFigure->type() == FigureBack::Pawn) {
        setSelectFigure(true);
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

TileBack *TilesFiguresHandler::getTile(int xCord, int yCord) {
    for(auto& [key, value] : tileFigurePairs) {
        if(key->xCord() == xCord && key->yCord() == yCord) {
            return key;
        }
    }
    return nullptr;
}

FigureBack *TilesFiguresHandler::getFigure(int xCord, int yCord) {
    for(auto& [key, value] : tileFigurePairs) {
        if(value->xCord() == xCord && value->yCord() == yCord) {
            return value;
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

void TilesFiguresHandler::clearCastledTiles() {
    // These are the only possible tiles for kings during castling
    getTile(3, 1)->setIsCastled(false);
    getTile(7, 1)->setIsCastled(false);
    getTile(3, 8)->setIsCastled(false);
    getTile(7, 8)->setIsCastled(false);
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

int TilesFiguresHandler::findValidTiles(FigureBack *SourceFigure) {
    int moves {0};
    if(SourceFigure != currentFigure) {
        clearPossibleTiles();
    }

    setCurrentFigure(SourceFigure);

    // TODO clears castled tiles
//    clearCastledTiles();

    switch(SourceFigure->type()) {
        case FigureBack::Pawn: {
            moves = findPawnTiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color(), SourceFigure);
            break;
        }
        case FigureBack::Bishop: {
            moves = findBishopTiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color(), SourceFigure);
            break;
        }
        case FigureBack::Knight: {
            moves = findKnightiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color(), SourceFigure);
            break;
        }
        case FigureBack::Rook: {
            moves = findRookTiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color(), SourceFigure);
            break;
        }
        case FigureBack::Queen: {
            moves = findQueenTiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color(), SourceFigure);
            break;
        }
        case FigureBack::King: {
            moves = findKingTiles(SourceFigure->xCord(), SourceFigure->yCord(), SourceFigure->color(), SourceFigure);
            break;
        }
        default: {
            // throw InvalidFigureException();  //// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
    }
    return moves;
}

// Function checks which figures can be moved and there won't be a check
// Rethink these two functions - maybe it can be written smarter much more smarter
// For example set two variables i and j and check both directions left and right etc
bool TilesFiguresHandler::findCheckBeforeMove(int xCord, int yCord, QColor color, TileBack* SourceTile, FigureBack* SourceFigure) {
    // Setting figure in new postition just to calculate possible checks and at the end it is returned to original tile
    FigureBack* figureReplacement = nullptr;
    for(auto& [key, value] : tileFigurePairs) {
        if(key->xCord() == xCord && key->yCord() == yCord) {
            tileFigurePairs[key] = nullptr;
            if(SourceTile->containsFigure()) {
                figureReplacement = tileFigurePairs[SourceTile];
                tileFigurePairs[SourceTile] = nullptr;
            }
            tileFigurePairs[SourceTile] = SourceFigure;
            break;
        }
    }

    FigureBack* kingFigure = getCurrentColorMove() == "white" ? whiteKing : blackKing;
    int kingXCord = kingFigure->xCord();
    int kingYCord = kingFigure->yCord();

    if(SourceFigure->type() == FigureBack::King) {
        kingFigure->setXCord(SourceTile->xCord());
        kingFigure->setYCord(SourceTile->yCord());
    }

    QColor kingColor = getCurrentColorMove() == "white" ? "black" : "white";
    bool tilePossible = true;

    /********************************************/
    // This part checks in all directions

    std::vector<FigureBack*> figuresChecking;

    // Rook/Queen movement checking
    bool exitLoop {false};
    for(int i {kingFigure->yCord()};i < 9;i++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == kingFigure->xCord() && key->yCord() == i + 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Rook) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int i {kingFigure->yCord()};i > 0;i--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == kingFigure->xCord() && key->yCord() == i - 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Rook) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int i {kingFigure->xCord()};i < 9;i++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == i + 1 && key->yCord() == kingFigure->yCord()) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Rook) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int i {kingFigure->xCord()};i > 0;i--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == i - 1 && key->yCord() == kingFigure->yCord()) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Rook) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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

    // Bishop movement checking
    exitLoop = false;
    for(int x {kingFigure->xCord()}, y {kingFigure->yCord()};x < 9 && y < 9;x++, y++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x + 1 && key->yCord() == y + 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Bishop) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int x {kingFigure->xCord()}, y {kingFigure->yCord()};x > 0 && y > 0;x--, y--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x - 1 && key->yCord() == y - 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Bishop) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int x {kingFigure->xCord()}, y {kingFigure->yCord()};x < 9 && y > 0;x++, y--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x + 1 && key->yCord() == y - 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Bishop) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int x {kingFigure->xCord()}, y {kingFigure->yCord()};x > 0 && y < 9;x--, y++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x - 1 && key->yCord() == y + 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Bishop) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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

    // Knight movement checking
    std::vector<std::pair<int, int>> possibleCords;
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() - 2, kingFigure->yCord() + 1});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() - 2, kingFigure->yCord() - 1});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() - 1, kingFigure->yCord() + 2});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() - 1, kingFigure->yCord() - 2});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() + 1, kingFigure->yCord() + 2});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() + 1, kingFigure->yCord() - 2});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() + 2, kingFigure->yCord() + 1});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() + 2, kingFigure->yCord() - 1});

    for(auto& [key, value] : tileFigurePairs) {
        for(auto &pair : possibleCords) {
            if(key->xCord() == pair.first && key->yCord() == pair.second) {
                if(value != nullptr) {
                    if(value->type() == FigureBack::Knight && value->color() == kingColor) {
                        figuresChecking.push_back(value);
                    }
                }
                break;
            }
        }
    }

    // Pawn movement checking
    if(kingColor == "black") {
        for(auto& [key, value] : tileFigurePairs) {
            if((key->xCord() == kingFigure->xCord() - 1 || key->xCord() == kingFigure->xCord() + 1) && key->yCord() == kingFigure->yCord() + 1) {
                if(value != nullptr) {
                    if(value->type() == FigureBack::Pawn && value->color() == kingColor){
                        figuresChecking.push_back(value);
                    }
                }
            }
        }
    } else {
        for(auto& [key, value] : tileFigurePairs) {
            if((key->xCord() == kingFigure->xCord() - 1 || key->xCord() == kingFigure->xCord() + 1) && key->yCord() == kingFigure->yCord() - 1) {
                if(value != nullptr) {
                    if(value->type() == FigureBack::Pawn && value->color() == kingColor){
                        figuresChecking.push_back(value);
                    }
                }
            }
        }
    }

    // King movement checking
    for(auto& [key, value] : tileFigurePairs) {
        if(value != nullptr) {
            if((key->xCord() == kingFigure->xCord() || key->xCord() == kingFigure->xCord() + 1 || key->xCord() == kingFigure->xCord() - 1) && (key->yCord() == kingFigure->yCord() || key->yCord() == kingFigure->yCord() + 1 || key->yCord() == kingFigure->yCord() - 1)) {
                if(key->xCord() != kingFigure->xCord() || key->yCord() != kingFigure->yCord()) {
                    if(value->type() == FigureBack::King) {
                        figuresChecking.push_back(value);
                    }
                }
            }
        }

    }

    /********************************************/

    if(!figuresChecking.empty()) {
        tilePossible = false;
//        std::for_each(figuresChecking.begin(), figuresChecking.end(), [](FigureBack* pointer){qInfo() << pointer->type();});
    }

    // Reversing figures position
    for(auto& [key, value] : tileFigurePairs) {
        if(key->xCord() == xCord && key->yCord() == yCord) {
            tileFigurePairs[key] = SourceFigure;
            tileFigurePairs[SourceTile] = figureReplacement;
            break;
        }
    }

    if(SourceFigure->type() == FigureBack::King) {
        kingFigure->setXCord(kingXCord);
        kingFigure->setYCord(kingYCord);
    }

    return tilePossible;
}

//Maybe the function should be executed from qml and have some variable that will unable drag when the function sets check possible
void TilesFiguresHandler::findCheckAfterMove() {
    FigureBack* kingFigure = getCurrentColorMove() == "white" ? blackKing : whiteKing;
    QColor kingColor = getCurrentColorMove();

    // This part resets tiles that are checked and kings attributes
    for(auto &[key, value] : tileFigurePairs) {
        if(key->isChecked()) {
            key->setIsChecked(false);
        }
    }
    whiteKing->setIsChecked(false);
    blackKing->setIsChecked(false);

    //****************************************

    std::vector<FigureBack*> figuresChecking;

    // Rook/Queen movement checking
    bool exitLoop {false};
    for(int i {kingFigure->yCord()};i < 9;i++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == kingFigure->xCord() && key->yCord() == i + 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Rook) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int i {kingFigure->yCord()};i > 0;i--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == kingFigure->xCord() && key->yCord() == i - 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Rook) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int i {kingFigure->xCord()};i < 9;i++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == i + 1 && key->yCord() == kingFigure->yCord()) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Rook) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int i {kingFigure->xCord()};i > 0;i--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == i - 1 && key->yCord() == kingFigure->yCord()) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Rook) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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

    // Bishop movement checking
    exitLoop = false;
    for(int x {kingFigure->xCord()}, y {kingFigure->yCord()};x < 9 && y < 9;x++, y++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x + 1 && key->yCord() == y + 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Bishop) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int x {kingFigure->xCord()}, y {kingFigure->yCord()};x > 0 && y > 0;x--, y--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x - 1 && key->yCord() == y - 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Bishop) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int x {kingFigure->xCord()}, y {kingFigure->yCord()};x < 9 && y > 0;x++, y--) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x + 1 && key->yCord() == y - 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Bishop) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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
    for(int x {kingFigure->xCord()}, y {kingFigure->yCord()};x > 0 && y < 9;x--, y++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x - 1 && key->yCord() == y + 1) {
                if(value == nullptr) {
                } else if((value->type() == FigureBack::Queen || value->type() == FigureBack::Bishop) && value->color() == kingColor) {
                    figuresChecking.push_back(value);
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

    // Knight movement checking
    std::vector<std::pair<int, int>> possibleCords;
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() - 2, kingFigure->yCord() + 1});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() - 2, kingFigure->yCord() - 1});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() - 1, kingFigure->yCord() + 2});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() - 1, kingFigure->yCord() - 2});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() + 1, kingFigure->yCord() + 2});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() + 1, kingFigure->yCord() - 2});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() + 2, kingFigure->yCord() + 1});
    possibleCords.push_back(std::pair<int,int> {kingFigure->xCord() + 2, kingFigure->yCord() - 1});

    for(auto& [key, value] : tileFigurePairs) {
        for(auto &pair : possibleCords) {
            if(key->xCord() == pair.first && key->yCord() == pair.second) {
                if(value != nullptr) {
                    if(value->type() == FigureBack::Knight && value->color() == kingColor) {
                        figuresChecking.push_back(value);
                    }
                }
                break;
            }
        }
    }

    // Pawn movement checking
    if(kingColor == "black") {
        // maybe lambda can be used
        for(auto& [key, value] : tileFigurePairs) {
            if((key->xCord() == kingFigure->xCord() - 1 || key->xCord() == kingFigure->xCord() + 1) && key->yCord() == kingFigure->yCord() + 1) {
                if(value != nullptr) {
                    if(value->type() == FigureBack::Pawn && value->color() == kingColor){
                        figuresChecking.push_back(value);
                    }
                }
            }
        }
    } else {
        for(auto& [key, value] : tileFigurePairs) {
            if((key->xCord() == kingFigure->xCord() - 1 || key->xCord() == kingFigure->xCord() + 1) && key->yCord() == kingFigure->yCord() - 1) {
                if(value != nullptr) {
                    if(value->type() == FigureBack::Pawn && value->color() == kingColor){
                        figuresChecking.push_back(value);
                    }
                }
            }
        }
    }

    // King movement checking
    for(auto& [key, value] : tileFigurePairs) {
        if(value != nullptr) {
            if((key->xCord() == kingFigure->xCord() || key->xCord() == kingFigure->xCord() + 1 || key->xCord() == kingFigure->xCord() - 1) && (key->yCord() == kingFigure->yCord() || key->yCord() == kingFigure->yCord() + 1 || key->yCord() == kingFigure->yCord() - 1)) {
                if(key->xCord() != kingFigure->xCord() || key->yCord() != kingFigure->yCord()) {
                    if(value->type() == FigureBack::King) {
                        figuresChecking.push_back(value);
                    }
                }
            }
        }

    }

    //*****************************************************************

    if(!figuresChecking.empty()) {
        for(auto& [key, value] : tileFigurePairs) {
            if(value == kingFigure) {
                key->setIsChecked(true);
                if(getCurrentColorMove() == "white") {
                    blackKing->setIsChecked(true);
                } else {
                    whiteKing->setIsChecked(true);
                }
            }
        }
//        std::for_each(figuresChecking.begin(), figuresChecking.end(), [](FigureBack* pointer){qInfo() << pointer->type();});
    }

    figuresChecking.clear();
    figuresChecking.resize(0);
}

void TilesFiguresHandler::findCheckMate() {
    QString currentColor = getCurrentColorMove() == "white" ? "white" : "black";
    FigureBack* currentKing = getCurrentColorMove() == "white" ? whiteKing : blackKing;

    if(currentKing->isChecked()) {
        int moves {0};
        for(auto& [key, value] : tileFigurePairs) {
            if(value != nullptr) {
                if(value->color() == getCurrentColorMove()) {
                    moves += findValidTiles(value);
                    clearPossibleTiles();
                }
            }
        }
        if(moves == 0) {
            setIsCheckMate(true);
        }
    } else {
        int moves {0};
        for(auto& [key, value] : tileFigurePairs) {
            if(value != nullptr) {
                if(value->color() == getCurrentColorMove()) {
                    moves += findValidTiles(value);
                    clearPossibleTiles();
                }
            }
        }
        if(moves == 0) {
            setIsDraw(true);
        }
    }
}

QString TilesFiguresHandler::winnerColor() const {
    if(whiteKing->isChecked()) {
        return "Black";
    } else {
        return "White";
    }
}

void TilesFiguresHandler::setSelectedFigure(int typeGiven, QString sourceGiven) {
    for(auto &[key, value] : tileFigurePairs) {
        if(value != nullptr) {
            if(value->type() == FigureBack::Pawn && (value->yCord() == 1 || value->yCord() == 8)) {
                value->setType(typeGiven);
                value->setImageSource(sourceGiven);
                setSelectFigure(false);
            }
        }
    }
}

int TilesFiguresHandler::findPawnTiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure) {
    int moves {0};
    if(color == "black") {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == xCord && (key->yCord() == yCord - 1 || (key->yCord() == yCord - 2 && !SourceFigure->wasMoved())) && !key->containsFigure()) {
                if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                    moves++;
                }
            } else if((key->xCord() == xCord - 1 || key->xCord() == xCord + 1) && key->yCord() == yCord - 1) {
                if(value != nullptr) {
                    if(value->color() == "white") {
                        if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                            key->setPossible(true);
                            key->setKey(QString::number(xCord) + QString::number(yCord));
                            moves++;
                        }
                    }
                }
            }
        }
    } else {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == xCord && (key->yCord() == yCord + 1 || (key->yCord() == yCord + 2 && !SourceFigure->wasMoved())) && !key->containsFigure()) {
                if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                    moves++;
                }
            } else if((key->xCord() == xCord - 1 || key->xCord() == xCord + 1) && key->yCord() == yCord + 1) {
                if(value != nullptr) {
                    if(value->color() == "black") {
                        if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                            key->setPossible(true);
                            key->setKey(QString::number(xCord) + QString::number(yCord));
                            moves++;
                        }
                    }
                }
            }
        }
    }
    return moves;
}

int TilesFiguresHandler::findBishopTiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure) {
    bool exitLoop {false};
    int moves {0};

    for(int x {xCord}, y {yCord};x < 9 && y < 9;x++, y++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == x + 1 && key->yCord() == y + 1) {
                if(value == nullptr) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                    }
                } else if(value->color() != color) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                        exitLoop = true;
                    }
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
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                    }
                } else if(value->color() != color) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                        exitLoop = true;
                    }
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
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                    }
                } else if(value->color() != color) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                        exitLoop = true;
                    }
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
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                    }
                } else if(value->color() != color) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                        exitLoop = true;
                    }
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
    return moves;
}

int TilesFiguresHandler::findKnightiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure) {
    std::vector<std::pair<int, int>> possibleCords;
    int moves {0};
    // Improve searching and delete pairs that are not available before searching

    possibleCords.push_back(std::pair<int,int> {xCord - 2, yCord + 1});
    possibleCords.push_back(std::pair<int,int> {xCord - 2, yCord - 1});
    possibleCords.push_back(std::pair<int,int> {xCord - 1, yCord + 2});
    possibleCords.push_back(std::pair<int,int> {xCord - 1, yCord - 2});
    possibleCords.push_back(std::pair<int,int> {xCord + 1, yCord + 2});
    possibleCords.push_back(std::pair<int,int> {xCord + 1, yCord - 2});
    possibleCords.push_back(std::pair<int,int> {xCord + 2, yCord + 1});
    possibleCords.push_back(std::pair<int,int> {xCord + 2, yCord - 1});

    // Error when placing horse on horse more than one time but does not get place during real game

    for(auto& [key, value] : tileFigurePairs) {
        for(auto &pair : possibleCords) {
            if(key->xCord() == pair.first && key->yCord() == pair.second) {
                if(value == nullptr || value->color() != color) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                    }
                }
                break;
            }
        }
    }
    return moves;
}

int TilesFiguresHandler::findRookTiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure) {
    int moves {0};
    // Whole rook functionality can be for sure improved much more - think about it !!!

    bool exitLoop {false};
    for(int i {yCord};i < 9;i++) {
        for(auto& [key, value] : tileFigurePairs) {
            if(key->xCord() == xCord && key->yCord() == i + 1) {
                if(value == nullptr) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                    }
                } else if(value->color() != color) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                        exitLoop = true;
                    }
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
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                    }
                } else if(value->color() != color) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                        exitLoop = true;
                    }
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
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                    }
                } else if(value->color() != color) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                        exitLoop = true;
                    }
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
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                    }
                } else if(value->color() != color) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                        exitLoop = true;
                    }
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
    return moves;
}

int TilesFiguresHandler::findQueenTiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure) {
    return findKingTiles(xCord, yCord, color, SourceFigure) +
           findRookTiles(xCord, yCord, color, SourceFigure) +
           findBishopTiles(xCord, yCord, color, SourceFigure);
}

int TilesFiguresHandler::findKingTiles(int xCord, int yCord, QColor color, FigureBack* SourceFigure) {
    int moves {0};
    for(auto& [key, value] : tileFigurePairs) {
        if((key->xCord() == xCord || key->xCord() == xCord + 1 || key->xCord() == xCord - 1) && (key->yCord() == yCord || key->yCord() == yCord + 1 || key->yCord() == yCord - 1)) {
            if(key->xCord() != xCord || key->yCord() != yCord) {
                if(value == nullptr || value->color() != color) {
                    if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                        key->setPossible(true);
                        key->setKey(QString::number(xCord) + QString::number(yCord));
                        moves++;
                    }
                }
            }
        }
    }

    // Checks castling
    // TODO currently there is problem with generating key for rooks tile. I think there should be added new key to the tile also for rook
//    if(!SourceFigure->wasMoved()) {
//        if(tileFigurePairs[getTile(8, 1)] != nullptr) {
//            if(!tileFigurePairs[getTile(8, 1)]->wasMoved()) {
//                bool canCastle {true};
//                for(int i {xCord};i <= xCord + 2;i++) {
//                    for(auto& [key, value] : tileFigurePairs) {
//                        if(key->xCord() == i && key->yCord() == 1) {
//                            if(!findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
//                                canCastle = false;
//                            }
//                        }
//                    }
//                }

//                if(canCastle) {
//                    for(auto& [key, value] : tileFigurePairs) {
//                        if(key->xCord() == xCord + 2 && key->yCord() == 1) {
//                            key->setPossible(true);
//                            key->setKey(QString::number(xCord) + QString::number(yCord));
//                            key->setIsCastled(true);
//                            getTile(6, 1)->setIsRookCastled("81");
//                            moves++;
//                        }
//                    }
//                }
//            } else if(!tileFigurePairs[getTile(1, 1)]->wasMoved()) {
//                bool canCastle {true};
//                for(int i {xCord};i >= xCord - 2;i--) {
//                    for(auto& [key, value] : tileFigurePairs) {
//                        if(key->xCord() == i && key->yCord() == 1) {
//                            if(!findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
//                                canCastle = false;
//                            }
//                        }
//                    }
//                }

//                if(canCastle) {
//                    for(auto& [key, value] : tileFigurePairs) {
//                        if(key->xCord() == xCord - 2 && key->yCord() == 1) {
//                            key->setPossible(true);
//                            key->setKey(QString::number(xCord) + QString::number(yCord));
//                            key->setIsCastled(true);
//                            getTile(4, 1)->setIsRookCastled("11");
//                            moves++;
//                        }
//                    }
//                }
//            }
//        }
//    }
    return moves;
}
