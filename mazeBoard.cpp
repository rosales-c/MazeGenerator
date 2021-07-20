//
// Created by Cinthya Drake on 11/23/20.
//

#include "mazeBoard.h"
#include <iostream>

mazeBoard::mazeBoard(int row, int col){
    rows = 2*row + 1;
    cols = 2*col + 1;
    base();
    setRand();
    weightedBoard(rndStart, rndEnd);
    setStartEnd();
    fillKruskals();
    primsMaze(startPoint);
    std::cout << "\n Prim's Maze\n";
    printBoard(primsBoard);
    setTrack(primsBoard);
    bool solved = solvePrims(startRow, startCol);
    std::cout << "\n Prim's Maze Solved\n";
    printBoard(primsBoard);
    kruskalsMaze();
    solved = solveKruskals(startRow, startCol);
    std::cout << "\n Kruskal's Maze \n";
    printBoard(kruskalsBoard);
    track.clear();
    setTrack(kruskalsBoard);
    solved = solveKruskals(startRow, startCol);
    std::cout << "\n Kruskal's Maze Solved \n";
    printBoard(kruskalsBoard);
}

mazeBoard::~mazeBoard() {}

void mazeBoard::base() {
    int r = rows;
    int c = cols;
    int path = 0;
    int edge = 1;
    std::vector<int> R;
    visited.push_back(true);

    for(int i=0; i<r; i++){
        for(int k=0; k<c; k++){
            if(i!=0 && i!=r-1 && k!=0 && k%2!=0 && i%2!=0){
                path = path + 1;
                R.push_back(path);
                visited.push_back(false);
            }
            else{
                R.push_back(edge);
            }
        }
        primsBoard.push_back(R);
        R.clear();
    }
}

void mazeBoard::setRand() {
    srand(time(NULL));
    int num;
    if(rows < cols)
        num = rows-3;
    else
        num = cols-3;
    startPoint = rand() %num;
    endPoint = rand() %num;
    if(startPoint%2 == 0){
        startPoint = startPoint + 1;
    }
    if(endPoint%2 == 0){
        endPoint = endPoint + 1;
    }

    rndStart = rand() % 12 + 2;
    rndEnd = rand() % 12 + 80;
    while(rndStart == rndEnd){
        rndEnd = rand() % 90 + 50;
    }
    leftTop = rand() % 2;
    rightBot = rand() % 2;
}

void mazeBoard::weightedBoard(int start, int end) {
    std::vector<int> tempVec;
    for(int i=1; i<=rows-2; i+=2){
        for(int k=1; k<=cols-2; k+=2){
            if(i==1){
                if(k==1){
                    int rightWeight = rand() % end + start;
                    primsBoard.at(i).at(k+1) = rightWeight;
                    pushRightKrus(i,k);

                    int bottomWeight = rand() % end + start;
                    primsBoard.at(i+1).at(k) = bottomWeight;
                    pushBottomKrus(i,k);
                }
                else if(k==cols-2){
                    int bottomWeight = rand() % end + start;
                    primsBoard.at(i+1).at(k) = bottomWeight;
                    pushBottomKrus(i,k);
                }
                else{
                    int rightWeight = rand() % end + start;
                    primsBoard.at(i).at(k+1) = rightWeight;
                    pushRightKrus(i,k);

                    int bottomWeight = rand() % end + start;
                    primsBoard.at(i+1).at(k) = bottomWeight;
                    pushBottomKrus(i,k);
                }
            }
            else if(i==rows-2){
                if(k==0){
                    int rightWeight = rand() % end + start;
                    primsBoard.at(i).at(k+1) = rightWeight;
                    pushRightKrus(i,k);
                }
                else if(k==cols-2){
                    continue;
                }
                else{
                    int rightWeight = rand() % end + start;
                    primsBoard.at(i).at(k+1) = rightWeight;
                    pushRightKrus(i,k);
                }
            }
            else{
                if(k==1){
                    int rightWeight = rand() % end + start;
                    primsBoard.at(i).at(k+1) = rightWeight;
                    pushRightKrus(i,k);

                    int bottomWeight = rand() % end + start;
                    primsBoard.at(i+1).at(k) = bottomWeight;
                    pushBottomKrus(i,k);
                }
                else if(k==cols-2){
                    int bottomWeight = rand() % end + start;
                    primsBoard.at(i+1).at(k) = bottomWeight;
                    pushBottomKrus(i,k);
                }
                else{
                    int rightWeight = rand() % end + start;
                    primsBoard.at(i).at(k+1) = rightWeight;
                    pushRightKrus(i,k);

                    int bottomWeight = rand() % end + start;
                    primsBoard.at(i+1).at(k) = bottomWeight;
                    pushBottomKrus(i,k);
                }
            }
        }
    }
}

void mazeBoard::setStartEnd() {
    if(leftTop == 0) {
        primsBoard.at(startPoint).at(0) = 0;
        startRow = startPoint;
        startCol = 0;
    }
    else{
        primsBoard.at(0).at(startPoint) = 0;
        startRow = 0;
        startCol = startPoint;
    }

    if(rightBot == 0) {
        primsBoard.at(endPoint).at(cols - 1) = 0;
        endRow = endPoint;
        endCol = cols-1;
    }
    else{
        primsBoard.at(rows - 1).at(endPoint) = 0;
        endRow = rows-1;
        endCol = endPoint;
    }
}

void mazeBoard::fillKruskals() {
    std::vector<int> temp(cols);
    for(int i=0; i<rows; i++){
        kruskalsBoard.push_back(temp);
    }
    kruskalsBoard=primsBoard;
}

void mazeBoard::primsMaze(int start) {
    int smallest = 10000;
    int s;
    int r = start;
    int c = 1;
    int WR, WC;
    int size = visited.size()-1;
    int vert;
    bool vist;

    for(int i=0; i<size; i++) {
        vert = primsBoard.at(r).at(c);
        primsBoard.at(r).at(c) = 0;
        visited.at(vert) = true;

        if (r == 1) {
            if (c == 1) {
                vert = primsBoard.at(r).at(c + 2);
                vist = visited.at(vert);
                if (!vist)
                    pushRightWeight(r,c);

                vert = primsBoard.at(r + 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushBottomWeight(r,c);

            }
            else if (c == cols - 2) {
                vert = primsBoard.at(r).at(c - 2);
                vist = visited.at(vert);
                if (!vist)
                    pushLeftWeight(r,c);

                vert = primsBoard.at(r + 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushBottomWeight(r,c);
            }
            else {
                vert = primsBoard.at(r).at(c + 2);
                vist = visited.at(vert);
                if (!vist)
                    pushRightWeight(r,c);

                vert = primsBoard.at(r).at(c - 2);
                vist = visited.at(vert);
                if (!vist)
                    pushLeftWeight(r,c);

                vert = primsBoard.at(r + 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushBottomWeight(r,c);
            }
        }
        else if (r == rows - 2) {
            if (c == 1) {
                vert = primsBoard.at(r).at(c + 2);
                vist = visited.at(vert);
                if (!vist)
                    pushRightWeight(r,c);

                vert = primsBoard.at(r - 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushTopWeight(r,c);
            }
            else if (c == cols - 2) {
                vert = primsBoard.at(r).at(c - 2);
                vist = visited.at(vert);
                if (!vist)
                    pushLeftWeight(r,c);

                vert = primsBoard.at(r - 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushTopWeight(r,c);
            }
            else {
                vert = primsBoard.at(r).at(c + 2);
                vist = visited.at(vert);
                if (!vist)
                    pushRightWeight(r,c);

                vert = primsBoard.at(r).at(c - 2);
                vist = visited.at(vert);
                if (!vist)
                    pushLeftWeight(r,c);

                vert = primsBoard.at(r - 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushTopWeight(r,c);
            }
        }
        else {
            if (c == 1) {
                vert = primsBoard.at(r).at(c + 2);
                vist = visited.at(vert);
                if (!vist)
                    pushRightWeight(r,c);

                vert = primsBoard.at(r - 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushTopWeight(r,c);

                vert = primsBoard.at(r + 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushBottomWeight(r,c);
            }
            else if (c == cols - 2) {
                vert = primsBoard.at(r).at(c - 2);
                vist = visited.at(vert);
                if (!vist)
                    pushLeftWeight(r,c);

                vert = primsBoard.at(r - 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushTopWeight(r,c);

                vert = primsBoard.at(r + 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushBottomWeight(r,c);
            }
            else {
                vert = primsBoard.at(r).at(c + 2);
                vist = visited.at(vert);
                if (!vist)
                    pushRightWeight(r,c);

                vert = primsBoard.at(r).at(c - 2);
                vist = visited.at(vert);
                if (!vist)
                    pushLeftWeight(r,c);

                vert = primsBoard.at(r - 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushTopWeight(r,c);

                vert = primsBoard.at(r + 2).at(c);
                vist = visited.at(vert);
                if (!vist)
                    pushBottomWeight(r,c);
            }
        }

        for(int k=0; k<weights.size(); k++){
            int temp = weights.at(k).at(0);
            int tr = weights.at(k).at(3);
            int tc = weights.at(k).at(4);
            int v = primsBoard.at(tr).at(tc);
            bool check = visited.at(v);
            if(temp < smallest && !check){
                smallest = temp;
                r = weights.at(k).at(3);
                c = weights.at(k).at(4);
                WR = weights.at(k).at(1);
                WC = weights.at(k).at(2);
                s = k;
            }
        }

        primsBoard.at(WR).at(WC)=0;
        weights.at(s).at(0) = 400;
        smallest = 10000;
    }
 fixedUnusedWeightsPrims();
}

void mazeBoard::pushRightWeight(int r, int c) {
    std::vector<int> tempVec;
    int WC = c + 1;
    int right = primsBoard.at(r).at(WC);
    tempVec.push_back(right);
    tempVec.push_back(r);
    tempVec.push_back(WC);
    WC = c + 2;
    tempVec.push_back(r);
    tempVec.push_back(WC);
    weights.push_back(tempVec);
    tempVec.clear();
}

void mazeBoard::pushLeftWeight(int r, int c) {
    std::vector<int> tempVec;
    int WC = c - 1;
    int left = primsBoard.at(r).at(WC);
    tempVec.push_back(left);
    tempVec.push_back(r);
    tempVec.push_back(WC);
    WC = c - 2;
    tempVec.push_back(r);
    tempVec.push_back(WC);
    weights.push_back(tempVec);
    tempVec.clear();
}

void mazeBoard::pushBottomWeight(int r, int c) {
    std::vector<int> tempVec;
    int WR = r + 1;
    int bottom = primsBoard.at(WR).at(c);
    tempVec.push_back(bottom);
    tempVec.push_back(WR);
    tempVec.push_back(c);
    WR = r + 2;
    tempVec.push_back(WR);
    tempVec.push_back(c);
    weights.push_back(tempVec);
    tempVec.clear();
}

void mazeBoard::pushTopWeight(int r, int c) {
    std::vector<int> tempVec;
    int WR = r - 1;
    int top = primsBoard.at(WR).at(c);
    tempVec.push_back(top);
    tempVec.push_back(WR);
    tempVec.push_back(c);
    WR = r - 2;
    tempVec.push_back(WR);
    tempVec.push_back(c);
    weights.push_back(tempVec);
    tempVec.clear();
}

void mazeBoard::fixedUnusedWeightsPrims() {
    for(int i=0; i<rows; i++){
        for(int k=0; k<cols; k++){
            int temp = primsBoard.at(i).at(k);
            if(temp>1)
                primsBoard.at(i).at(k) = 1;
        }
    }
}

void mazeBoard::kruskalsMaze() {
    int smallest = 400;
    int FR, FC, SR, SC, WR, WC, v1, v2, p;
    bool add;
    for(int i=0; i<kwghts.size();i++){
        for(int k=0; k<kwghts.size(); k++) {
            int temp = kwghts.at(k).at(0);
            if (temp < smallest) {
                smallest = temp;
                FR = kwghts.at(k).at(3);
                FC = kwghts.at(k).at(4);
                SR = kwghts.at(k).at(5);
                SC = kwghts.at(k).at(6);
                WR = kwghts.at(k).at(1);
                WC = kwghts.at(k).at(2);
                p = k;
            }
        }
        v1 = kruskalsBoard.at(FR).at(FC);
        v2 = kruskalsBoard.at(SR).at(SC);
        add = buildKrusAdjMat(v1,v2);
        if(add) {
            kruskalsBoard.at(WR).at(WC) = 0;
        }
        kwghts.at(p).at(0) = 400;
        smallest = 400;
    }
    setVertZero();
    fixedUnusedWeightsKrus();
}

void mazeBoard::pushRightKrus(int r, int c) {
    std::vector<int> tempVec;
    int WC = c + 1;
    int right = primsBoard.at(r).at(WC);
    tempVec.push_back(right);
    tempVec.push_back(r);
    tempVec.push_back(WC);
    tempVec.push_back(r);
    tempVec.push_back(c);
    WC = c + 2;
    tempVec.push_back(r);
    tempVec.push_back(WC);
    kwghts.push_back(tempVec);
    tempVec.clear();
}

void mazeBoard::pushBottomKrus(int r, int c) {
    std::vector<int> tempVec;
    int WR = r + 1;
    int bottom = primsBoard.at(WR).at(c);
    tempVec.push_back(bottom);
    tempVec.push_back(WR);
    tempVec.push_back(c);
    tempVec.push_back(r);
    tempVec.push_back(c);
    WR = r + 2;
    tempVec.push_back(WR);
    tempVec.push_back(c);
    kwghts.push_back(tempVec);
    tempVec.clear();
}

void mazeBoard::fixedUnusedWeightsKrus() {
    for(int i=0; i<rows; i++){
        for(int k=0; k<cols; k++){
            int temp = kruskalsBoard.at(i).at(k);
            if(temp>1)
                kruskalsBoard.at(i).at(k) = 1;
        }
    }
}

bool mazeBoard::buildKrusAdjMat(int one, int two) {
    std::vector<int> temp;
    bool oneTrue = false;
    bool twoTrue = false;
    int row1 = 0;
    int row2 = 0;

    if(krusAdjMat.size() == 0){
        temp.push_back(one);
        temp.push_back(two);
        krusAdjMat.push_back(temp);
        return true;
    }
    else{
        int outterSize = krusAdjMat.size();
        for(int i=0; i<outterSize; i++){
            int innerSize = krusAdjMat.at(i).size();
            for(int k=0; k< innerSize; k++){
                if (one == krusAdjMat.at(i).at(k)) {
                    oneTrue = true;
                    row1 = i;
                }
                if (two == krusAdjMat.at(i).at(k)) {
                    twoTrue = true;
                    row2 = i;
                }
                if (oneTrue && twoTrue) {
                    k = innerSize;
                    i = outterSize;
                }
            }
        }
        if((oneTrue && twoTrue) && (row1 == row2)){
            return false;
        }
        else if((oneTrue && twoTrue) && row1 != row2){
            for(int j=0; j<krusAdjMat.at(row2).size(); j++){
                krusAdjMat.at(row1).push_back(krusAdjMat.at(row2).at(j));
                krusAdjMat.at(row2).at(j)=400;
            }
            return true;
        }
        else if((oneTrue || twoTrue)){
            if(oneTrue){
                krusAdjMat.at(row1).push_back(two);
                return true;
            }
            else{
                krusAdjMat.at(row2).push_back(one);
                return true;
            }
        }
        else if(!oneTrue && !twoTrue){
            temp.push_back(one);
            temp.push_back(two);
            krusAdjMat.push_back(temp);
            return true;
        }
    }
}

void mazeBoard::setVertZero() {
    for(int i=1; i<kruskalsBoard.size()-1;i+=2){
        for(int k=1; k<kruskalsBoard.at(i).size()-1; k+=2)
        {
            if(i%2 !=0 && k%2 !=0){
                kruskalsBoard.at(i).at(k) = 0;
            }
        }
    }
}

void mazeBoard::setTrack(std::vector<std::vector<int>> board) {
    std::vector<bool> temp;
    for(int i=0; i<rows; i++){
        for(int k=0; k<cols;k++){
            if(board.at(i).at(k)==1)
                temp.push_back(true);
            else
                temp.push_back(false);
        }
        track.push_back(temp);
        temp.clear();
    }
}

bool mazeBoard::solvePrims(int row, int col) {

    if (row < 0 || col <0) {
        return false;
    }
    if(row >= rows || col >= cols){
        return false;
    }
    if (row == endRow && col == endCol) {
        primsBoard.at(row).at(col)=9;
        return true;
    }
    if(primsBoard.at(row).at(col)==1){
        return false;
    }
    if(track.at(row).at(col)){
        return false;
    }

    track.at(row).at(col) = true;
    if (solvePrims(row - 1, col)) {
        primsBoard.at(row).at(col)=9;
        return true; }
    if (solvePrims(row, col + 1)){
        primsBoard.at(row).at(col)=9;
        return true; }
    if (solvePrims(row + 1, col)){
        primsBoard.at(row).at(col)=9;
        return true; }
    if (solvePrims(row, col - 1)
    ){
        primsBoard.at(row).at(col)=9;
        return true; }

    track.at(row).at(col) = false;
    return false;
}

bool mazeBoard::solveKruskals(int row, int col) {

    if (row < 0 || col <0) {
        return false;
    }
    if (row >= rows || col >= cols) {
        return false;
    }

    if (row == endRow && col == endCol) {
        kruskalsBoard.at(row).at(col)=9;
        return true;
    }
    if(kruskalsBoard.at(row).at(col)==1){
        return false;
    }
    if(track.at(row).at(col)){
        return false;
    }

    track.at(row).at(col) = true;
    if (solveKruskals(row+1,col) == true){
        kruskalsBoard.at(row).at(col)=9;
        return true; }
    if (solveKruskals(row,col+1) == true){
        kruskalsBoard.at(row).at(col)=9;
        return true; }
    if (solveKruskals(row,col-1) == true){
        kruskalsBoard.at(row).at(col)=9;
        return true; }
    if (solveKruskals(row-1, col)) {
        kruskalsBoard.at(row).at(col)=9;
        return true; }

    track.at(row).at(col) = false; //kruskalsBoard.at(row).at(col)=0;
    return false;
}

void mazeBoard::printBoard(std::vector<std::vector<int>> board) const {
    for(int i=0; i<rows; i++){
        for(int k=0; k<cols; k++) {
            //this code could be condensed. i left as is so that I could easily change the style for visibility
            if(board.at(i).at(k) == 9)
                std::cout << "  ";
            else if(board.at(i).at(k) == 0){
                std::cout << "0 ";
            }
            else
                std::cout << "1 ";

        }
        std::cout << std::endl;
    }
}



