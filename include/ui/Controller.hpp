#pragma once

#include "ui/UI.hpp"

#include <thread>
#include <memory>
#include <string>
#include <map>

class Controller {
public:
    Controller();
    virtual ~Controller();

    void run();

protected:
    std::unique_ptr<UI> _ui;
    //FIXME: temp
    using model_t = std::map<std::string_view, std::unique_ptr<IObserver>>;
    model_t _model;
};