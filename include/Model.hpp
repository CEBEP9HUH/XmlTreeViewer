/*
Model part of MVC pattern.
*/
#pragma once

#include <inttypes.h>
#include <memory>
#include <mutex>
#include <atomic>

#include "commands/Command.hpp"
#include "commands/CommandHistory.hpp"
#include "TreeContainer.hpp"

class Model{
protected:
    std::shared_ptr<Node> _root;
    std::shared_ptr<ICommandsHistory> _command_history;
    std::list<std::pair<std::shared_ptr<ICommand>, bool> > _command_buffer;
    std::mutex _command_buffer_mutex;
    std::atomic<bool> _close = false;

public:
    Model();
    virtual ~Model();
    void run();
    void exit();
    void addCommand(std::shared_ptr<ICommand> cmd, bool store_in_history = false);
    std::shared_ptr<Node> getDepartment() const { return _root; }
    std::shared_ptr<ICommandsHistory> getCommandHistory() const { return _command_history; }
};