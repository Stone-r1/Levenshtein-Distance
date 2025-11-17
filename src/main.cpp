#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <memory>
#include <unistd.h>

#include "../data/dictionary.h"
#include "../models/model.h"

// super lazy XD
#include "../models/model1.cpp"
#include "../models/model2.cpp"
#include "../models/model3.cpp"

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

void assignModel(int model, std::unique_ptr<IModel>& ldist, std::string& inputString) {
    switch(model) {
        case 1:
            ldist = std::make_unique<Model1>(inputString);
            break;
        case 2:
            ldist = std::make_unique<Model2>(inputString);
            break;
        case 3:
            ldist = std::make_unique<Model3>(inputString);
            break;
        default:
            std::cerr << "Something went wrong...\n";
            break;
    }
}

int main(int argc, char* argv[]) {
    int model = defaultModel;
    std::unique_ptr<IModel> ldist;

    if (validateArgument(argc, argv, model) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    std::string inputString;
    std::cout << "What do you want to search?\n";
    std::cin >> inputString;

    assignModel(model, ldist, inputString);
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
        int currentDistance = ldist->computeDistance(word);
        
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
