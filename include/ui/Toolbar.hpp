#pragma once

#include "UIElement.hpp"
#include <memory>
#include <list>

class Toolbar: public UIElementBase {
public:
    Toolbar();
    Toolbar(const float x, const float y, const float w, const float h, std::string_view caption);
    virtual ~Toolbar() = default;

    virtual void draw() override;
    void append(UIElementBase* element);

protected:
    std::list<std::unique_ptr<UIElementBase>> _elements;
    bool _is_active;
    constexpr static int _element_size = 100; 
};