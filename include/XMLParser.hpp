#pragma once

#include <string>

#include "TreeContainer.hpp"

class IXMLParser {
public:
    virtual ~IXMLParser() = default;
    virtual void setFilePath(std::string_view path) = 0;
    virtual std::string_view getFilePath() = 0;
    virtual bool load(Node* root) = 0;
    virtual bool save(Node* root) = 0;
};

