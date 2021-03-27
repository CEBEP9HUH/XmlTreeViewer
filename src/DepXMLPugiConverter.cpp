#include "DepXMLPugiConverter.hpp"
#include <array>

constexpr const size_t LOAD_FILE_DEFAULT_OPTIONS = 116;
const DepXMLPugiConverter::structure_t
DepXMLPugiConverter::_department_xml_structure = {{{"departments", Node::NodeType::ROOT_NODE},
                                                {"department", Node::NodeType::BASIC_NODE}, 
                                                {"employments", Node::NodeType::CONTAINER_NODE}, 
                                                {"employment", Node::NodeType::VIEW_NODE}}};

void DepXMLPugiConverter::_parse(std::shared_ptr<Node>& tnode, pugi::xml_node& pnode, size_t depth) {
    for (pugi::xml_node& n: pnode.children()) {
        if(std::strlen(n.name())==0) {
            continue;
        }
        std::shared_ptr<Node> cur;
        if(depth < _department_xml_structure_depth) {
            switch(_department_xml_structure[depth].second) {
                case Node::NodeType::CONTAINER_NODE: {
                    _parse(tnode, n, depth + 1);
                    continue;
                } break;
                case Node::NodeType::VIEW_NODE : {
                    cur = ViewNode::makeNewChild(tnode, 3);
                } break;
                default: {
                    cur = Node::makeNewChild(tnode);
                } break;
            }
        } else {
            cur = Node::makeNewChild(tnode);
        }
        cur->setTag(n.name());
        for(auto& attr: n.attributes()) { 
            cur->addAttribute(attr.name(), attr.value());
        }
        if(std::strlen(n.child_value()) > 0) {
            cur->setValue(n.child_value());
        } else {
            cur->useAttributeAsValue(n.first_attribute().name());
        }
        _parse(cur, n, depth + 1);
    }
}

bool DepXMLPugiConverter::load(std::shared_ptr<Node>& root) {
	pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(_path.c_str(), LOAD_FILE_DEFAULT_OPTIONS, pugi::encoding_utf8);
    if (!result || root == nullptr) {
        return false;
    }    
    root->setTag(_department_xml_structure[0].first);
    _parse(root, doc.first_child(), 1);
    return true;
}

void DepXMLPugiConverter::_convert(std::shared_ptr<Node>& tnode, pugi::xml_node pnode, size_t depth) {
    if(depth < _department_xml_structure_depth) {
        if(_department_xml_structure[depth].second == Node::NodeType::CONTAINER_NODE) {
            pnode = pnode.append_child(_department_xml_structure[depth].first.c_str());
        }
    }
    auto tnode_childs = tnode->getChildList();
    for(auto& tnode_child: tnode_childs) {
        auto pnode_child = pnode.append_child(tnode_child->getTag().data());
        if(tnode_child->hasValue()) {
            pnode_child.text().set(tnode_child->getValue().data());
        }
        auto attrs = tnode_child->getAttributesList();
        for(auto& [name, value]: attrs) {
            pnode_child.append_attribute(name.c_str()).set_value(value.c_str());
        }
        _convert(tnode_child, pnode_child, depth + 1);
    }
}

bool DepXMLPugiConverter::save(std::shared_ptr<Node>& root) {
    if (root == nullptr) {
        return false;
    }   
	pugi::xml_document doc; 
    _convert(root, doc.append_child(root->getTag().data()), 1);
    doc.save_file("qwe.xml", " ", 1U, pugi::encoding_utf8);
    return true;
}