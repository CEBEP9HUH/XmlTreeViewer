/*
CommandsHistory allows to store commands and navigate through them
*/
#pragma once

#include "Command.hpp"

#include <memory>
#include <list>

class ICommandsHistory {
public:
    virtual ~ICommandsHistory() = default;
    virtual std::shared_ptr<ICommand> pop() = 0;
    virtual void push(std::shared_ptr<ICommand>&) = 0;
    virtual void setSize(const size_t) = 0;
    virtual size_t getSize() = 0;
    virtual bool undo() = 0;
    virtual bool redo() = 0;
};

class CommandsHistory: public ICommandsHistory {
protected:
    std::list<std::shared_ptr<ICommand> > _history;
    std::list<std::shared_ptr<ICommand> >::iterator _it;
    size_t _size = 0;

public:
    CommandsHistory();
    virtual ~CommandsHistory() = default;
    virtual std::shared_ptr<ICommand> pop() override;
    virtual void push(std::shared_ptr<ICommand>& cmd) override;
    virtual bool undo() override;
    virtual bool redo() override;
    virtual void setSize(const size_t size) override { _size = size; }
    virtual size_t getSize() override { return _size; }
};