#include "Department.hpp"

#include <algorithm>

size_t Department::addPerson(const std::shared_ptr<IEmployee>& person) { 
    _staff.emplace(_id_counter, person);
    return _id_counter++;
}

bool Department::addPerson(const std::shared_ptr<IEmployee>& person, const size_t id) { 
    if(_staff.count(id) > 0) {
        return false;
    }
    _staff.emplace(id, person);
    return true;
}

void Department::removePerson(const size_t id) { 
    _staff.erase(id);
}

std::shared_ptr<IEmployee> Department::getPerson(const size_t id) { 
    if(_staff.count(id) != 0) {
        return _staff[id];
    } 
    return nullptr;
}
