/*
Tree UI element. Used for xml-tree showing
*/
#pragma once
#include "UIElement.hpp"
#include "commands/Command.hpp"
#include "TreeContainer.hpp"

class Tree: public UIElementBase {
protected:
    constexpr static const int INPUT_FIELDS_SIZE = 50;
    std::shared_ptr<ICommand> _command;
    std::shared_ptr<Node> _data = nullptr;
    std::shared_ptr<Node> _cur_draw_pos = nullptr;
    struct{
        char _value[INPUT_FIELDS_SIZE];
        char _role[INPUT_FIELDS_SIZE];
    } _new_node;
    void _draw_add_button(const int id);
    void _draw_delete_button(const int id);
    void _draw_edit_button(const int id);
    void _draw_node_button(const int id);
    
public:
    Tree() = delete;
    Tree(const float x, const float y, const float w, const float h, std::string_view caption);
    Tree(std::string_view caption);
    virtual ~Tree() = default;
    void setData(std::shared_ptr<Node> data);
    virtual void draw() override;
};