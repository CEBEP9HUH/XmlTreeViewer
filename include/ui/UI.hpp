#pragma once

#include <list>
#include <map>
#include <memory>
#include <SDL.h>
#include <SDL_opengl.h>
#include <functional>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

#include "UIElement.hpp"
#include "Toolbar.hpp"
#include "Observer.hpp"

class IUIElementEventHandler: public IObserver {
public:
    virtual ~IUIElementEventHandler() = default;
};

template<typename T>
class UIElementEventHandler: public IUIElementEventHandler {
protected:
    using callback_t = std::function<void(const T&)>;
    callback_t _callback;

public:
    UIElementEventHandler(const callback_t& callback)
    :   _callback{callback}
    {

    }
    virtual ~UIElementEventHandler() = default;
    virtual void update(const std::any& parameter) override {
        if(typeid(T) == parameter.type()) {
            _callback(std::any_cast<T>(parameter));
        }
    }
};



class UI {
public:
    enum class ElementType {
        Button,
        Tree
    };

    UI(const int window_width, const int window_height);
    virtual ~UI() = default;
    int init();
    void run();
    void deinit();

    void addToolbarElement(std::string_view toolbar_name, UIElementBase* element);

    template<ElementType, typename...Args>
    UIElementBase* make_element(std::string_view caption, IObserver* handler, Args...args);

protected:
    SDL_Window* window;
    SDL_WindowFlags window_flags;
    SDL_GLContext gl_context;
    ImGuiIO io;
    ImVec4 clear_color;

    std::map<std::string_view, Toolbar> bars;
    std::pair<int, int> window_size;
    constexpr static const float bottom_toolbar_height = 20.f;
};