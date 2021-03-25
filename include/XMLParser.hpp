#pragma once

#include <string>
#include <memory>

#include "TreeContainer.hpp"

class IXMLParser {
public:
    virtual ~IXMLParser() = default;
    virtual void setFilePath(std::string_view path) = 0;
    virtual std::string_view getFilePath() = 0;
    virtual bool load(std::shared_ptr<Node> root) = 0;
    virtual bool save(std::shared_ptr<Node> root) = 0;
};

