#ifndef LEVENSHTEIN_MODEL_H
#define LEVENSHTEIN_MODEL_H

#include <string>

#include "IModel.h"
#include "storage/IGridStorage.h"

class LevenshteinModel : public IModel {
private: 
    std::string userInput;
    IGridStorage& grid;

public:
    LevenshteinModel(const std::string& userInput, IGridStorage& grid);
    int computeDistance(const std::string& dictionaryWord) override;
};

#endif
