#include "ui/Controller.hpp"
#include "ui/Model.hpp"
#include "Command.hpp"


#include "DepXMLPugiConverter.hpp"
#include "Department.hpp"
#include "ui/Tree.hpp"

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




    ICommand* qwe = nullptr;
    auto tree = _ui->make_element<UI::ElementType::Tree>("derevo", 
                                                            nullptr, 
                                                            qwe);
    auto buf = std::make_shared<DepXMLPugiConverter::_departments_container_t>();;
    DepXMLPugiConverter a(buf);
    a.setFilePath("../data/tsl.xml");
    a.load();
    reinterpret_cast<Tree*>(tree)->setData(buf);
    _ui->addToolbarElement("tree", tree);
}

void Controller::run() {
    std::thread th(&UI::run, _ui.get());
    th.join();
}



Controller::~Controller()
{

}