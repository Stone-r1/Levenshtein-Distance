#include <vector>
#include <string>
#include <algorithm>

class Model2 {
private:
    std::string userInput;
    std::vector<int> grid;
    
public:
    Model2(const std::string& userInput) {
        this->userInput = userInput;
    }
    
    void fillBaseCaseMatrix(int n, int m) {
        int rows = n + 1;
        int cols = m + 1;
        int size = rows * cols;
       
        // bad
        // 1) destroys old elements
        // 2) checks if it needs new allocation
        // 3) constructs new elements of required size
        // 4) copy/write into memory
        // 5) free old memory buffer
        // grid.assign(n * m, 0);

        if (grid.capacity() < size) {
            grid.reserve(size);
        }

        grid.resize(size);
       
        // grid[0][i] = i
        for (int i = 0; i < cols; i++) {
            grid[i] = i;
        }
       
        // grid[i][0] = i
        for (int i = 0; i < rows; i++) {
            grid[i*cols] = i;
        }
    }
    
    // O(n*m)
    int computeDistance(const std::string& dictionaryWord) {
        int n = this->userInput.size();
        int m = dictionaryWord.size(); 
        int rows = n + 1;
        int cols = m + 1;

        fillBaseCaseMatrix(n, m);
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int minRow = grid[(i-1)*cols + j] + 1;
                int minCol = grid[i*cols + (j-1)] + 1;
                int minDiag = grid[(i-1)*cols + (j-1)] + (this->userInput[i-1] == dictionaryWord[j-1] ? 0 : 1);
                grid[i*cols+j] = std::min({minRow, minCol, minDiag}); 
            }
        }
        
        return grid[n*cols + m];
    }
};
