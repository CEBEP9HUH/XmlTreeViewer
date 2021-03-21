#pragma once
#include "Observer.hpp"
#include <string>
#include <set>
#include <any>

class IUIElement {
public:
    virtual void draw() = 0;
    virtual ~IUIElement() = default;
};

class UIElementBase: public IUIElement, public ISubject {
protected:
    struct {
        float posX;
        float posY;
        float width;
        float height;
    } _shapeRect;
    std::set<IObserver*> _observers;
    bool _strong_placement;
    std::string _caption;

    virtual void notify(const std::any& parameter) override {
        for(const auto o: _observers) {
            o->update(parameter);
        }
    }

    virtual void attach(IObserver* observer) override {
        _observers.insert(observer);
    }

    virtual void detach(IObserver* observer) override {
        _observers.erase(observer);
    }

public:
    UIElementBase() = delete;
    UIElementBase(const float x, const float y, const float w, const float h, std::string_view caption) 
    :   _shapeRect{x, y, w, h} 
    ,   _caption{caption}
    {}
    virtual ~UIElementBase() = default;

    void setPos(const float x, const float y) { 
        _shapeRect.posX = x; 
        _shapeRect.posY = y; 
        _strong_placement = true;
    }

    void setSize(const float w, const float h) { 
        _shapeRect.width = w; 
        _shapeRect.height = h; 
    }

    UIElementBase* attach_to(IObserver* observer) {
        attach(observer);
        return this;
    }

    UIElementBase* detach_from(IObserver* observer) {
        detach(observer);
        return this;
    }
    
    UIElementBase* detach_from_all() {
        _observers.clear();
        return this;
    }

    std::pair<float, float> getPos() const noexcept {
        return {_shapeRect.posX, _shapeRect.posY};
    }

    std::pair<float, float> getSize() const noexcept {
        return {_shapeRect.width, _shapeRect.height};
    }

};