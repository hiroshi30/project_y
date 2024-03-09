cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(ENGINE_NAME
	VERSION 0.0.1
	DESCRIPTION "ENGINE_NAME is my game engine"
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

add_subdirectory(external/Simple-OpenGL-Image-Library)

add_library(ENGINE_NAME STATIC
	src/main.c
	src/new_math.c
	src/vec3.c
	src/vec4.c
	src/mat4x4.c
)

target_include_directories(ENGINE_NAME PUBLIC
	${OPENGL_INCLUDE_DIRS}
	external/glew-2.1.0/include
	external/glfw-3.3.10/include
	external/Simple-OpenGL-Image-Library/src

	include
	src
)

target_link_libraries(ENGINE_NAME PUBLIC
	OpenGL::GL
	glfw
	glew_s
	SOIL
)

# -mwindows - remove console output
target_compile_options(ENGINE_NAME PRIVATE -Wall -Wextra -Wpedantic)
target_compile_features(ENGINE_NAME PRIVATE c_std_23)
