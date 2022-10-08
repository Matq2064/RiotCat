project(Project)
cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(C:/libs/SDL/include)
link_directories(C:/libs/SDL/lib/x64)

add_executable(RiotCat src/main.cpp src/Window.h src/Window.cpp src/Drawing.h src/Drawing.cpp src/Clock.h src/Clock.cpp src/Input.h src/Input.cpp src/Files.cpp src/Files.h src/Tiles.cpp src/Tiles.h src/Character.cpp src/Character.h src/Rect.h src/Rect.cpp)
add_executable(Editor src/editor.cpp src/Window.h src/Window.cpp src/Drawing.h src/Drawing.cpp src/Clock.h src/Clock.cpp src/Input.h src/Input.cpp src/Files.cpp src/Files.h src/Tiles.cpp src/Tiles.h src/Character.cpp src/Character.h src/Rect.h src/Rect.cpp)

target_link_libraries(RiotCat SDL2main SDL2)
target_link_libraries(Editor SDL2main SDL2)