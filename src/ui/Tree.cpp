#include "ui/Tree.hpp"

#include "imgui.h"
#include "commands/TreeCommand.hpp"
#include "commands/SystemCommand.hpp"

#include <cstring>

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

void Tree::_draw_add_button(const int id) {
    auto add_button_name = "Add##" + std::to_string(id);
    if(ImGui::Button(add_button_name.c_str())) {
        auto new_node = std::make_shared<Node>();
        new_node->setValue(_new_node._value);
        new_node->setTag(_new_node._role);
        ICommand* cmd = new TreeCommandAdd(_cur_draw_pos, new_node);
        _command.reset(cmd);
    }
}

void Tree::_draw_delete_button(const int id) {
    auto parent = _cur_draw_pos->getParentNode();
    if(parent) {
        auto delete_button_name = "Delete##" + std::to_string(id);
        if(ImGui::Button(delete_button_name.c_str())) {
            if(parent) {
                ICommand* cmd = new TreeCommandRemove(_cur_draw_pos);
                _command.reset(cmd);
            }
        }
    }
}

void Tree::_draw_edit_button(const int id) {
    auto edit_button_name = "Edit##" + std::to_string(id);
    if(ImGui::Button(edit_button_name.c_str())) {
        ICommand* cmd = new TreeCommandEdit(_cur_draw_pos, _new_node._value);
        _command.reset(cmd);
    }
}

void Tree::_draw_node_button(const int id) {
    if(_cur_draw_pos->isLeaf()) {
        ImGui::Text(_cur_draw_pos->getValue().data());
    } else {
        std::string node_label(_cur_draw_pos->getValue());
        node_label += "##" + std::to_string(id);
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

void Tree::draw() {
    static int id;
    if(_cur_draw_pos) {
        _draw_add_button(id++);
        ImGui::SameLine();
        _draw_edit_button(id++);
        ImGui::SameLine();
        _draw_delete_button(id++);
        ImGui::SameLine();
        _draw_node_button(id++);
    }
    auto parent = _cur_draw_pos->getParentNode();
    if(parent != nullptr) {
        _cur_draw_pos = parent;
    } else {
        _cur_draw_pos = _data;
        id = 0;
        ImGui::InputText("New value",_new_node._value, INPUT_FIELDS_SIZE);
        ImGui::InputText("New role",_new_node._role, INPUT_FIELDS_SIZE);
    }
    if(_command.get() && parent.get()) {
        notify(_command);
        _command.reset();
    }
}