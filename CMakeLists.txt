project(bdash)
cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(bdash
    src/bdash.cpp
)

target_link_libraries(bdash PRIVATE
	sfml-window
	sfml-graphics
	sfml-system
	sfml-audio
)

file(COPY "${PROJECT_SOURCE_DIR}/resources" DESTINATION "${PROJECT_BINARY_DIR}")
