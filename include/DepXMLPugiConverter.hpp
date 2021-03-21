#pragma once 

#include "Department.hpp"
#include "XMLParser.hpp"

class DepXMLPugiConverter: public IXMLParser {
public:
    using _departments_container_t = std::list<std::shared_ptr<IDepartment> >;
protected:
    std::string _path;
    std::shared_ptr<_departments_container_t > _departments;
public:
    DepXMLPugiConverter(std::shared_ptr<_departments_container_t> departments);
    virtual ~DepXMLPugiConverter() = default;
    virtual void setFilePath(std::string_view path) override { _path = path; };
    virtual std::string_view getFilePath() override { return _path; };
    virtual bool load() override;
    virtual bool save() override;
};