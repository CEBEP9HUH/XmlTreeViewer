#include "ui/Toolbar.hpp"

#include "imgui.h"

Toolbar::Toolbar(const float x, const float y, const float w, const float h, std::string_view caption)
:   UIElementBase{x, y, w, h, caption}
,   _is_active{false}
{

}

Toolbar::Toolbar()
:   UIElementBase{0, 0, 0, 0, ""}
{

}

void Toolbar::append(UIElementBase* element) {
    _elements.emplace_back(element);
}

void Toolbar::draw() {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
                            | ImGuiWindowFlags_NoResize
                            | ImGuiWindowFlags_NoTitleBar
                            | ImGuiWindowFlags_NoScrollbar
                            | ImGuiWindowFlags_AlwaysUseWindowPadding;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
    ImGui::Begin(_caption.c_str(), &_is_active, flags);
    ImGui::SetWindowSize({_shapeRect.width, _shapeRect.height});
    ImGui::SetWindowPos({_shapeRect.posX, _shapeRect.posY});
    for(auto& el: _elements) {
        ImGui::SameLine();
        el->draw();
    }
    ImGui::End();
    ImGui::PopStyleVar();
}