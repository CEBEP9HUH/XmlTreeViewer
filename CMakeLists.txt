cmake_minimum_required(VERSION 3.2)

project(XmlTreeViewver)
set(src ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(incl ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(pugixml REQUIRED)

add_executable(${PROJECT_NAME} 
${src}/main.cpp
${src}/Department.cpp
${src}/DepXMLPugiConverter.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
${incl}
)

target_link_libraries(${PROJECT_NAME}  PRIVATE 
    pugixml
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)