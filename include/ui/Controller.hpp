#pragma once

#include "ui/UI.hpp"

#include <thread>
#include <memory>
#include <string>
#include <map>

#include "TreeContainer.hpp"

class Controller {
public:
    Controller();
    virtual ~Controller();

    void run();

protected:
    std::unique_ptr<UI> _ui;

    std::shared_ptr<Node> root = nullptr;

    //FIXME: temp
    using model_t = std::map<std::string_view, std::unique_ptr<IObserver>>;
    model_t _model;
};