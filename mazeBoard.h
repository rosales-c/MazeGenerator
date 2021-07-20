//
// Created by Cinthya Drake on 11/23/20.
//

#ifndef MAZEPROJECT_MAZEBOARD_H
#define MAZEPROJECT_MAZEBOARD_H

#include<vector>
#include <time.h>


class mazeBoard {
public:
    mazeBoard(int,int);
    ~mazeBoard();

    void base();
    void printBoard(std::vector<std::vector<int>>) const;
    void weightedBoard(int,int);
    void fillKruskals();
    void setRand();
    void setStartEnd();
    void primsMaze(int);
    void pushRightWeight(int,int);
    void pushLeftWeight(int,int);
    void pushTopWeight(int,int);
    void pushBottomWeight(int,int);
    void fixedUnusedWeightsPrims();
    void kruskalsMaze();
    void pushRightKrus(int,int);
    void pushBottomKrus(int,int);
    void fixedUnusedWeightsKrus();
    bool buildKrusAdjMat(int,int);
    void setVertZero();
    bool solvePrims(int, int);
    bool solveKruskals(int, int);
    void setTrack(std::vector<std::vector<int>>);


private:
    int rows,cols, rndStart, rndEnd, startPoint, endPoint,leftTop,rightBot, startRow, startCol, endRow, endCol;
    std::vector<bool> visited;
    std::vector<std::vector<int>> primsBoard;
    std::vector<std::vector<int>> kruskalsBoard;
    std::vector<std::vector<int>> weights;
    std::vector<std::vector<int>> kwghts;
    std::vector<std::vector<int>> krusAdjMat;
    std::vector<std::vector<bool>>track;
};


#endif //MAZEPROJECT_MAZEBOARD_H
