/*
observer-publisher pattern
*/
#pragma once
#include <any>
#include <memory>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const std::any& parameter) = 0;
};

class ISubject {
protected:
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;

public:
    virtual ~ISubject() = default;
    virtual void notify(const std::any&parameter) = 0;
};