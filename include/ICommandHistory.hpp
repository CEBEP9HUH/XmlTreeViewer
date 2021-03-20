#pragma once

#include "Command.hpp"

#include <memory>
#include <list>
#include <iterator>

class ICommandsHistory {
public:
    virtual ~ICommandsHistory();
    virtual ICommand* pop() = 0;
    virtual void push(const ICommand*) = 0;
    virtual void setSize(const size_t) = 0;
    virtual size_t getSize() = 0;
    virtual bool undo() = 0;
    virtual bool redo() = 0;
};

class CommandsHystory {
    std::list<ICommand*> _history;
    size_t _size = 0;
    std::list<ICommand*>::iterator _it;
public:
    CommandsHystory(): _it{_history.begin()} {}
    virtual ~CommandsHystory();
    virtual ICommand* pop() { 
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
    virtual void push(ICommand* cmd) { 
        if(_history.size() == _size) 
            _history.pop_front(); 
        _history.push_back(cmd); 
        ++_it;
    }
    virtual void setSize(const size_t size) { _size = size; }
    virtual size_t getSize() { return _size; }
    virtual bool undo() {
        if(*_it) {
            (*_it)->undo();
            if(_it != _history.begin()) {
                --_it;
            }
        }
    }
    virtual bool redo() {
        if(*_it) {
            (*_it)->execute();
            if(std::next(_it) != _history.end()) {
                ++_it;
            }
        }
    }
};