#include "Controller.hpp"
#include "Model.hpp"
#include "Command.hpp"
#include "ui/Tree.hpp"

#include <functional>
#include <thread>

Controller::Controller()
:   _ui{new UI(500, 500)}
,   _model{new Model()}
{
    std::shared_ptr<ICommand> undo(new CommandUndo(_model->getCommandHistory()));
    _ui->addToolbarElement("tree", 
        _ui->make_element<UI::ElementType::Button>("Undo", 
            new UIElementEventHandler<std::shared_ptr<ICommand>>(std::bind(&Model::addCommand, _model.get(), std::placeholders::_1, false)), 
            undo));

    std::shared_ptr<ICommand> redo(new CommandRedo(_model->getCommandHistory()));
    _ui->addToolbarElement("tree", 
                _ui->make_element<UI::ElementType::Button>("Redo", 
                new UIElementEventHandler<std::shared_ptr<ICommand>>(std::bind(&Model::addCommand, _model.get(), std::placeholders::_1, false)), 
                redo));

    auto tree = _ui->make_element<UI::ElementType::Tree>("tree_view", 
            new UIElementEventHandler<std::shared_ptr<ICommand>>(std::bind(&Model::addCommand, _model.get(), std::placeholders::_1, true)));

    reinterpret_cast<Tree*>(tree)->setData(_model->getDepartment());
    tree->setSize(100,500);
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