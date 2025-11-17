#ifndef NAIVE_MATRIX_H
#define NAIVE_MATRIX_H

#include <vector>

#include "IGridStorage.h"

class NaiveMatrix: public IGridStorage {
private:
    std::vector<std::vector<int>> matrix;

public:
    void init(int rows, int cols) override;
    int& at(int row, int col) override;
};

#endif
