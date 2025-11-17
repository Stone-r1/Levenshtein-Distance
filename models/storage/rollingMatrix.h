#ifndef ROLLING_MATRIX_H
#define ROLLING_MATRIX_H

#include <vector>

#include "IGridStorage.h"

class RollingMatrix : public IGridStorage {
private:
    std::vector<int> rollingMatrix;
    int columns;

public:
    void init(int rows, int cols) override;
    int& at(int row, int col) override;
};

#endif
