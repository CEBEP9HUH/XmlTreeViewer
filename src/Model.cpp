#include "Model.hpp"
#include "DepXMLPugiConverter.hpp"
#include <iostream>


Model::Model()
:   _root{new Node()}
,   _command_history(new CommandsHistory)
{
    DepXMLPugiConverter converter;
    _root->setValue("Root");
    converter.load(_root, "../data/tsl.xml");
}



void Model::addCommand(std::shared_ptr<ICommand> cmd, bool store_in_history) { 
    std::lock_guard locker(_command_buffer_mutex);
    _command_buffer.push_back(std::make_pair(cmd, store_in_history));
}

void Model::run() { 
    while(!_close.load(std::memory_order_relaxed)) {
        std::lock_guard locker(_command_buffer_mutex);
        if(!_command_buffer.empty()) {
            auto cur_cmd = _command_buffer.front();
            _command_buffer.pop_front();
            cur_cmd.first->execute();
            if(cur_cmd.second) {
                _command_history->push(cur_cmd.first);
            }
        }
    }
}

void Model::exit() {
    _close.store(true, std::memory_order_relaxed);
}


Model::~Model() {
    DepXMLPugiConverter converter;
    converter.save(_root, "../data/output.xml");
}