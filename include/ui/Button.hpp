/*
Button UI element. On click - sends (via observer-publisher pattern) a command which was given in constructor
*/

#pragma once
#include "UIElement.hpp"
#include "commands/Command.hpp"

#include <memory>

class Button: public UIElementBase {
protected:
    std::shared_ptr<ICommand> _command;

public:
    Button() = delete;
    Button(const float x, const float y, const float w, const float h, std::string_view caption, std::shared_ptr<ICommand> command);
    Button(std::string_view caption, std::shared_ptr<ICommand> command);
    virtual ~Button() = default;
    virtual void draw() override;
};