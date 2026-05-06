cmake_minimum_required(VERSION 3.25)
project(SmartTransit VERSION 1.0.0 LANGUAGES CXX)

# Global Compiler Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Mission-Critical Warning Levels
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find the Gear
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
qt_standard_project_setup()

# Gather the Recon - Cleaned up GLOBs to avoid duplicates
file(GLOB_RECURSE SRC "src/*.cpp")
file(GLOB_RECURSE HDR "include/*.h")

# Build the Main Executable
add_executable(SmartTransitApp WIN32 ${SRC} ${HDR})

# Tactical Include Paths
target_include_directories(SmartTransitApp PRIVATE include)

# Link the Firepower
target_link_libraries(SmartTransitApp 
    PRIVATE 
    Qt6::Widgets 
    Qt6::Core 
    Qt6::Gui
)

# Define GUI flag for the code
target_compile_definitions(SmartTransitApp PRIVATE SMARTTRANSIT_WITH_GUI)