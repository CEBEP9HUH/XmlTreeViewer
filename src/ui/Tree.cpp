#include "ui/Tree.hpp"

#include "imgui.h"

#include "Command.hpp"

Tree::Tree(const float x, const float y, const float w, const float h, std::string_view caption)
:   UIElementBase{x, y, w, h, caption}
{
    std::memset(&_new_node, 0, sizeof(_new_node));
}

Tree::Tree(std::string_view caption)
:   UIElementBase{0, 0, 0, 0, caption}
{
    std::memset(&_new_node, 0, sizeof(_new_node));
}

void Tree::setData(std::shared_ptr<Node> data) {
    _data = data;
    _cur_draw_pos = _data;
}

void Tree::draw() {
    static int id;
    if(_cur_draw_pos) {
        auto add_button_name = "Add##" + std::to_string(id++);
        if(ImGui::Button(add_button_name.c_str())) {
            auto new_node = std::make_shared<Node>();
            new_node->setValue(_new_node._value);
            new_node->setTag(_new_node._role);
            ICommand* cmd = new DepartmentCommandAppend(_cur_draw_pos, new_node);
            _command.reset(cmd);
        }
        ImGui::SameLine();
        auto edit_button_name = "Edit##" + std::to_string(id++);
        if(ImGui::Button(edit_button_name.c_str())) {
            ICommand* cmd = new DepartmentCommandEdit(_cur_draw_pos, _new_node._value);
            _command.reset(cmd);
        }
        ImGui::SameLine();
        auto delete_button_name = "Delete##" + std::to_string(id++);
        if(ImGui::Button(delete_button_name.c_str())) {
            auto parent = _cur_draw_pos->getParentNode();
            if(parent) {
                ICommand* cmd = new DepartmentCommandRemove(_cur_draw_pos);
                _command.reset(cmd);
            }
        }
        ImGui::SameLine();
        if(_cur_draw_pos->isLeaf()) {
            ImGui::Text(_cur_draw_pos->getValue().data());
        } else {
            std::string node_label(_cur_draw_pos->getValue());
            node_label += "##" + std::to_string(id++);
            if (ImGui::TreeNode(node_label.c_str())) {
                auto children = _cur_draw_pos->getChildList();
                for(auto child: children) {
                    _cur_draw_pos = child;
                    draw();
                }
                ImGui::TreePop();
            }
        }
    }
    auto parent = _cur_draw_pos->getParentNode();
    if(parent != nullptr) {
        _cur_draw_pos = parent;
    } else {
        _cur_draw_pos = _data;
        id = 0;
        ImGui::InputText("new_value_input",_new_node._value, 10);
        ImGui::InputText("new_role_input",_new_node._role, 10);
    }
    if(_command.get() && parent.get()) {
        notify(_command);
        _command.reset();
    }
}