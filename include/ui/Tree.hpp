#pragma once

#include "UIElement.hpp"
#include "Command.hpp"

#include "TreeContainer.hpp"

class Tree: public UIElementBase {
protected:
    std::shared_ptr<ICommand> _command;
    std::shared_ptr<Node> _data = nullptr;
    std::shared_ptr<Node> _cur_draw_pos = nullptr;
    struct{
        char _value[10];
        char _role[10];
    } _new_node;
public:
    Tree() = delete;
    Tree(const float x, const float y, const float w, const float h, std::string_view caption);
    Tree(std::string_view caption);
    virtual ~Tree() = default;
    void setData(std::shared_ptr<Node> data);
    virtual void draw() override;
};