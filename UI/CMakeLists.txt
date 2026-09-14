cmake_minimum_required(VERSION 3.16)
project(RS1_Test_UI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML (simple 2D graphics + input)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(RS1_Test_UI
    src/main.cpp
    src/Application.cpp
    src/PhaseSelector.cpp
    src/Phase1.cpp
    src/Phase2.cpp
    src/RobotController.cpp
)

target_include_directories(RS1_Test_UI PRIVATE src)
target_link_libraries(RS1_Test_UI PRIVATE sfml-graphics sfml-window sfml-system)