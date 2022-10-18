project(Project)
cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(C:/libs/SDL/include C:/libs/SDL_ttf/include)
link_directories(C:/libs/SDL/lib/x64 C:/libs/SDL_ttf/lib/x64)

add_executable(RiotCat src/main.cpp src/RiotCat/Window.h src/RiotCat/Window.cpp src/RiotCat/Drawing.h src/RiotCat/Drawing.cpp src/RiotCat/Clock.h src/RiotCat/Clock.cpp src/RiotCat/Input.h src/RiotCat/Input.cpp src/RiotCat/Files.cpp src/RiotCat/Files.h src/RiotCat/Character.cpp src/RiotCat/Character.h src/RiotCat/Rect.h src/RiotCat/Rect.cpp src/RiotCat/Tile.h src/RiotCat/Tile.cpp src/RiotCat/editor/ETilemap.h src/RiotCat/editor/ETilemap.cpp src/RiotCat/Gameworld.h src/RiotCat/Gameworld.cpp)
add_executable(Editor src/editor.cpp src/RiotCat/Window.h src/RiotCat/Window.cpp src/RiotCat/Drawing.h src/RiotCat/Drawing.cpp src/RiotCat/Clock.h src/RiotCat/Clock.cpp src/RiotCat/Input.h src/RiotCat/Input.cpp src/RiotCat/Files.cpp src/RiotCat/Files.h src/RiotCat/Character.cpp src/RiotCat/Character.h src/RiotCat/Rect.h src/RiotCat/Rect.cpp src/RiotCat/Tile.h src/RiotCat/Tile.cpp src/RiotCat/editor/ETilemap.h src/RiotCat/editor/ETilemap.cpp src/RiotCat/Gameworld.h src/RiotCat/Gameworld.cpp)

target_link_libraries(RiotCat SDL2main SDL2 SDL2_ttf)
target_link_libraries(Editor SDL2main SDL2 SDL2_ttf)
