#include "commands/SystemCommand.hpp"

CommandRedo::CommandRedo(std::shared_ptr<ICommandsHistory> command_history)
:   SystemCommandBase{}
,   _history{command_history}
{

}

void CommandRedo::execute() {
    _history->redo();
}

void CommandRedo::undo() {
    _history->undo();
}


CommandUndo::CommandUndo(std::shared_ptr<ICommandsHistory> command_history)
:   SystemCommandBase{}
,   _history{command_history}
{

}

void CommandUndo::execute() {
    _history->undo();
}

void CommandUndo::undo() {
    _history->redo();
}