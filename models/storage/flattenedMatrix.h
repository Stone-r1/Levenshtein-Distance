#ifndef FLATTENED_MATRIX_H
#define FLATTENED_MATRIX_H

#include <vector>

#include "IGridStorage.h"

class FlattenedMatrix : public IGridStorage {
private:
    std::vector<int> flattenedMatrix;
    int columns;

public:
    void init(int rows, int cols) override;
    int& at(int row, int col) override;
};

#endif
