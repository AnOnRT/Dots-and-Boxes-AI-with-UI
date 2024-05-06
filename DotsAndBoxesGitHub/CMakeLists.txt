#cmake_minimum_required(VERSION 3.25)
#project(DotsAndBoxes)
#
#set(CMAKE_CXX_STANDARD 17)
#
#add_executable(DotsAndBoxes main.cpp Board.h Player.h Move.h Box.h GameView.h GameController.h Board.cpp Box.cpp Player.cpp GameView.cpp GameController.cpp)

cmake_minimum_required(VERSION 3.25)
project(DotsAndBoxes)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files list
set(SOURCE_FILES main.cpp Board.h Player.h Move.h Box.h GameView.h GameController.h Board.cpp Box.cpp Player.cpp GameView.cpp GameController.cpp GridLine.h)

# Add executable target with source files
add_executable(DotsAndBoxes ${SOURCE_FILES})

# Find SFML components

# Conditional configuration based on platform
if(WIN32)
    # Specify the path to SFML static libraries on Windows
    set(SFML_DIR "YourPathTo/SFML/SFML-2.6.1/lib/cmake/SFML") # Change this to your path
    set(SFML_DLL "YourPathTo/SFML/SFML-2.6.1") # Change this to your path
    find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
    include_directories(${SFML_INCLUDE_DIR})
    add_custom_command(TARGET DotsAndBoxes POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DLL}/bin/sfml-graphics-d-2.dll"
            "${SFML_DLL}/bin/sfml-system-d-2.dll"
            "${SFML_DLL}/bin/sfml-window-d-2.dll"
            $<TARGET_FILE_DIR:DotsAndBoxes>)
else()
    find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
    include_directories(/usr/local/include)
endif()

# Include the SFML headers and link libraries
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(DotsAndBoxes sfml-system sfml-window sfml-graphics sfml-audio sfml-network)