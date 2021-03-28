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
    
    std::shared_ptr<ICommand> undo(new CommandUndo(_model->getCommandHistory()));
    auto no_history_handler = std::bind(&Model::addCommand, _model.get(), std::placeholders::_1, false);
    std::shared_ptr<IObserver> no_history_observer = std::make_shared<UIElementEventHandler<std::shared_ptr<ICommand>>>(no_history_handler);
    _ui->addToolbarElement("tree", 
        _ui->make_element<UI::ElementType::Button>("Undo", 
            no_history_observer, 
            undo));

    std::shared_ptr<ICommand> redo(new CommandRedo(_model->getCommandHistory()));
    _ui->addToolbarElement("tree", 
                _ui->make_element<UI::ElementType::Button>("Redo", 
                no_history_observer, 
                redo));

    auto with_history_handler = std::bind(&Model::addCommand, _model.get(), std::placeholders::_1, true);
    std::shared_ptr<IObserver> with_history_observer = std::make_shared<UIElementEventHandler<std::shared_ptr<ICommand>>>(with_history_handler);
    auto tree = _ui->make_element<UI::ElementType::Tree>("tree_view", with_history_observer);
    reinterpret_cast<Tree*>(tree)->setData(_model->getDepartment());
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