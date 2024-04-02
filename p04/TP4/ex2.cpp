#include <iostream>     // std::cout
#include <algorithm>    // std::count
#include "exercises.h"

// Auxiliary recursive function
void hanoiAux(unsigned int n, char src, char aux, char dest, std::string &moves) {
    if (n == 1) {
        moves += std::string(1, src) + "->" + std::string(1, dest) + ",";
        return;
    }
    hanoiAux(n - 1, src, dest, aux, moves);
    moves += std::string(1, src) + "->" + std::string(1, dest) + ",";
    hanoiAux(n - 1, aux, src, dest, moves);
}

std::string hanoiDC(unsigned int n, char src, char dest) {
    std::string moves = "";
    char aux = 'C';
    hanoiAux(n, src, aux, dest, moves);
    moves.pop_back();
    return moves;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, testHanoi_height4) {
    std::string moves = hanoiDC(4, 'A', 'B');
    EXPECT_EQ(std::count(moves.begin(),moves.end(),','),14); // there are 15 moves
    EXPECT_EQ(moves,"A->C,A->B,C->B,A->C,B->A,B->C,A->C,A->B,C->B,C->A,B->A,C->B,A->C,A->B,C->B");
}