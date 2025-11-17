#ifndef MODEL_H
#define MODEL_H

#include <string>

class IModel {
public:
    virtual ~IModel() = default;

    virtual int computeDistance(const std::string& dictionaryWord) = 0;
};

#endif
