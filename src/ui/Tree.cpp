#include "ui/Tree.hpp"

#include "imgui.h"

Tree::Tree(const float x, const float y, const float w, const float h, std::string_view caption, ICommand* command)
:   UIElementBase{x, y, w, h, caption}
,   _command{command}
{

}

Tree::Tree(std::string_view caption, ICommand* command)
:   UIElementBase{0, 0, 0, 0, caption}
,   _command{command} 
{

}

void Tree::setData(std::shared_ptr<std::list<std::shared_ptr<IDepartment> > > department) {
    _department = department;
}

void Tree::draw() {
    for(auto& dep: *_department) {
        if (ImGui::TreeNode(dep->getName().data()))
        {
            for(auto& [unused, emp]: *dep) {
                
                if (ImGui::TreeNode(emp->getFullName().data())) {
                    ImGui::Text(emp->getFunction().data());
                    ImGui::Text(std::to_string(emp->getSalary()).c_str());
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
    }
}