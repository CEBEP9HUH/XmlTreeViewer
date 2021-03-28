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
    std::map<std::string, std::string> _attributes;
    std::string _value = "";
    std::string _value_source = "";
    std::string _tag = "unknown";
public:
    Node() = default;
    virtual ~Node() = default;

    void setValue(std::string_view value) {
        if(_value_source.empty()) {
            _value = value;
        } else {
            _attributes[_value_source] = value;
        }
    }

    void setTag(std::string_view tag) {
        _tag = tag;
    }

    std::string_view getTag() const {
        return _tag;
    }

    virtual std::string_view getValue() {
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
            if(name == _value_source) {
                _value_source = "";
            }
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

    void setParentNode(std::shared_ptr<Node>& parent) {
        _parent = parent;
    }

    void resetParentNode() {
        _parent.reset();
    }

    std::shared_ptr<Node> getParentNode() const noexcept {
        return _parent.lock();
    }

    void addChild(std::shared_ptr<Node>& child) {
        _children.emplace_back(child);
    }


    void removeChild(std::shared_ptr<Node>& child) {
        _children.remove_if([child](auto val){ return val.get() == child.get();});
    }

    std::list<std::shared_ptr<Node> > getChildList() const noexcept {
        return _children;
    }

    bool isLeaf() const noexcept {
        return _children.empty();
    }

    static std::shared_ptr<Node> makeNewChild(std::shared_ptr<Node>& parent) {
        auto child = std::make_shared<Node>();
        parent->addChild(child);
        child->setParentNode(parent);
        return child;
    }

    virtual bool hasValue() const {
        return !_value.empty();
    }
};

class ViewNode: public Node {
protected:
    uint64_t _childs_to_value = 0;
public:
    ViewNode()
    :   Node{}
    {

    }
    virtual ~ViewNode() = default;
    virtual std::string_view getValue() override {
        _value.clear();
        uint64_t counter = 0;
        for(auto& child: _children) {
            if(++counter > _childs_to_value) {
                break;
            }
            _value.append(child->getValue());
            _value.append(" ");
        }
        return _value;
    }

    static std::shared_ptr<Node> makeNewChild(std::shared_ptr<Node>& parent, const uint64_t first_n_use_as_label = 0) {
        auto tmp = std::make_shared<ViewNode>();
        tmp->_childs_to_value = first_n_use_as_label;
        std::shared_ptr<Node> child = tmp;
        parent->addChild(child);
        child->setParentNode(parent);
        return child;
    }

    bool hasValue() const override {
        return false;
    }
};