#include "Model.hpp"
#include "DepXMLPugiConverter.hpp"
#include <iostream>


Model::Model()
:   _root{new Node()}
,   _command_history(new CommandsHistory)
{
    DepXMLPugiConverter converter;
    converter.setFilePath("../data/tsl.xml");
    _root->setValue("Root");
    converter.load(_root);
}



void Model::systemCommandHandler(std::shared_ptr<ICommand> cmd) { 
    auto local_cmd = reinterpret_cast<SystemCommandBase*>(cmd.get());
    switch(local_cmd->getCommandType()) {
        case SystemCommandBase::command_t::Undo:
            _command_history->undo();
            break;
        case SystemCommandBase::command_t::Redo:
            _command_history->redo();
            break;
        default:
            std::cerr << "Bad system command has received\n"; 
            break;
    }
}

void Model::departmentCmdHandler(std::shared_ptr<ICommand> cmd) { 
    cmd->execute();
    _command_history->push(cmd);
}


Model::~Model() {
    DepXMLPugiConverter converter;
    converter.save(_root);
}