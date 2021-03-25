#include "ui/Tree.hpp"

#include "imgui.h"

#include "Command.hpp"

Tree::Tree(const float x, const float y, const float w, const float h, std::string_view caption)
:   UIElementBase{x, y, w, h, caption}
{

}

Tree::Tree(std::string_view caption)
:   UIElementBase{0, 0, 0, 0, caption}
{

}

void Tree::setData(std::shared_ptr<Node> data) {
    _data = data;
    _cur_draw_pos = _data;
}

void Tree::draw() {
    static int id;
    if(_cur_draw_pos) {
        auto add_button_name = "Add##" + std::to_string(id++); //FIXME buttons doesnt work sometimes
        if(ImGui::Button(add_button_name.c_str())) {
            ICommand* cmd = new DepartmentCommandAppend(_cur_draw_pos, std::make_shared<Node>());
            _command.reset(cmd);
        }
        ImGui::SameLine();
        auto edit_button_name = "Edit##" + std::to_string(id++);
        if(ImGui::Button(edit_button_name.c_str())) {
            auto new_node = std::make_shared<Node>();
            ICommand* cmd = new DepartmentCommandEdit(_cur_draw_pos, "PUPA");
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
    if(parent != nullptr) {
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