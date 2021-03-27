#pragma once 

#include "XMLParser.hpp"
#include "pugixml.hpp"

class DepXMLPugiConverter: public IXMLParser {
protected:
    constexpr static const size_t _department_xml_structure_depth = 4;
    using structure_t = std::array<std::pair<std::string, Node::NodeType>, _department_xml_structure_depth>;
    static const structure_t _department_xml_structure;
    std::string _path;
    void _parse(std::shared_ptr<Node>& root, pugi::xml_node& node, size_t depth);
    void _convert(std::shared_ptr<Node>& tnode, pugi::xml_node pnode, size_t depth);
public:
    DepXMLPugiConverter() = default;
    virtual ~DepXMLPugiConverter() = default;
    virtual void setFilePath(std::string_view path) override { _path = path; };
    virtual std::string_view getFilePath() override { return _path; };
    virtual bool load(std::shared_ptr<Node>& root) override;
    virtual bool save(std::shared_ptr<Node>& root) override;
};