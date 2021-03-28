/*
UIElementEventHandler - helper class. Provides convertion from std::any to stored type. 
Used for commands passing from ui elements to model. Uses callback function to pass the command.
UI - is a main UI class. Stores all ui elements has to be shown, inits imgui for drawing, 
draws all elements in main loop
*/
#pragma once

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

#include "UIElement.hpp"
#include "Toolbar.hpp"
#include "Observer.hpp"

#include <map>
#include <memory>
#include <functional>
#include <SDL.h>
#include <SDL_opengl.h>

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
protected:
    SDL_Window* window;
    SDL_WindowFlags window_flags;
    SDL_GLContext gl_context;
    ImGuiIO io;
    ImVec4 clear_color;
    std::map<std::string_view, Toolbar> bars;
    std::pair<int, int> window_size;

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
    void addToolbarElement(std::string_view toolbar_name, UIElementBase* element, bool new_line = false);
    // Method for ui element creation helping. Has concrete overloading for ui element creation
    template<ElementType, typename...Args>
    UIElementBase* make_element(std::string_view caption, IObserver* handler, Args...args);

};