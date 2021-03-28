#pragma once 

#include "XMLParser.hpp"
#include "pugixml.hpp"

class DepXMLPugiConverter: public IXMLParser {
protected:
    enum class NodeType{
        ROOT_NODE,
        BASIC_NODE,
        CONTAINER_NODE,
        VIEW_NODE
    };
    constexpr static const size_t _department_xml_structure_depth = 4;
    using structure_t = std::array<std::pair<std::string, NodeType>, _department_xml_structure_depth>;
    static const structure_t _department_xml_structure;
    void _parse(std::shared_ptr<Node>& root, pugi::xml_node& node, size_t depth);
    void _convert(std::shared_ptr<Node>& tnode, pugi::xml_node pnode, size_t depth);
public:
    DepXMLPugiConverter() = default;
    virtual ~DepXMLPugiConverter() = default;
    virtual bool load(std::shared_ptr<Node>& root, std::string_view file_name) override;
    virtual bool save(std::shared_ptr<Node>& root, std::string_view file_name) override;
};