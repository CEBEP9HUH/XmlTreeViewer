#include "Controller.hpp"
#include "Model.hpp"
#include "Command.hpp"
#include "ui/Tree.hpp"

#include <functional>
#include <thread>

Controller::Controller()
:   _ui{new UI(1000, 700)}
,   _model{new Model()}
{
    std::shared_ptr<ICommand> undo(new CommandUndo());
    _ui->addToolbarElement("tree", 
        _ui->make_element<UI::ElementType::Button>("Undo", 
            new UIElementEventHandler<std::shared_ptr<ICommand>>(std::bind(&Model::systemCommandHandler, _model.get(), std::placeholders::_1)), 
            undo));

    std::shared_ptr<ICommand> redo(new CommandRedo());
    _ui->addToolbarElement("tree", 
                _ui->make_element<UI::ElementType::Button>("Redo", 
                new UIElementEventHandler<std::shared_ptr<ICommand>>(std::bind(&Model::systemCommandHandler, _model.get(), std::placeholders::_1)), 
                redo));

    auto tree = _ui->make_element<UI::ElementType::Tree>("tree_view", 
            new UIElementEventHandler<std::shared_ptr<ICommand>>(std::bind(&Model::departmentCmdHandler, _model.get(), std::placeholders::_1)));

    reinterpret_cast<Tree*>(tree)->setData(_model->getDepartment());
    _ui->addToolbarElement("tree", tree);
}

void Controller::run() {
    std::thread th(&UI::run, _ui.get());
    th.join();
}



Controller::~Controller()
{

}