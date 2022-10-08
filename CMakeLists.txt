project(Project)
cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(C:/libs/SDL/include)
link_directories(C:/libs/SDL/lib/x64)

add_executable(RiotCat main.cpp Window.h Window.cpp Drawing.h Drawing.cpp Clock.h Clock.cpp Input.h Input.cpp Files.cpp Files.h Tiles.cpp Tiles.h Character.cpp Character.h Rect.h Rect.cpp)
add_executable(Editor editor.cpp Window.h Window.cpp Drawing.h Drawing.cpp Clock.h Clock.cpp Input.h Input.cpp Files.cpp Files.h Tiles.cpp Tiles.h Character.cpp Character.h Rect.h Rect.cpp)

target_link_libraries(RiotCat SDL2main SDL2)
target_link_libraries(Editor SDL2main SDL2)