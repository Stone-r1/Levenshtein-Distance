#include <vector>
#include <string>
#include <algorithm>

#include "model.h"

class Model1 : public IModel {
private:
    std::string userInput;
    std::vector<std::vector<int>> matrix;
    
public:
    Model1(const std::string& userInput) {
        this->userInput = userInput;
    }
    
    void fillBaseCaseMatrix(int sizeA, int sizeB) {
        int n = sizeA + 1, m = sizeB + 1;
        
        matrix.assign(n, std::vector<int>(m, 0));
        
        for (int i = 0; i < n; i++) {
            matrix[i][0] = i;
        }
        
        for (int i = 0; i < m; i++) {
            matrix[0][i] = i;
        }
    }
    
    // O(n*m)
    int computeDistance(const std::string& dictionaryWord) override {
        fillBaseCaseMatrix(this->userInput.size(), dictionaryWord.size());
        
        for (int i = 1; i <= this->userInput.size(); i++) {
            for (int j = 1; j <= dictionaryWord.size(); j++) {
                int minRow = matrix[i-1][j] + 1;
                int minCol = matrix[i][j-1] + 1;
                int minDiag = matrix[i-1][j-1] + (this->userInput[i-1] == dictionaryWord[j-1] ? 0 : 1);
                matrix[i][j] = std::min({minRow, minCol, minDiag});
                
            }
        }
        
        return matrix[this->userInput.size()][dictionaryWord.size()];
    }
};
