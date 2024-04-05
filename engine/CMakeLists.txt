cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(engine
	VERSION 0.0.1
	DESCRIPTION "it is my game engine"
	LANGUAGES C
)


# OpenGL
find_package(OpenGL REQUIRED)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "" FORCE)


# GLFW
add_subdirectory(external/glfw-3.3.10)

set(BUILD_UTILS OFF CACHE BOOL "" FORCE)


# GLEW
add_subdirectory(external/glew-2.1.0/build/cmake)


# SOIL
add_subdirectory(external/Simple-OpenGL-Image-Library)


# engine
add_library(engine STATIC
	src/additional_math.c
	src/vec3.c
	src/mat4x4.c
	src/camera.c
	
	src/engine.c
	src/shader.c
	src/texture.c
)

target_include_directories(engine PUBLIC
	${OPENGL_INCLUDE_DIRS}
	external/glew-2.1.0/include
	external/glfw-3.3.10/include
	external/Simple-OpenGL-Image-Library/src

	src
	include
)

target_link_libraries(engine PUBLIC
	OpenGL::GL
	glew_s
	glfw
	SOIL
)

# -mwindows - remove console output
target_compile_options(engine PRIVATE -Wall -Wextra -Wpedantic -D${CMAKE_BUILD_TYPE} -DGLEW_STATIC)
target_compile_features(engine PRIVATE c_std_23)
