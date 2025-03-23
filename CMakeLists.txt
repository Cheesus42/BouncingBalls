cmake_minimum_required(VERSION 3.10)

# Projektname
project(BouncingBalls)

# Setze die C++-Standardversion
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Finde SDL2
find_package(SDL2 REQUIRED)

# Füge das ausführbare Ziel hinzu
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Inkludiere SDL2-Header
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})

# Binde SDL2-Bibliotheken ein
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
