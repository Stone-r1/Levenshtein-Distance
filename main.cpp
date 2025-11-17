#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <memory>
#include <unistd.h>

#include "data/dictionary.h"
#include "models/LevenshteinModel.h"
#include "models/storage/naiveMatrix.h"
#include "models/storage/flattenedMatrix.h"
#include "models/storage/rollingMatrix.h"

constexpr int modelCount = 3;
constexpr int defaultModel = 3;

int validateModel(const char* str) {
    std::string s(str);
    if (!std::all_of(s.begin(), s.end(), ::isdigit)) {
        throw std::invalid_argument("Model must be an integer");
    }

    int v = std::stoi(s);
    if (!v || v > modelCount) {
        throw std::out_of_range("Model out of range");
    }

    return v;
}

int validateArgument(int argc, char* argv[], int& model) {
    int option;

    while ((option = getopt(argc, argv, "m:")) != -1) {
        switch(option) {
            case 'm': {
                try {
                    model = validateModel(optarg);
                } catch (...) {
                    std::cerr << "Invalid -m argument!\n";
                    return EXIT_FAILURE;
                }

                break;
            }

            default: {
                std::cerr << "Incorrect argument!\n";
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}

std::unique_ptr<IGridStorage> selectStorage(int model, int inputSize, int wordSize) {
    switch (model) {
        case 1: {
            auto storage = std::make_unique<NaiveMatrix>();
            storage->init(inputSize + 1, wordSize + 1);
            return storage;
        }

        case 2: {
            auto storage = std::make_unique<FlattenedMatrix>();
            storage->init(inputSize + 1, wordSize + 1);
            return storage;
        }

        case 3: {
            auto storage = std::make_unique<RollingMatrix>();
            storage->init(inputSize + 1, wordSize + 1);
            return storage;
        }

        default:
            throw std::invalid_argument("Invalid storage model");
    }
}

int main(int argc, char* argv[]) {
    int model = defaultModel;

    if (validateArgument(argc, argv, model) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    std::string inputString;
    std::cout << "What do you want to search?\n";
    std::cin >> inputString;

    std::unique_ptr<IGridStorage> grid = selectStorage(model, inputString.size(), 10);
    LevenshteinModel ldist(inputString, *grid);

    auto startTime = std::chrono::high_resolution_clock::now();
    
    // O(nlogn)
    auto it = std::lower_bound(dictionary.begin(), dictionary.end(), inputString);
    if (it != dictionary.end() && *it == inputString) {
        std::cout << "The word " << inputString << " was found in the dictionary.\n";
        return 0;
    } 
    
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
