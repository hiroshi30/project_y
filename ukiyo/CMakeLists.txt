cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(ukiyo
	VERSION 0.0.1
	DESCRIPTION "3D game engine"
	LANGUAGES C
)


set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -DGLEW_STATIC")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	string(APPEND CMAKE_C_FLAGS " -DDEBUG")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	string(APPEND CMAKE_C_FLAGS " -DRELEASE")
endif()


# OpenGL
find_package(OpenGL REQUIRED)


# GLFW
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw-3.3.10)


# GLEW
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glew-2.1.0/build/cmake)


# SOIL
add_subdirectory(external/Simple-OpenGL-Image-Library)


# ukiyo
add_library(ukiyo STATIC
	src/random.c

	src/vec3.c
	src/mat4x4.c
	
	src/camera.c
	
	src/engine.c
	src/shader.c
)

target_include_directories(ukiyo PUBLIC
	${OPENGL_INCLUDE_DIRS}
    external/glew-2.1.0/include
	external/glfw-3.3.10/include
	external/Simple-OpenGL-Image-Library/src

	src
)

target_link_libraries(ukiyo PUBLIC
	OpenGL::GL
	glew_s
	glfw
	SOIL
)
