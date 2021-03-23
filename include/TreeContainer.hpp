#pragma once

#include <map>
#include <list>
#include <string>
#include <memory>

#include <algorithm>

class Node: public std::enable_shared_from_this<Node> {
protected:
    std::weak_ptr<Node> _parent;
    std::list<std::shared_ptr<Node> > _children;
    std::map<std::string, std::string> _attributes; //+
    std::string _value = ""; //+
    std::string _value_source = ""; //+
public:
    Node() = default;
    virtual ~Node() = default;

    void setValue(std::string_view value) {
      _value = value;
    }

    std::string_view getValue() const noexcept {
        if(_value_source.empty()) {
            return _value;
        }
        return _attributes.at(_value_source);
    }

    void addAttribute(std::string_view name, std::string_view value) {
        _attributes.emplace(name, value);
    }

    std::string getAttribute(std::string_view name) const {
        if(auto it = _attributes.find(std::string(name)); it != _attributes.end()) {
            return it->second;
        }
        return "";
    }

    void removeAttribute(std::string_view name) {
        if(auto it = _attributes.find(std::string(name)); it != _attributes.end()) {
            _attributes.erase(it);
        }
    }

    std::map<std::string, std::string> getAttributesList() const noexcept {
        return _attributes;
    }

    bool useAttributeAsValue(std::string_view name) {
        if(auto it = _attributes.find(std::string(name)); it == _attributes.end()) {
            return false;
        }
        _value_source = name;
        return true;
    }

    void dontUseAttributeAsValue() {
        _value_source = "";
    }

    void setParentNode(std::shared_ptr<Node> parent) {
        _parent = parent;
    }

    std::shared_ptr<Node> getParentNode() const noexcept {
        return _parent.lock();
    }

    void addChild(std::shared_ptr<Node> child) {
        _children.emplace_back(child);
    }


    void removeChild(Node* child) {
        _children.remove_if([child](auto val){ return val.get() == child;});
    }

    std::list<std::shared_ptr<Node> > getChildList() const noexcept {
        return _children;
    }

    bool isLeaf() const noexcept {
        return _children.empty();
    }

    static std::shared_ptr<Node> makeNewChild(std::shared_ptr<Node> parent) {
        auto child = std::make_shared<Node>();
        parent->addChild(child);
        child->setParentNode(parent);
        return child;
    }

};