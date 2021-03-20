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
constexpr const char XML_EMPS_CONTAINER[] = "employments";
constexpr const char XML_EMP_NODE[] = "employment";

DepXMLPugiConverter::DepXMLPugiConverter(std::shared_ptr<_departments_container_t> departments): _departments(departments) {

}

bool DepXMLPugiConverter::parse() {
	pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(_path.c_str(), LOAD_FILE_DEFAULT_OPTIONS, pugi::encoding_utf8);
    if (!result || _departments == nullptr) {
        return false;
    }    
    for (pugi::xml_node dep: doc.child(XML_DEPS_CONTAINER).children(XML_DEP_NODE)) {
        if (auto attr = dep.attribute("name").as_string(); attr != "") {
            _departments->emplace_back(std::make_shared<Department>(attr));
            for (pugi::xml_node person: dep.child(XML_EMPS_CONTAINER).children(XML_EMP_NODE)) {
                auto emp = std::make_shared<Employee>();
                emp->setName(person.child(XML_PERSON_NAME_FIELD).child_value());
                emp->setSurname(person.child_value(XML_PERSON_SURNAME_FIELD));
                emp->setMidname(person.child_value(XML_PERSON_MIDNAME_FIELD));
                emp->setFunction(person.child_value(XML_PERSON_FUNCTION_FIELD));
                emp->setSalary(std::stoi(person.child_value(XML_PERSON_SALARY_FIELD)));
                _departments->back()->addPerson(emp);
            }
        }
    }
    return true;
}