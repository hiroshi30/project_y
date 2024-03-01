cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(engine
	VERSION 0.0.1
	DESCRIPTION "my game engine"
	LANGUAGES C
)

find_package(OpenGL REQUIRED)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw-3.3.10)

set(BUILD_UTILS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glew-2.1.0/build/cmake)


add_library(engine STATIC
	src/main.c
)

target_include_directories(engine PUBLIC
	${OPENGL_INCLUDE_DIRS}
	external/glew-2.1.0/include
	external/glfw-3.3.10/include

	include
)

target_link_libraries(engine PUBLIC
	OpenGL::GL
	glfw
	glew_s
)

# -mwindows - remove console output
target_compile_options(engine PRIVATE -Wall -Wextra -Wpedantic)
target_compile_features(engine PRIVATE c_std_23)
