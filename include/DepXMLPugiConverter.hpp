#pragma once 

#include "Department.hpp"
#include "XMLParser.hpp"

class DepXMLPugiConverter: public IXMLParser {
protected:
    std::string _path;
public:
    DepXMLPugiConverter() = default;
    virtual ~DepXMLPugiConverter() = default;
    virtual void setFilePath(std::string_view path) override { _path = path; };
    virtual std::string_view getFilePath() override { return _path; };
    virtual bool load(Node* root) override;
    virtual bool save(Node* root) override;
};