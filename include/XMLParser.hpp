#pragma once

#include <string>
#include <memory>

#include "TreeContainer.hpp"

class IXMLParser {
public:
    virtual ~IXMLParser() = default;
    virtual bool load(std::shared_ptr<Node>& root, std::string_view file_name) = 0;
    virtual bool save(std::shared_ptr<Node>& root, std::string_view file_name) = 0;
};

