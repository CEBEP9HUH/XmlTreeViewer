#include "DepXMLPugiConverter.hpp"
#include "pugixml.hpp"

constexpr const size_t LOAD_FILE_DEFAULT_OPTIONS = 116;
constexpr const char XML_PERSON_NAME_FIELD[] = "name";
constexpr const char XML_PERSON_SURNAME_FIELD[] = "surname";
constexpr const char XML_PERSON_MIDNAME_FIELD[] = "middleName";
constexpr const char XML_PERSON_FUNCTION_FIELD[] = "function";
constexpr const char XML_PERSON_SALARY_FIELD[] = "salary";

constexpr const char XML_DEPS_CONTAINER[] = "departments";
constexpr const char XML_DEP_NODE[] = "department";
constexpr const char XML_DEP_NAME_ATTR[] = "name";
constexpr const char XML_EMPS_CONTAINER[] = "employments";
constexpr const char XML_EMP_NODE[] = "employment";

// bool DepXMLPugiConverter::load() {
// 	pugi::xml_document doc;
//     pugi::xml_parse_result result = doc.load_file(_path.c_str(), LOAD_FILE_DEFAULT_OPTIONS, pugi::encoding_utf8);
//     if (!result || _departments == nullptr) {
//         return false;
//     }    
//     for (pugi::xml_node dep: doc.child(XML_DEPS_CONTAINER).children(XML_DEP_NODE)) {
//         if (auto attr = dep.attribute(XML_DEP_NAME_ATTR).as_string(); attr != "") {
//             _departments->emplace_back(std::make_shared<Department>(attr));
//             for (pugi::xml_node person: dep.child(XML_EMPS_CONTAINER).children(XML_EMP_NODE)) {
//                 auto emp = std::make_shared<Employee>();
//                 emp->setSurname(person.child_value(XML_PERSON_SURNAME_FIELD));
//                 emp->setName(person.child(XML_PERSON_NAME_FIELD).child_value());
//                 emp->setMidname(person.child_value(XML_PERSON_MIDNAME_FIELD));
//                 emp->setFunction(person.child_value(XML_PERSON_FUNCTION_FIELD));
//                 emp->setSalary(std::stoi(person.child_value(XML_PERSON_SALARY_FIELD)));
//                 _departments->back()->addPerson(emp);
//             }
//         }
//     }
//     return true;
// }

bool DepXMLPugiConverter::load(Node* root) {
	pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(_path.c_str(), LOAD_FILE_DEFAULT_OPTIONS, pugi::encoding_utf8);
    if (!result || root == nullptr) {
        return false;
    }    
    for (pugi::xml_node dep: doc.child(XML_DEPS_CONTAINER).children(XML_DEP_NODE)) {
        if (auto attr = dep.attribute(XML_DEP_NAME_ATTR).as_string(); attr != "") {
            auto dep_node = root->makeNewChild();
            dep_node->addAttribute(XML_DEP_NAME_ATTR, attr);
            dep_node->useAttributeAsValue(XML_DEP_NAME_ATTR);
            for (pugi::xml_node person: dep.child(XML_EMPS_CONTAINER).children(XML_EMP_NODE)) {
                auto emp_node = dep_node->makeNewChild();
                std::string surname = person.child(XML_PERSON_SURNAME_FIELD).child_value();
                std::string name = person.child(XML_PERSON_NAME_FIELD).child_value();
                std::string midname = person.child(XML_PERSON_MIDNAME_FIELD).child_value();
                std::string fullname(surname+" "+name+" "+midname);
                emp_node->setValue(fullname);
                emp_node->makeNewChild()->setValue(surname);
                emp_node->makeNewChild()->setValue(name);
                emp_node->makeNewChild()->setValue(midname);
                emp_node->makeNewChild()->setValue(person.child_value(XML_PERSON_FUNCTION_FIELD));
                emp_node->makeNewChild()->setValue(person.child_value(XML_PERSON_SALARY_FIELD));
            }
        }
    }
    return true;
}

bool DepXMLPugiConverter::save(Node* root) {
	// pugi::xml_document doc;
    // if (_departments == nullptr) {
    //     return false;
    // }    
    // pugi::xml_node main = doc.append_child(XML_DEPS_CONTAINER);
    // for(auto dep: *_departments) {
    //     pugi::xml_node xmldep = main.append_child(XML_DEP_NODE);
    //     xmldep.append_attribute(XML_DEP_NAME_ATTR).set_value(dep->getName().data());
    //     pugi::xml_node xmlstaff = xmldep.append_child(XML_EMPS_CONTAINER);
    //     for(auto [unused, emp]: *dep) {
    //         pugi::xml_node xmlemp = xmlstaff.append_child(XML_EMP_NODE);
    //         xmlemp.append_child(XML_PERSON_SURNAME_FIELD).text().set(emp->getSurname().data());
    //         xmlemp.append_child(XML_PERSON_NAME_FIELD).text().set(emp->getName().data());
    //         xmlemp.append_child(XML_PERSON_MIDNAME_FIELD).text().set(emp->getMidname().data());
    //         xmlemp.append_child(XML_PERSON_FUNCTION_FIELD).text().set(emp->getFunction().data());
    //         xmlemp.append_child(XML_PERSON_SALARY_FIELD).text().set(std::to_string(emp->getSalary()).c_str());
    //     }
    // }
    // doc.save_file("qwe.xml", " ", 1U, pugi::encoding_utf8);
    return true;
}