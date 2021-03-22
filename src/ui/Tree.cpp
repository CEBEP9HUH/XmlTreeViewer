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

void Tree::setData(Node* data) {
    _data = data;
    _cur_draw_pos = _data;
}

#include <iostream>

void Tree::draw() {
    if(_cur_draw_pos) {
        if(_cur_draw_pos->isLeaf()) {
            ImGui::Button("Edit");
            ImGui::SameLine();
            ImGui::Button("Delete");
            ImGui::SameLine();
            ImGui::Text(_cur_draw_pos->getValue().data());
        } else {
            ImGui::Button("Add");
            ImGui::SameLine();
            ImGui::Button("Delete");
            ImGui::SameLine();
            if (ImGui::TreeNode(_cur_draw_pos->getValue().data())) {
                auto children = _cur_draw_pos->getChildList();
                for(auto child: children) {
                    _cur_draw_pos = child.get();
                    draw();
                }
                ImGui::TreePop();
            }
        }
    }
    auto parent = _cur_draw_pos->getParentNode();
    _cur_draw_pos = parent ? parent : _data;
}