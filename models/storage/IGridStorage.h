#ifndef GRID_STORAGE_H
#define GRID_STORAGE_H

class IGridStorage {
public:
    virtual ~IGridStorage() = default;
    virtual void init(int rows, int cols) = 0;
    virtual int& at(int row, int col) = 0;
};

#endif
