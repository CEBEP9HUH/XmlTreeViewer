cmake_minimum_required(VERSION 3.2)
# cmake -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake ..

project(XmlTreeViewver)
set(src ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(incl ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(libs ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(pugixml REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} 
${src}/main.cpp
${src}/Controller.cpp
${src}/Model.cpp
${src}/ui/UI.cpp
${src}/ui/Button.cpp
${src}/ui/Tree.cpp
${src}/ui/Toolbar.cpp
${src}/xmlparser/DepXMLPugiConverter.cpp
${src}/commands/CommandHistory.cpp
${src}/commands/SystemCommand.cpp
${src}/commands/TreeCommand.cpp

${libs}/imgui/imgui.cpp
${libs}/imgui/imgui_tables.cpp
${libs}/imgui/imgui_widgets.cpp
${libs}/imgui/imgui_draw.cpp
${libs}/imgui/imgui_demo.cpp
${libs}/imgui/backends/imgui_impl_opengl2.cpp
${libs}/imgui/backends/imgui_impl_sdl.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
${incl}
${libs}/imgui
${libs}/imgui/backends
${OPENGL_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}  PRIVATE 
    Threads::Threads
    pugixml
    SDL2::SDL2 
    ${OPENGL_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)