#include <iostream>
#include "mazeBoard.h"

int main(int argc, char *argv[]) {
    if(argc != 3) {
        std::cout<<"Invalid number of arguments.";
        exit(1);
    }
    int row = std::stoi(argv[1]);
    int col = std::stoi(argv[2]);

    mazeBoard(row,col);

    return 0;
}
