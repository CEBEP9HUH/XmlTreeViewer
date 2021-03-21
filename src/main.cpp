#include "DepXMLPugiConverter.hpp"
#include "Department.hpp"

#include "CommandHistory.hpp"
#include "Command.hpp"

#include <iostream>

int main() {
    auto buf = std::make_shared<DepXMLPugiConverter::_departments_container_t>();;
    DepXMLPugiConverter a(buf);
    a.setFilePath("../data/tsl.xml");
    a.load();
    
    for(auto dep: *buf) {
        std::cout << dep->getName() << "\n";
        for(auto [id, emp]: *dep) {
            std::cout << "\t" << emp->getSurname() << " " << emp->getName() << " " << emp->getMidname() << "\n";
        }
        break;
    }
    ICommandsHistory* ch = new CommandsHistory();
    ch->setSize(10);
    auto cmd = new DepartmentCommandRemove<Employee>(buf->front(), 0U);
    auto cmd2 = new DepartmentCommandAppend<Employee>(buf->front(), buf->front()->getPerson(3).get());
    
    auto p = new Employee();
    p->setName("Николай");
    p->setSurname("Шуляков");
    p->setMidname("Васильевич");
    p->setFunction("Я");
    p->setSalary(50);


    auto cmd3 = new DepartmentCommandEdit<Employee>(buf->front(), p, 4U);

    cmd->execute();
    cmd2->execute();
    cmd3->execute();
    a.save();

    for(auto dep: *buf) {
        std::cout << dep->getName() << "\n";
        for(auto [id, emp]: *dep) {
            std::cout << "\t" << emp->getSurname() << " " << emp->getName() << " " << emp->getMidname() << "\n";
        }
        break;
    }

    ch->push(cmd);
    ch->push(cmd2);
    ch->push(cmd3);
    ch->undo();
    ch->undo();
    ch->undo();

    for(auto dep: *buf) {
        std::cout << dep->getName() << "\n";
        for(auto [id, emp]: *dep) {
            std::cout << "\t" << emp->getSurname() << " " << emp->getName() << " " << emp->getMidname() << "\n";
        }
        break;
    }
    return 0;
}