#pragma once

#include "TreeContainer.hpp"

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual bool isExecuted() = 0;
};

class DepartmentCommandBase: public ICommand {
protected:
    bool _executed = false;
public:
    DepartmentCommandBase() = default;
    virtual ~DepartmentCommandBase() = default;
    virtual bool isExecuted() override {
        return _executed;
    }
};

class DepartmentCommandAppend: public DepartmentCommandBase {
protected:
    std::shared_ptr<Node> _parent;
    std::shared_ptr<Node> _child;
public:
    DepartmentCommandAppend(std::shared_ptr<Node> parent, std::shared_ptr<Node> child)
    :   _parent{parent}
    ,   _child{child}
    {
        
    }
    virtual ~DepartmentCommandAppend() = default;
    virtual void execute() override {
        _parent->addChild(_child);
        _child->setParentNode(_parent);
        _executed = true;
    }
    virtual void undo() override { 
        _parent->removeChild(_child);
        _child->setParentNode(nullptr);
        _executed = false;
    }
};

class DepartmentCommandRemove: public DepartmentCommandBase {
protected:
    std::shared_ptr<Node> _node;
public:
    DepartmentCommandRemove(std::shared_ptr<Node> node)
    :   _node{node}
    {

    }
    virtual ~DepartmentCommandRemove() {
    }
    virtual void execute() override {
        auto parent = _node->getParentNode();
        if(parent) {
            parent->removeChild(_node);
        }
        _executed = true;
    }
    virtual void undo() override {
        auto parent = _node->getParentNode();
        if(parent) {
            parent->addChild(_node);
        }
        _executed = false;
    }
};

class DepartmentCommandEdit: public DepartmentCommandBase {
protected:
    std::shared_ptr<Node> _target_node;
    std::string _value;
public:
    DepartmentCommandEdit(std::shared_ptr<Node> target_node, std::string_view new_value)
    :   _target_node{target_node}
    ,   _value {new_value}
    {
        
    }
    virtual ~DepartmentCommandEdit() = default;
    virtual void execute() override {
        std::string tmp(_target_node->getValue());
        _target_node->setValue(_value);
        _value = tmp;
        _executed = true;
    }
    virtual void undo() override {
        std::string tmp(_target_node->getValue());
        _target_node->setValue(_value);
        _value = tmp;
        _executed = false;
    }
};


class SystemCommandBase: public ICommand {
public:
    enum class command_t {
        Redo,
        Undo
    };
protected:
    const command_t _command;
public:
    virtual ~SystemCommandBase() = default;
    SystemCommandBase(const command_t command): _command{command} {}
    command_t getCommandType() const { return _command; }
    virtual void execute() override { }
    virtual void undo() override { }
    virtual bool isExecuted() override { return true; }
};

class CommandRedo: public SystemCommandBase {
public:
    virtual ~CommandRedo() = default;
    CommandRedo(): SystemCommandBase{command_t::Redo} {}
};

class CommandUndo: public SystemCommandBase {
public:
    virtual ~CommandUndo() = default;
    CommandUndo(): SystemCommandBase{command_t::Undo} {}
};