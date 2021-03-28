/*
Commands interface                    
*/
#pragma once


class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual bool isExecuted() = 0;
};

