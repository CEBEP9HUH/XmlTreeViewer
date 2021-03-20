#pragma once

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class XMLCommandBase: public ICommand {
public:
    virtual ~XMLCommandBase() = default;

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
};

class CommandRedo: public SystemCommandBase {
public:
    virtual ~CommandRedo() = default;
    CommandRedo(): SystemCommandBase{command_t::Redo} {}
    virtual void execute() override {}
    virtual void undo() override {}
};

class CommandUndo: public SystemCommandBase {
public:
    virtual ~CommandUndo() = default;
    CommandUndo(): SystemCommandBase{command_t::Undo} {}
    virtual void execute() override {}
    virtual void undo() override {}
};