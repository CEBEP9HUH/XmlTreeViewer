#pragma once

#include "UIElement.hpp"
#include "Command.hpp"

#include "Department.hpp"

class Tree: public UIElementBase {
protected:
    std::shared_ptr<ICommand> _command;
    std::shared_ptr<std::list<std::shared_ptr<IDepartment> > > _department;
public:
    Tree() = delete;
    Tree(const float x, const float y, const float w, const float h, std::string_view caption, ICommand* command);
    Tree(std::string_view caption, ICommand* command);
    virtual ~Tree() = default;

    void setData(std::shared_ptr<std::list<std::shared_ptr<IDepartment> > > department);

    virtual void draw() override;
};