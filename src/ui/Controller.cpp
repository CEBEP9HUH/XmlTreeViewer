#include "ui/Controller.hpp"
#include "ui/Model.hpp"
#include "Command.hpp"

Controller::Controller()
:   _ui{new UI(1000, 700)}
{
    _model.emplace("systemCmdHandler", new UIElementEventHandler<ICommand*>(Model::systemCommandHandler));

    ICommand* undo = new CommandUndo();
    _ui->addToolbarElement("tree", 
                _ui->make_element<UI::ElementType::Button>("Undo", 
                                                            _model["systemCmdHandler"].get(), 
                                                            undo));
    ICommand* redo = new CommandRedo();
    _ui->addToolbarElement("tree", 
                _ui->make_element<UI::ElementType::Button>("Redo", 
                                                            _model["systemCmdHandler"].get(), 
                                                            redo));
}

void Controller::run() {
    std::thread th(&UI::run, _ui.get());
    th.join();
}



Controller::~Controller()
{

}