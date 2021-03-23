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
    DepartmentCommandAppend(Node* parent, Node* child)
    :   _parent{parent}
    ,   _child{child}
    {
        
    }
    virtual ~DepartmentCommandAppend() = default;
    virtual bool execute() override {
        _parent->addChild(_child.get());
        return true; //FIXME should do we return anything?
    }
    virtual bool undo() override { 
        _parent->removeChild(_child.get());
        return true; //FIXME should do we return anything?
    }
};

class DepartmentCommandRemove: public DepartmentCommandBase {
protected:
    std::shared_ptr<Node> _parent;
    std::shared_ptr<Node> _child;
public:
    DepartmentCommandRemove(Node* parent, Node* child)
    :   _parent{parent}
    ,   _child{child}
    {
        
    }
    virtual ~DepartmentCommandRemove() = default;
    virtual bool execute() override {
        _parent->removeChild(_child.get());
        return true; //FIXME should do we return anything?
    }
    virtual bool undo() override {
        _parent->addChild(_child.get());
        return true; //FIXME should do we return anything?
    }
};

class DepartmentCommandEdit: public DepartmentCommandBase {
protected:
    std::shared_ptr<Node> _new_node;
    std::shared_ptr<Node> _target_node;
public:
    DepartmentCommandEdit(Node* target_node, Node* new_node)
    :   _target_node{target_node}
    ,   _new_node{new_node}
    {
        
    }
    virtual ~DepartmentCommandEdit() = default;
    virtual bool execute() override {
        _target_node.swap(_new_node);
        return true; //FIXME should do we return anything?
    }
    virtual bool undo() override {
        _target_node.swap(_new_node);
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