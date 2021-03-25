#include "ui/Button.hpp"

#include "imgui.h"

Button::Button(const float x, const float y, const float w, const float h, std::string_view caption, std::shared_ptr<ICommand> command)
:   UIElementBase{x, y, w, h, caption}
,   _command{command}
{
    _strong_placement = true;
}

Button::Button(std::string_view caption, std::shared_ptr<ICommand> command)
:   UIElementBase{0, 0, 0, 0, caption}
,   _command{command}
{
    _strong_placement = false;
}

void Button::draw() {
    if(_strong_placement) {
        ImGui::SetCursorPos({_shapeRect.posX, _shapeRect.posY});
    }
    if(ImGui::Button(_caption.c_str(), {_shapeRect.width, _shapeRect.height})) {
        notify(_command);
    }
}