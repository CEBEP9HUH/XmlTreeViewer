/*
Classes for tree operations command.
*/
#pragma once
#include "Command.hpp"
#include "TreeContainer.hpp"

class TreeCommandBase: public ICommand {
protected:
    bool _executed = false;

public:
    TreeCommandBase() = default;
    virtual ~TreeCommandBase() = default;
    virtual bool isExecuted() override {
        return _executed;
    }
};

class TreeCommandAdd: public TreeCommandBase {
protected:
    std::shared_ptr<Node> _parent;
    std::shared_ptr<Node> _child;

public:
    TreeCommandAdd(std::shared_ptr<Node>& parent, std::shared_ptr<Node>& child);
    virtual ~TreeCommandAdd() = default;
    virtual void execute() override;
    virtual void undo() override;
};

class TreeCommandRemove: public TreeCommandBase {
protected:
    std::shared_ptr<Node> _node;

public:
    TreeCommandRemove(std::shared_ptr<Node>& node);
    virtual ~TreeCommandRemove() = default;
    virtual void execute() override;
    virtual void undo() override;
};

class TreeCommandEdit: public TreeCommandBase {
protected:
    std::shared_ptr<Node> _target_node;
    std::string _value;

public:
    TreeCommandEdit(std::shared_ptr<Node>& target_node, std::string_view new_value);
    virtual ~TreeCommandEdit() = default;
    virtual void execute() override;
    virtual void undo() override;
};