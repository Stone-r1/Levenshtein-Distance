#include "rollingMatrix.h"

void RollingMatrix::init(int rows, int cols) {
    this->columns = cols;
    int size = cols * 2;
    
    if (rollingMatrix.capacity() < size) {
        rollingMatrix.reserve(size);
    }

    rollingMatrix.resize(size);
}

int& RollingMatrix::at(int row, int col) {
    return rollingMatrix[(row % 2) * columns + col];
}
