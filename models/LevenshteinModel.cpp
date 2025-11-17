#include <string>

#include "LevenshteinModel.h"

LevenshteinModel::LevenshteinModel(const std::string& userInput, IGridStorage& grid, int allowedDistance):
    userInput(userInput), grid(grid) , allowedDistance(allowedDistance) {}

int LevenshteinModel::computeDistance(const std::string& dictionaryWord) {
    int n = userInput.size();
    int m = dictionaryWord.size();

    if (std::abs(n - m) > allowedDistance) {
        return allowedDistance + 1;
    }

    grid.init(m + 1, n + 1);

    for (int i = 0; i <= n; i++) {
        grid.at(0, i) = (i <= allowedDistance ? i : allowedDistance + 1);
    }

    for (int i = 1; i <= m; i++) {
        grid.at(i, 0) = (i <= allowedDistance ? i : allowedDistance + 1);
        bool inRange = false;
        
        int end = std::min(n, i + allowedDistance);

        for (int j = std::max(1, i - allowedDistance); j <= end; j++) {
            int cost = (userInput[j - 1] == dictionaryWord[i - 1] ? 0 : 1);
            int row = grid.at(i - 1, j) + 1;
            int col = grid.at(i, j - 1) + 1;
            int diag = grid.at(i - 1, j - 1) + cost;
            grid.at(i, j) = std::min(row, std::min(col, diag));

            if (grid.at(i, j) <= allowedDistance) {
                inRange = true;
            }
        }

        if (!inRange) {
            return allowedDistance + 1;
        }
    }

    int result = grid.at(m, n);
    return result <= allowedDistance ? result : allowedDistance + 1;
}
