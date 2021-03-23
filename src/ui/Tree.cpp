#include "ui/Tree.hpp"

#include "imgui.h"

#include "Command.hpp"

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

void Tree::setData(Node* data) {
    _data.reset(data);
    _cur_draw_pos = _data;
}

void Tree::draw() {
    static int id;
    if(_cur_draw_pos) {
        if(_cur_draw_pos->isLeaf()) {
            ImGui::Button("Edit");
            ImGui::SameLine();
            ImGui::Text(_cur_draw_pos->getValue().data());
        } else {
            if(ImGui::Button("Add")) {
                ICommand* cmd = new DepartmentCommandAppend(_cur_draw_pos, std::make_shared<Node>());
                _command.reset(cmd);
            }
            ImGui::SameLine();
            if(ImGui::Button("Edit")) {
                auto new_node = std::make_shared<Node>();
                new_node->setValue("EDITED_NODE");
                ICommand* cmd = new DepartmentCommandEdit(_cur_draw_pos, new_node);
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
            if (ImGui::TreeNode(_cur_draw_pos->getValue().data())) {
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
    if(parent) {
        _cur_draw_pos = parent;
    } else {
        _cur_draw_pos = _data;
        id = 0;
    }
    if(_command.get() && parent.get()) {
        notify(_command);
        _command.reset();
    }
}