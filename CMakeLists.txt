cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(project_y
	VERSION 0.0.1
	DESCRIPTION "Some kind of game"
	LANGUAGES C
)


set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	string(APPEND CMAKE_C_FLAGS " -DDEBUG")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	string(APPEND CMAKE_C_FLAGS " -DRELEASE -mwindows")
endif()


# ukiyo
add_subdirectory(ukiyo)


# game
add_executable(game
	src/main.c
)

target_include_directories(game PRIVATE
	ukiyo
)

target_link_libraries(game PRIVATE
	ukiyo
)
