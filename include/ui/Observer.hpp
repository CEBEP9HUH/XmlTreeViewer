#pragma once
#include <any>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const std::any& parameter) = 0;
};

class ISubject {
protected:
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;

public:
    virtual ~ISubject() = default;
    virtual void notify(const std::any&parameter) = 0;
};