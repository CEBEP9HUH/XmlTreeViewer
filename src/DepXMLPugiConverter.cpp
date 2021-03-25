#include "DepXMLPugiConverter.hpp"
#include "pugixml.hpp"

constexpr const size_t LOAD_FILE_DEFAULT_OPTIONS = 116;
constexpr const char XML_PERSON_SURNAME_FIELD[] = "surname";
constexpr const char XML_PERSON_NAME_FIELD[] = "name";
constexpr const char XML_PERSON_MIDNAME_FIELD[] = "middleName";
constexpr const char XML_PERSON_FUNCTION_FIELD[] = "function";
constexpr const char XML_PERSON_SALARY_FIELD[] = "salary";

constexpr const char XML_DEPS_CONTAINER[] = "departments";
constexpr const char XML_DEP_NODE[] = "department";
constexpr const char XML_DEP_NAME_ATTR[] = "name";
constexpr const char XML_EMPS_CONTAINER[] = "employments";
constexpr const char XML_EMP_NODE[] = "employment";

void initNode(std::shared_ptr<Node>& parameter, std::string_view tag, pugi::xml_node& source) {
    parameter->setValue(source.child_value(tag.data()));
    parameter->setTag(tag);
}

bool DepXMLPugiConverter::load(std::shared_ptr<Node> root) {
	pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(_path.c_str(), LOAD_FILE_DEFAULT_OPTIONS, pugi::encoding_utf8);
    if (!result || root == nullptr) {
        return false;
    }    
    for (pugi::xml_node dep: doc.child(XML_DEPS_CONTAINER).children(XML_DEP_NODE)) {
        if (auto attr = dep.attribute(XML_DEP_NAME_ATTR).as_string(); attr != "") {
            auto dep_node = Node::makeNewChild(root);
            dep_node->addAttribute(XML_DEP_NAME_ATTR, attr);
            dep_node->setTag(XML_DEP_NODE);
            dep_node->useAttributeAsValue(XML_DEP_NAME_ATTR);
            for (pugi::xml_node person: dep.child(XML_EMPS_CONTAINER).children(XML_EMP_NODE)) {
                auto emp_node = ViewNode::makeNewChild(dep_node, 3);
                emp_node->setTag(XML_EMP_NODE);
                initNode(Node::makeNewChild(emp_node), XML_PERSON_SURNAME_FIELD, person);
                initNode(Node::makeNewChild(emp_node), XML_PERSON_NAME_FIELD, person);
                initNode(Node::makeNewChild(emp_node), XML_PERSON_MIDNAME_FIELD, person);
                initNode(Node::makeNewChild(emp_node), XML_PERSON_FUNCTION_FIELD, person);
                initNode(Node::makeNewChild(emp_node), XML_PERSON_SALARY_FIELD, person);
            }
        }
    }
    return true;
}

bool DepXMLPugiConverter::save(std::shared_ptr<Node> root) {
	pugi::xml_document doc;
    if (root == nullptr) {
        return false;
    }    
    pugi::xml_node main = doc.append_child(XML_DEPS_CONTAINER);
    
    auto deps = root->getChildList();

    for(auto& dep: deps) {
        pugi::xml_node xmldep = main.append_child(dep->getTag().data());
        auto attrs = dep->getAttributesList();
        for(auto& [name, value]: attrs) {
            xmldep.append_attribute(name.c_str()).set_value(value.c_str());
        }
        auto staff = dep->getChildList();
        pugi::xml_node xmlstaff = xmldep.append_child(XML_EMPS_CONTAINER);
        for(auto& emp: staff) {
            pugi::xml_node xmlemp = xmlstaff.append_child(emp->getTag().data());
            auto emp_data = emp->getChildList();
            for(auto& data: emp_data) {
                xmlemp.append_child(data->getTag().data()).text().set(data->getValue().data());
            }
        }
    }
    doc.save_file("qwe.xml", " ", 1U, pugi::encoding_utf8);
    return true;
}