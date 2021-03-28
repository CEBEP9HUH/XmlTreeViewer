#include "commands/TreeCommand.hpp"

TreeCommandAdd::TreeCommandAdd(std::shared_ptr<Node>& parent, std::shared_ptr<Node>& child)
:   _parent{parent}
,   _child{child}
{
    
}

void TreeCommandAdd::execute() {
    _parent->addChild(_child);
    _child->setParentNode(_parent);
    _executed = true;
}

void TreeCommandAdd::undo() { 
    _parent->removeChild(_child);
    _child->resetParentNode();
    _executed = false;
}


TreeCommandRemove::TreeCommandRemove(std::shared_ptr<Node>& node)
:   _node{node}
{

}

void TreeCommandRemove::execute() {
    auto parent = _node->getParentNode();
    if(parent) {
        parent->removeChild(_node);
    }
    _executed = true;
}

void TreeCommandRemove::undo() {
    auto parent = _node->getParentNode();
    if(parent) {
        parent->addChild(_node);
    }
    _executed = false;
}


TreeCommandEdit::TreeCommandEdit(std::shared_ptr<Node>& target_node, std::string_view new_value)
:   _target_node{target_node}
,   _value {new_value}
{
    
}

void TreeCommandEdit::execute() {
    std::string tmp(_target_node->getValue());
    _target_node->setValue(_value);
    _value = tmp;
    _executed = true;
}

void TreeCommandEdit::undo() {
    std::string tmp(_target_node->getValue());
    _target_node->setValue(_value);
    _value = tmp;
    _executed = false;
}