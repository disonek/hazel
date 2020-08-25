cmake_minimum_required (VERSION 3.13)

project(hazel)
set(CMAKE_BUILD_TYPE=Debug)

add_library(hazel STATIC
    hazel/src/hazel/Application.cpp
    hazel/src/hazel/Application.hpp
    hazel/src/hazel/core/Timestep.hpp
    hazel/src/hazel/Core.hpp
    hazel/src/hazel/EntryPoint.hpp
    hazel/src/hazel/events/ApplicationEvent.hpp
    hazel/src/hazel/events/Event.hpp
    hazel/src/hazel/events/KeyEvent.hpp
    hazel/src/hazel/events/MouseEvent.hpp
    hazel/src/hazel/ImGui/ImGuiBuild.cpp
    hazel/src/hazel/ImGui/ImGuiLayer.cpp
    hazel/src/hazel/ImGui/ImGuiLayer.hpp
    hazel/src/hazel/Input.hpp
    hazel/src/hazel/KeyCodes.hpp
    hazel/src/hazel/Layer.cpp
    hazel/src/hazel/Layer.hpp
    hazel/src/hazel/LayerStack.cpp
    hazel/src/hazel/LayerStack.hpp
    hazel/src/hazel/Log.cpp
    hazel/src/hazel/Log.hpp
    hazel/src/hazel/MouseButtonCodes.hpp
    hazel/src/hazel/renderer/Buffer.cpp
    hazel/src/hazel/renderer/Buffer.hpp
    hazel/src/hazel/renderer/GraphicsContext.hpp
    hazel/src/hazel/renderer/OrthographicCamera.cpp
    hazel/src/hazel/renderer/OrthographicCamera.hpp
    hazel/src/hazel/renderer/RenderCommand.cpp
    hazel/src/hazel/renderer/RenderCommand.hpp
    hazel/src/hazel/renderer/Renderer.cpp
    hazel/src/hazel/renderer/Renderer.hpp
    hazel/src/hazel/renderer/RendererAPI.cpp
    hazel/src/hazel/renderer/RendererAPI.hpp
    hazel/src/hazel/renderer/Shader.cpp
    hazel/src/hazel/renderer/Shader.hpp
    hazel/src/hazel/renderer/Texture.cpp
    hazel/src/hazel/renderer/Texture.hpp
    hazel/src/hazel/renderer/VertexArray.cpp
    hazel/src/hazel/renderer/VertexArray.hpp
    hazel/src/hazel/Window.hpp
    hazel/src/Hazel.hpp
    hazel/src/platform/OpenGL
    hazel/src/platform/OpenGL/OpenGLBuffer.cpp
    hazel/src/platform/OpenGL/OpenGLBuffer.hpp
    hazel/src/platform/OpenGL/OpenGLContext.cpp
    hazel/src/platform/OpenGL/OpenGLContext.hpp
    hazel/src/platform/OpenGL/OpenGLRendererAPI.cpp
    hazel/src/platform/OpenGL/OpenGLRendererAPI.hpp
    hazel/src/platform/OpenGL/OpenGLShader.cpp
    hazel/src/platform/OpenGL/OpenGLShader.hpp
    hazel/src/platform/OpenGL/OpenGLTexture.cpp
    hazel/src/platform/OpenGL/OpenGLTexture.hpp
    hazel/src/platform/OpenGL/OpenGLVertexArray.cpp
    hazel/src/platform/OpenGL/OpenGLVertexArray.hpp
    hazel/src/platform/windows/WindowsInput.cpp
    hazel/src/platform/windows/WindowsInput.hpp
    hazel/src/platform/windows/WindowsWindow.cpp
    hazel/src/platform/windows/WindowsWindow.hpp
    hazel/src/hzpch.cpp
    hazel/src/hzpch.h
	hazel/vendor/stb_image/stb_image.hpp
	hazel/vendor/stb_image/stb_image.cpp
    )

add_subdirectory(hazel/vendor/glm)
add_subdirectory(hazel/vendor/GLFW)
add_subdirectory(hazel/vendor/Glad)
add_subdirectory(hazel/vendor/imgui)
add_subdirectory(hazel/vendor/spdlog)
	
	
add_compile_definitions(
    HZ_PLATFORM_WINDOWS=1
    HZ_BUILD_DLL=1
    GLFW_INCLUDE_NONE=1
    _CRT_SECURE_NO_WARNINGS2=1
    )

target_precompile_headers(hazel
    PUBLIC
    hazel/src/hzpch.h
 )

 target_compile_options(hazel
    PUBLIC
     -g -Wall
    PRIVATE
     -fPIC)

target_link_libraries(hazel
    PUBLIC
        glm
        glfw
        Glad
        imgui
        spdlog
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
        hazel/src
    )
    
 add_executable(sandbox
     sandbox/src/Sandbox.cpp
 )
 
 target_link_libraries(sandbox
    PUBLIC
        hazel
 )
