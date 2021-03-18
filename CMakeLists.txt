cmake_minimum_required(VERSION 3.2)

project(XmlTreeViewver)
set(src ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(incl ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} 
${src}/main.cpp
)