cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(project_y
	VERSION 0.0.1
	DESCRIPTION "my mmorpg"
	LANGUAGES C
)

add_executable(project_y
	src/main.c
)

add_subdirectory(ENGINE_NAME)

target_link_libraries(project_y PRIVATE
	ENGINE_NAME
)

target_include_directories(project_y PRIVATE
	ENGINE_NAME
)

target_compile_options(project_y PRIVATE -Wall -Wextra -Wpedantic -DDEBUG)
target_compile_features(project_y PRIVATE c_std_23)
