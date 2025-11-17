#include "flattenedMatrix.h"

void FlattenedMatrix::init(int rows, int cols) {
    this->columns = cols;
    int size = rows * cols;

    if (flattenedMatrix.capacity() < size) {
        flattenedMatrix.reserve(size);
    }

    flattenedMatrix.resize(size);
}

int& FlattenedMatrix::at(int row, int col) {
    return flattenedMatrix[columns*row + col];
}
