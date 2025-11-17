#include <string>

#include "LevenshteinModel.h"

LevenshteinModel::LevenshteinModel(const std::string& userInput, IGridStorage& grid):
    userInput(userInput), grid(grid) {}

int LevenshteinModel::computeDistance(const std::string& dictionaryWord) {
    int n = this->userInput.size();
    int m = dictionaryWord.size();

    grid.init(m + 1, n + 1);

    for (int i = 0; i <= n; i++) {
        grid.at(0, i) = i;
    }

    for (int i = 1; i <= m; i++) {
        grid.at(i, 0) = i;
        for (int j = 1; j <= n; j++) {
            int cost = (this->userInput[j - 1] == dictionaryWord[i - 1] ? 0 : 1);
            int row = grid.at(i - 1, j) + 1;
            int col = grid.at(i, j - 1) + 1;
            int diag = grid.at(i - 1, j - 1) + cost;
            grid.at(i, j) = std::min(row, std::min(col, diag));
        }
    }

    return grid.at(m, n);
}
