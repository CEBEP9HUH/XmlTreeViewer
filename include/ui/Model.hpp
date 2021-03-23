#pragma once

#include <inttypes.h>
#include <any>
#include <iostream>

#include "Command.hpp"

class Model{
public:
    static void systemCommandHandler(ICommand* cmd) { 
        auto local_cmd = reinterpret_cast<SystemCommandBase*>(cmd);
        switch(local_cmd->getCommandType()) {
            case SystemCommandBase::command_t::Undo:
                std::cout << "Undo\n"; 
                break;
            case SystemCommandBase::command_t::Redo:
                std::cout << "Redo\n"; 
                break;
            default:
                std::cout << "Bad system command has received\n"; 
                break;
        }
    }

    static void departmentCmdHandler(std::shared_ptr<ICommand> cmd) { 
        cmd->execute();
    }
};