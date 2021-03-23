#pragma once

#include "TreeContainer.hpp"

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual bool execute() = 0;
    virtual bool undo() = 0;
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
    virtual bool execute() override {
        _parent->addChild(_child);
        _executed = true;
        return true; //FIXME should do we return anything?
    }
    virtual bool undo() override { 
        _parent->removeChild(_child.get());
        _executed = false;
        return true; //FIXME should do we return anything?
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
    virtual bool execute() override {
        auto parent = _node->getParentNode();
        if(parent) {
            parent->removeChild(_node.get());
        }
        _executed = true;
        return true; //FIXME should do we return anything?
    }
    virtual bool undo() override {
        auto parent = _node->getParentNode();
        if(parent) {
            parent->addChild(_node);
        }
        _executed = false;
        return true; //FIXME should do we return anything?
    }
};

class DepartmentCommandEdit: public DepartmentCommandBase {
protected:
    std::shared_ptr<Node> _new_node;
    std::shared_ptr<Node> _target_node;
public:
    DepartmentCommandEdit(std::shared_ptr<Node> target_node, std::shared_ptr<Node> new_node)
    :   _target_node{target_node}
    ,   _new_node{new_node}
    {
        
    }
    virtual ~DepartmentCommandEdit() = default;
    virtual bool execute() override {
        auto parent = _target_node->getParentNode();
        if(parent) {
            parent->addChild(_new_node);
            parent->removeChild(_target_node.get());
        }
        _executed = true;
        return true; //FIXME should do we return anything?
    }
    virtual bool undo() override {
        auto parent = _target_node->getParentNode();
        if(parent) {
            parent->addChild(_target_node);
            parent->removeChild(_new_node.get());
        }
        _executed = false;
        return false;
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
    virtual bool isExecuted() override { return true; }
    virtual bool execute() override { return true; }
    virtual bool undo() override { return true; }
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