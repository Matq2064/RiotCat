cmake_minimum_required(VERSION 3.23)
project(RiotCat CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(C:/libs/SDL/include)
link_directories(C:/libs/SDL/lib/x64)

set(SOURCE_FILES main.cpp Window.h Window.cpp Drawing.h Drawing.cpp Clock.h Clock.cpp Input.h Input.cpp)
add_executable(RiotCat ${SOURCE_FILES})

target_link_libraries(RiotCat SDL2main SDL2)