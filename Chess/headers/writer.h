#ifndef WRITER_H
#define WRITER_H


#include <string>
#include <iostream>

// TODO This class is designed to create game moves file and to save statistics (future option)
class Writer
{
private:
    std::string movesCords;
public:
    Writer();

    void addNewMove(std::string newMoveCords); // New moves will be send as strings and added to one long string containing all moves
                                               // this solution helps to avoid opening and closing file many times
    void saveMoves();
};

#endif // WRITER_H
