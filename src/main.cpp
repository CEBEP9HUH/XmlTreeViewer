#include "DepXMLPugiConverter.hpp"
#include "Department.hpp"

#include <iostream>

int main() {
    auto buf = std::make_shared<DepXMLPugiConverter::_departments_container_t>();;
    DepXMLPugiConverter a(buf);
    a.setFilePath("../data/tsl.xml");
    a.parse();
    
    for(auto dep: *buf) {
        std::cout << dep->getName() << "\n";
        for(auto [id, emp]: *dep) {
            std::cout << "\t" << emp->getSurname() << " " << emp->getName() << " " << emp->getMidname() << "\n";
        }
    }
    return 0;
}