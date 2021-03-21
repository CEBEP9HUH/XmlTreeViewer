#include "ui/UI.hpp"
#include "ui/Button.hpp"

UI::UI(const int window_width, const int window_height) 
:   window_size{window_width, window_height}
{
    bars.emplace(std::piecewise_construct,
                std::forward_as_tuple("tree"), 
                std::forward_as_tuple(0.f, 0.f, float(window_width)/2, float(window_height), "tree"));
}

template<>
UIElementBase* UI::make_element<UI::ElementType::Button, ICommand*>(std::string_view caption, IObserver* handler, ICommand* command) {
    return (new Button(caption, command))->attach_to(handler);
}

void UI::addToolbarElement(std::string_view toolbar_name, UIElementBase* element) {
    if(bars.count(toolbar_name.data())) {
        bars[toolbar_name.data()].append(element);
    }
}

int UI::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        return -1;
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("XmlTreeViewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size.first, window_size.second, window_flags);
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    return 0;
}

void UI::run() {
    bool done = false;
    init();
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        float dx = float(window_size.first), dy = float(window_size.second);
        SDL_GetWindowSize(window, &window_size.first, &window_size.second);
        dx = window_size.first / dx;
        dy = window_size.second / dy;

        for(auto& [unused, bar]: bars) {
            auto [x, y] = bar.getPos();
            bar.setPos(x*dx, y*dy);
            auto [x1, y1] = bar.getSize();
            bar.setSize(x1*dx, y1*dy);
            bar.draw();
        }

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
    deinit();
}

void UI::deinit() {
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}