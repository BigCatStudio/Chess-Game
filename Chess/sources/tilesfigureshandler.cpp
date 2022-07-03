#include "headers/tilesfigureshandler.h"

TilesFiguresHandler::TilesFiguresHandler(QObject *parent)
    : QObject(parent), currentFigure{nullptr}, currentColorMove{"white"}, blackKing{nullptr},
      whiteKing{nullptr}, selectFigureValue{false}, isCheckMateValue{false} {}

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
    SourceFigure->setWasMoved(true);
    SourceTile->setContainsFigure(true);

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

int TilesFiguresHandler::findValidTiles(FigureBack *SourceFigure) {
    int moves {0};
    if(SourceFigure != currentFigure) {
        clearPossibleTiles();
    }

    setCurrentFigure(SourceFigure);

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
// for example set two variables i and j and check both directions left and right etc
bool TilesFiguresHandler::findCheckBeforeMove(int xCord, int yCord, QColor color, TileBack * SourceTile, FigureBack* SourceFigure) {
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

    qInfo() << "Looking for check for " << getCurrentColorMove();
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

    if(!figuresChecking.empty()) {
        tilePossible = false;
        qInfo() << "there is check for " << kingColor;
        std::for_each(figuresChecking.begin(), figuresChecking.end(), [](FigureBack* pointer){qInfo() << pointer->type();});
    }
    /********************************************/

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

    qInfo() << "Looking for check for " << kingColor;

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

        qInfo() << "there is check for " << kingColor;
        std::for_each(figuresChecking.begin(), figuresChecking.end(), [](FigureBack* pointer){qInfo() << pointer->type();});
    }

    figuresChecking.clear();
    figuresChecking.resize(0);
}

void TilesFiguresHandler::findCheckMate() {

    FigureBack* currentKing = getCurrentColorMove() == "white" ? whiteKing : blackKing;
    qInfo() << "white king:" << whiteKing->isChecked() << " blackKing:" << blackKing->isChecked();
    if(currentKing->isChecked()) {
        qInfo() << "******** Looking for Check Mate ********";
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
            qInfo() << "******** Check Mate ********";
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
    qInfo() << "---- In setSelectedFigure ----";
    for(auto &[key, value] : tileFigurePairs) {
        if(value != nullptr) {
            if(value->type() == FigureBack::Pawn && (value->yCord() == 1 || value->yCord() == 8)) {
                qInfo() << typeGiven;
                qInfo() << sourceGiven;
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
        // maybe lambda can be used
        for(auto& [key, value] : tileFigurePairs) {
            // Fix when figure is on last line
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
            // Fix when figure is on last line
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

    // Error when placing horse on horse more than one time does not get place during real game

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
            if(value == nullptr || value->color() != color) {
                if(findCheckBeforeMove(xCord, yCord, color, key, SourceFigure)) {
                    key->setPossible(true);
                    key->setKey(QString::number(xCord) + QString::number(yCord));
                    moves++;
                }
            }
        }
    }
    return moves;
}
