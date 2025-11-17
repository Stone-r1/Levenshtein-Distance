#include "naiveMatrix.h"

void NaiveMatrix::init(int rows, int cols) {
    matrix.assign(rows, std::vector<int>(cols, 0));
}

int& NaiveMatrix::at(int row, int col) {
    return matrix[row][col];
}
