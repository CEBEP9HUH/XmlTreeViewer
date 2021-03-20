#pragma once

#include <string>

class IXMLParser {
public:
    virtual ~IXMLParser() = default;
    virtual void setFilePath(std::string_view path) = 0;
    virtual std::string_view getFilePath() = 0;
    virtual bool parse() = 0;
};

