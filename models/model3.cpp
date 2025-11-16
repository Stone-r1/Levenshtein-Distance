#include <vector>
#include <string>
#include <algorithm>

class Model3 {
private:
    std::string userInput;
    std::vector<int> grid;
    
public:
    Model3(const std::string& userInput) {
        this->userInput = userInput;
        grid.resize(2 * (userInput.size() + 1));
    }
    
    void fillBaseCaseMatrix(int n) {
        for (int i = 0; i <= n; i++) {
            grid[i] = i;
        }
    }
    
    int computeDistance(const std::string& dictionaryWord) {
        int n = this->userInput.size();
        int m = dictionaryWord.size(); 
        int cols = n + 1;
        int rows = m + 1;
        int size = 2 * cols;

        fillBaseCaseMatrix(n);
       
        int curRow = 0;
        for (int i = 1; i < rows; i++) {          
            curRow = (i * cols) % size; // 0th index of the row if in matrix
            int prevRow = (curRow + cols) % size;
            grid[curRow] = i; // assign value to it like we normally do

            for (int j = 1; j < cols; j++) {
                int minRow = grid[prevRow + j] + 1; // never past 2 * cols
                int minCol = grid[curRow + (j-1)] + 1;
                int minDiag = grid[prevRow + (j-1)] + (this->userInput[j-1] == dictionaryWord[i-1] ? 0 : 1);
                grid[curRow+j] = std::min(minRow, std::min(minCol, minDiag)); 
            }
        }
        
        return grid[curRow + n];
    }
};
