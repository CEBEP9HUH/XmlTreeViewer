#pragma once

#include "ui/UI.hpp"
#include "Model.hpp"

#include <memory>

class Controller {
public:
    Controller();
    virtual ~Controller();
    void run();

protected:
    std::unique_ptr<UI> _ui;
    std::unique_ptr<Model> _model;
};