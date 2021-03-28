#include "commands/CommandHistory.hpp"

CommandsHistory::CommandsHistory()
:   _it{_history.begin()}
{

}

std::shared_ptr<ICommand> CommandsHistory::pop() { 
    if(_history.size() == 0) {
        return nullptr;
    }
    auto res = _history.front(); 
    _history.pop_front(); 
    if(*_it == res) {
        _it = _history.begin();
    }
    return res;
}

void CommandsHistory::push(std::shared_ptr<ICommand>& cmd) { 
    if(_size > 0 && _history.size() == _size) 
        _history.pop_front(); 
    if(_it != _history.end()) {
        _history.erase(std::next(_it), _history.end());
    }
    _history.push_back(cmd); 
    _it = std::prev(_history.end());
}

bool CommandsHistory::undo() {
    if(!_history.empty() && (*_it)->isExecuted()) {
        (*_it)->undo();
        if(_it != _history.begin()) {
            --_it;
        }
        return true;
    }
    return false;
}

bool CommandsHistory::redo() {
    if(std::next(_it) != _history.end()) {
        ++_it;
        if(!_history.empty() && !(*_it)->isExecuted()) {
            (*_it)->execute();
            return true;
        }
    }
    return false;
}