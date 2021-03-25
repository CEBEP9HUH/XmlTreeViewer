#pragma once

#include <inttypes.h>
#include <any>
#include <memory>

#include "Command.hpp"
#include "TreeContainer.hpp"
#include "CommandHistory.hpp"

class Model{
protected:
    std::shared_ptr<Node> _root;
    std::shared_ptr<ICommandsHistory> _command_history;
public:
    Model();
    virtual ~Model();

    void systemCommandHandler(std::shared_ptr<ICommand> cmd);
    void departmentCmdHandler(std::shared_ptr<ICommand> cmd);
    std::shared_ptr<Node> getDepartment() const { return _root; }
};