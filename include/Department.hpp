#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "Employee.hpp"

class IDepartment {
protected:
    std::unordered_map<size_t, std::shared_ptr<IEmployee> > _staff;
public:
    virtual ~IDepartment() = default;
    virtual void setName(std::string_view name) = 0;
    virtual std::string_view getName() = 0;
    virtual size_t addPerson(const std::shared_ptr<IEmployee>& person) = 0;
    virtual void removePerson(size_t id) = 0;
    virtual std::shared_ptr<IEmployee> getPerson(const size_t id) = 0;
    virtual size_t getDepartmentSize() = 0;
    class iterator{
        private:
            using _init_t = decltype(_staff.begin());
            using _iter_t = std::pair<size_t, std::shared_ptr<IEmployee> >;
            _init_t _iter;
        public:
            iterator(_init_t i) : _iter{i} {};
            ~iterator() = default;
            iterator operator++(){ iterator iter = *this; _iter++; return iter;}
            iterator operator++(int i) {_iter++; return *this;}
            _iter_t operator*() const {return std::make_pair(_iter->first, _iter->second);}
            _init_t operator->() const {return _iter;}
            bool operator==(const iterator& other) const {return _iter == other._iter;}
            bool operator!=(const iterator& other) const {return !(*this == other);}
        };
    auto begin(){
        return iterator(_staff.begin());
    }
    auto end(){
        return iterator(_staff.end());
    }
};

class Department: public IDepartment {
protected:
    std::string _name;
    size_t _id_counter = 0;
public:
    Department(std::string_view name): _name{name} {}
    virtual ~Department() = default;
    virtual void setName(std::string_view name) override { _name = name; }
    virtual std::string_view getName() override { return _name; }
    virtual size_t addPerson(const std::shared_ptr<IEmployee>&) override;
    virtual void removePerson(size_t id) override;
    virtual std::shared_ptr<IEmployee> getPerson(const size_t id) override;
    virtual size_t getDepartmentSize() override { return _staff.size(); }
};