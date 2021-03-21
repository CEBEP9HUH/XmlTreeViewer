#pragma once

#include "Employee.hpp"
#include "Department.hpp"

#include <iostream>

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual bool execute() = 0;
    virtual bool undo() = 0;
    virtual bool isExecuted() = 0;
};

class DepartmentCommandBase: public ICommand {
protected:
    std::weak_ptr<IDepartment> _department;
    bool _executed = false;
public:
    DepartmentCommandBase(std::shared_ptr<IDepartment> department): _department{department} {}
    virtual ~DepartmentCommandBase() = default;
    virtual bool isExecuted() override {
        return _executed;
    }
};

template<class employee_t>
class DepartmentCommandAppend: public DepartmentCommandBase {
    static_assert(std::is_base_of_v<IEmployee, employee_t>);
protected:
    std::shared_ptr<IEmployee> _node;
    size_t _node_id = 0;
public:
    DepartmentCommandAppend(std::shared_ptr<IDepartment> department, IEmployee* person)
    :   DepartmentCommandBase{department}
    ,   _node{new employee_t(*reinterpret_cast<employee_t*>(person))} 
    {
        
    }
    virtual ~DepartmentCommandAppend() = default;
    virtual bool execute() override {
        if(auto dep = _department.lock()) {
            if(_node_id == 0) {
                _node_id = dep->addPerson(_node);
                _executed = true;
            } else {
                _executed = dep->addPerson(_node, _node_id);
            }
            return _executed;
        }
        return false;
    }
    virtual bool undo() override { 
        auto dep = _department.lock();
        if(_executed && dep != nullptr) {
            dep->removePerson(_node_id);
            _executed = false;
            return true;
        }
        return false;
    }
};

template<class employee_t>
class DepartmentCommandRemove: public DepartmentCommandBase {
    static_assert(std::is_base_of_v<IEmployee, employee_t>);
protected:
    std::shared_ptr<IEmployee> _node = nullptr;
    size_t _node_id = 0;
public:
    DepartmentCommandRemove(std::shared_ptr<IDepartment> department, size_t node_id)
    :   DepartmentCommandBase{department}
    ,   _node_id{node_id} 
    {
        
    }
    virtual ~DepartmentCommandRemove() = default;
    virtual bool execute() override {
        if(auto dep = _department.lock()) {
            _node = dep->getPerson(_node_id);
            dep->removePerson(_node_id);
            _executed = true;
            return true;
        }
        return false;
    }
    virtual bool undo() override {
        auto dep = _department.lock();
        if(_executed && dep != nullptr) {
            _executed = !dep->addPerson(_node, _node_id);
            return !_executed;
        }
        return false;
    }
};

template<class employee_t>
class DepartmentCommandEdit: public DepartmentCommandBase {
    static_assert(std::is_base_of_v<IEmployee, employee_t>);
protected:
    std::shared_ptr<IEmployee> _node_prev = nullptr;
    std::shared_ptr<IEmployee> _node_new = nullptr;
    size_t _node_id = 0;
public:
    DepartmentCommandEdit(std::shared_ptr<IDepartment> department, IEmployee* person, size_t node_id)
    :   DepartmentCommandBase{department}
    ,   _node_new{new employee_t(*reinterpret_cast<employee_t*>(person))} 
    ,   _node_id{node_id} 
    {
        _node_prev.reset(new employee_t(*reinterpret_cast<employee_t*>(department->getPerson(_node_id).get())));
    }
    virtual ~DepartmentCommandEdit() = default;
    virtual bool execute() override {
        if(auto dep = _department.lock()) {
            dep->removePerson(_node_id);
            _executed = dep->addPerson(_node_new, _node_id);;
            return _executed;
        }
        return false;
    }
    virtual bool undo() override {
        auto dep = _department.lock();
        if(_executed && dep != nullptr) {
            dep->removePerson(_node_id);
            _executed = !dep->addPerson(_node_prev, _node_id);
            return !_executed;
        }
        return false;
    }
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
    virtual bool isExecuted() override {}
    virtual bool execute() override {}
    virtual bool undo() override {}
};

class CommandRedo: public SystemCommandBase {
public:
    virtual ~CommandRedo() = default;
    CommandRedo(): SystemCommandBase{command_t::Redo} {}
};

class CommandUndo: public SystemCommandBase {
public:
    virtual ~CommandUndo() = default;
    CommandUndo(): SystemCommandBase{command_t::Undo} {}
};