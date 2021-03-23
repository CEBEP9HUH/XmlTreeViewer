#include "ui/Controller.hpp"
#include "ui/Model.hpp"
#include "Command.hpp"


#include "DepXMLPugiConverter.hpp"
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


    
    DepXMLPugiConverter a;
    a.setFilePath("../data/tsl.xml");
    Node* root = new Node();
    root->setValue("Root");
    a.load(root);
    reinterpret_cast<Tree*>(tree)->setData(root);
    _ui->addToolbarElement("tree", tree);
}

void Controller::run() {
    std::thread th(&UI::run, _ui.get());
    th.join();
}



Controller::~Controller()
{

}