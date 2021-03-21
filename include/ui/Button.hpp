#pragma once
#include "UIElement.hpp"
#include "Command.hpp"

class Button: public UIElementBase {
protected:
    std::shared_ptr<ICommand> _command;
public:
    Button() = delete;
    Button(const float x, const float y, const float w, const float h, std::string_view caption, ICommand* command);
    Button(std::string_view caption, ICommand* command);
    virtual ~Button() = default;

    virtual void draw() override;
};