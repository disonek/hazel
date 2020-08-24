cmake_minimum_required (VERSION 3.13)

project(hazel)
set(CMAKE_BUILD_TYPE=Debug)

add_library(hazel STATIC
    src/*.hpp,
	src/*.h,
	src/*.cpp,
	vendor/stb_image/*.hpp,
	vendor/stb_image/*.cpp,
	vendor/glm/glm/*.hpp,
	vendor/glm/glm/*.inl
    )

target_compile_definitions(hazel PUBLIC 
	HZ_PLATFORM_WINDOWS,
	HZ_BUILD_DLL,
	GLFW_INCLUDE_NONE,
	_CRT_SECURE_NO_WARNINGS
	)

include(cmake/PrecompiledHeader.cmake)
add_precompiled_header(hazel hzpch.hpp SOURCE_CXX hazel/src/hzpch.cpp FORCEINCLUDE)

target_compile_options(hazel
   PUBLIC
    -g -Wall
   PRIVATE
    -fPIC)

target_link_libraries(hazel
    PRIVATE
    )

target_compile_features(hazel
    PUBLIC
		cxx_std_17
	)

target_include_directories(hazel
	PUBLIC
		hazel/vendor/GLFW/include
		hazel/vendor/Glad/include
		hazel/vendor/imgui
		hazel/vendor/glm
		hazel/vendor/stb_image
	)

