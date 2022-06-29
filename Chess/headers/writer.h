#ifndef WRITER_H
#define WRITER_H


#include <string>
#include <iostream>

// This class is designed to create game moves file and to save statistics (future option)
class Writer
{
private:
    std::string movesCords;
public:
    Writer();

    void addNewMove(std::string newMoveCords);
    void saveMoves();
};

#endif // WRITER_H
