project(bdash)
cmake_minimum_required(VERSION 3.3)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

add_executable(bdash
	src/bdash.c
	src/map.c
	src/player.c
)

target_link_libraries(bdash PRIVATE
	allegro
	allegro_font
	allegro_image
)

file(COPY "${PROJECT_SOURCE_DIR}/resources" DESTINATION "${PROJECT_BINARY_DIR}")
