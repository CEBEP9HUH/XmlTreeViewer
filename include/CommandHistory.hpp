#pragma once

#include "Command.hpp"

#include <memory>
#include <list>
#include <iterator>

class ICommandsHistory {
public:
    virtual ~ICommandsHistory() = default;
    virtual ICommand* pop() = 0;
    virtual void push(ICommand*) = 0;
    virtual void setSize(const size_t) = 0;
    virtual size_t getSize() = 0;
    virtual bool undo() = 0;
    virtual bool redo() = 0;
};

class CommandsHistory: public ICommandsHistory {
    std::list<ICommand*> _history;
    size_t _size = 0;
    std::list<ICommand*>::iterator _it;
public:
    CommandsHistory(): _it{_history.begin()} {}
    virtual ~CommandsHistory() = default;
    virtual ICommand* pop() override { 
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
    virtual void push(ICommand* cmd) override { 
        if(_size > 0 && _history.size() == _size) 
            _history.pop_front(); 
        _history.push_back(cmd); 
        _it = std::prev(_history.end());
    }
    virtual void setSize(const size_t size) override { _size = size; }
    virtual size_t getSize() override { return _size; }
    virtual bool undo() override {
        if(*_it && (*_it)->isExecuted()) {
            (*_it)->undo();
            if(_it != _history.begin()) {
                --_it;
            }
            return true;
        }
        return false;
    }
    virtual bool redo() override {
        if(*_it && !(*_it)->isExecuted()) {
            (*_it)->execute();
            if(std::next(_it) != _history.end()) {
                ++_it;
            }
            return true;
        }
        return false;
    }
};