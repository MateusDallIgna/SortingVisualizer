cmake_minimum_required(VERSION 3.10)

project(SortingVisualizer)

add_executable(my_program 
    main.cpp
    src/algorithms.cpp
    src/render.cpp
    src/theme.cpp
)

target_link_libraries(my_program raylib)
