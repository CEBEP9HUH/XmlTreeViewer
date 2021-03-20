#pragma once

#include <string>

class IEmployee {
public:
    virtual ~IEmployee() = default;
    virtual void setName(std::string_view name) = 0;
    virtual void setSurname(std::string_view sername) = 0;
    virtual void setMidname(std::string_view midname) = 0;
    virtual void setFunction(std::string_view function) = 0;
    virtual void setSalary(const size_t salary) = 0;

    virtual std::string_view getName() = 0;
    virtual std::string_view getSurname() = 0;
    virtual std::string_view getMidname() = 0;
    virtual std::string_view getFunction() = 0;
    virtual size_t getSalary() = 0;
};

class Employee: public IEmployee {
    std::string _name;
    std::string _surname;
    std::string _midname;
    std::string _function;
    size_t _salary; 
public:
    virtual ~Employee() = default;
    virtual void setName(std::string_view name) override { _name = name; }
    virtual void setSurname(std::string_view surname) override { _surname = surname; }
    virtual void setMidname(std::string_view midname) override { _midname = midname; }
    virtual void setFunction(std::string_view function) override { _function = function; }
    virtual void setSalary(const size_t salary) override { _salary = salary; }

    virtual std::string_view getName() override { return _name; }
    virtual std::string_view getSurname() override { return _surname; }
    virtual std::string_view getMidname() override { return _midname; }
    virtual std::string_view getFunction() override { return _function; }
    virtual size_t getSalary() override { return _salary; }
};