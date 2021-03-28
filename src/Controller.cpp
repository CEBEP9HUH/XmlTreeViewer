#include "Controller.hpp"
#include "Model.hpp"
#include "commands/SystemCommand.hpp"
#include "commands/TreeCommand.hpp"
#include "ui/Tree.hpp"

#include <functional>
#include <thread>

Controller::Controller()
:   _ui{new UI(500, 500)}
,   _model{new Model()}
{
    
    auto cmd_handler_no_history = new UIElementEventHandler<std::shared_ptr<ICommand>>(std::bind(&Model::addCommand, _model.get(), std::placeholders::_1, false));
    std::shared_ptr<ICommand> undo(new CommandUndo(_model->getCommandHistory()));
    _ui->addToolbarElement("tree", 
        _ui->make_element<UI::ElementType::Button>("Undo", 
            cmd_handler_no_history, 
            undo));

    std::shared_ptr<ICommand> redo(new CommandRedo(_model->getCommandHistory()));
    _ui->addToolbarElement("tree", 
                _ui->make_element<UI::ElementType::Button>("Redo", 
                cmd_handler_no_history, 
                redo));

    auto tree = _ui->make_element<UI::ElementType::Tree>("tree_view", 
            new UIElementEventHandler<std::shared_ptr<ICommand>>(std::bind(&Model::addCommand, _model.get(), std::placeholders::_1, true)));

    reinterpret_cast<Tree*>(tree)->setData(_model->getDepartment());
    // tree->setSize(100,500);
    _ui->addToolbarElement("tree", tree, true);
}

void Controller::run() {
    auto ui_thread = std::thread(&UI::run, _ui.get());
    auto model_thread = std::thread(&Model::run, _model.get());
    ui_thread.join();
    _model->exit();
    model_thread.join();
}


Controller::~Controller()
{

}