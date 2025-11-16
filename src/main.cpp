#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>

#include "../data/dictionary.h"

// super lazy XD
#include "../models/model1.cpp"
#include "../models/model2.cpp"
#include "../models/model3.cpp"


int main() {
    std::string inputString;
    std::cout << "What do you want to search?\n";
    std::cin >> inputString;

    auto startTime = std::chrono::high_resolution_clock::now();
    
    // O(nlogn)
    auto it = std::lower_bound(dictionary.begin(), dictionary.end(), inputString);
    if (it != dictionary.end() && *it == inputString) {
        std::cout << "The word " << inputString << " was found in the dictionary.\n";
        return 0;
    }
    
    Model3 ldist(inputString);
    
    int minDistance = std::numeric_limits<int>::max();
    std::string closestWord;
    
    for (const std::string& word : dictionary) {
        int currentDistance = ldist.computeDistance(word);
        
        if (minDistance > currentDistance) {
            minDistance = currentDistance;
            closestWord = word;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = endTime - startTime;
    
    std::cout << "The minimum distance is between " << inputString << " and " << closestWord << " and it equals to: " << minDistance << '\n';

    std::cout << "Time taken to compute distances: " << duration.count() << " ms\n";
}
