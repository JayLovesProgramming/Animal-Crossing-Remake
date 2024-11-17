cmake_minimum_required(VERSION 3.10)
project(Game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

# Include the dependencies
include_directories(C:/Users/jayxw/Desktop/AnimalCrossing/dependencies/rlImGui C:/Users/jayxw/Desktop/AnimalCrossing/dependencies/raylib/include C:/Users/jayxw/Desktop/AnimalCrossing/dependencies/imgui)

# Add executable
add_executable(Game src/Application/Application.cpp src/Main.cpp)

# Disable specific warnings for MSVC
if(MSVC)
    target_compile_options(Game PRIVATE
        /W3                # Set warning level to 3
        /wd4244           # Disable warning C4244
        /wd4477           # Disable warning C4477
    )
endif()

# Link the libraries
if (WIN32)
    target_link_libraries(Game C:/Users/jayxw/Desktop/AnimalCrossing/dependencies/raylib/lib/raylib.lib winmm)
elseif (UNIX)
    target_link_libraries(Game C:/Users/jayxw/Desktop/AnimalCrossing/dependencies/raylib/lib/libraylib.a m pthread dl rt)
endif()

target_compile_definitions(Game PRIVATE _CRT_SECURE_NO_WARNINGS)
