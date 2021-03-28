/*
Classes for system commands.
*/
#pragma once
#include "Command.hpp"
#include "CommandHistory.hpp"

class SystemCommandBase: public ICommand {
public:
    virtual ~SystemCommandBase() = default;
    SystemCommandBase() = default;
    virtual bool isExecuted() override { return true; }
};

class CommandRedo: public SystemCommandBase {
protected:
    std::shared_ptr<ICommandsHistory> _history;

public:
    CommandRedo(std::shared_ptr<ICommandsHistory> command_history);
    virtual ~CommandRedo() = default;
    virtual void execute() override;
    virtual void undo() override;
};

class CommandUndo: public SystemCommandBase {
protected:
    std::shared_ptr<ICommandsHistory> _history;

public:
    CommandUndo(std::shared_ptr<ICommandsHistory> command_history);
    virtual ~CommandUndo() = default;
    virtual void execute() override;
    virtual void undo() override;
};