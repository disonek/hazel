cmake_minimum_required (VERSION 3.13)

project(hazel)

add_library(hazel STATIC
    hazel/src/Hazel.hpp
    hazel/src/hzpch.cpp
    hazel/src/hzpch.h
    hazel/src/hazel/core/Application.cpp
    hazel/src/hazel/core/Application.hpp
    hazel/src/hazel/core/Timestep.hpp
    hazel/src/hazel/core/Core.hpp
    hazel/src/hazel/core/EntryPoint.hpp
    hazel/src/hazel/events/ApplicationEvent.hpp
    hazel/src/hazel/events/Event.hpp
    hazel/src/hazel/events/KeyEvent.hpp
    hazel/src/hazel/events/MouseEvent.hpp
    hazel/src/hazel/ImGui/ImGuiBuild.cpp
    hazel/src/hazel/ImGui/ImGuiLayer.cpp
    hazel/src/hazel/ImGui/ImGuiLayer.hpp
    hazel/src/hazel/core/Input.hpp
    hazel/src/hazel/core/KeyCodes.hpp
    hazel/src/hazel/core/Layer.cpp
    hazel/src/hazel/core/Layer.hpp
    hazel/src/hazel/core/LayerStack.cpp
    hazel/src/hazel/core/LayerStack.hpp
    hazel/src/hazel/core/Log.cpp
    hazel/src/hazel/core/Log.hpp
    hazel/src/hazel/core/MouseButtonCodes.hpp
    hazel/src/hazel/core/Window.hpp
    hazel/src/hazel/renderer/OrthographicCameraController.cpp 
    hazel/src/hazel/renderer/OrthographicCameraController.hpp
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
    hazel/src/hazel/renderer/Renderer2D.cpp
    hazel/src/hazel/renderer/Renderer2D.hpp
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
    _CRT_SECURE_NO_WARNINGS=1
    )

target_precompile_headers(hazel
    PUBLIC
    hazel/src/hzpch.h
 )

 target_link_libraries(hazel
    PUBLIC
        glm
        glfw
        Glad
        imgui
        spdlog
    )
    
target_compile_options(hazel
   PRIVATE
   /W4 # Baseline reasonable warnings
   /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss of data
   /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
   /w14263 # 'function': member function does not override any base class virtual member function
   /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not
           # be destructed correctly
   /w14287 # 'operator': unsigned/negative constant mismatch
   /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside
           # the for-loop scope
   /w14296 # 'operator': expression is always 'boolean_value'
   /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
   /w14545 # expression before comma evaluates to a function which is missing an argument list
   /w14546 # function call before comma missing argument list
   /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
   /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
   /w14555 # expression has no effect; expected expression with side- effect
   /w14619 # pragma warning: there is no warning number 'number'
   /w14640 # Enable warning on thread un-safe static member initialization
   /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
   /w14905 # wide string literal cast to 'LPSTR'
   /w14906 # string literal cast to 'LPWSTR'
   /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
   /permissive- # standards conformance mode for MSVC compiler.
    )

target_compile_features(hazel
    PRIVATE
		cxx_std_17
	)

target_include_directories(hazel
    PUBLIC
        hazel/src
    PRIVATE
        hazel/src/hazel
        hazel/vendor/stb_image
    )
    
 add_executable(sandbox
    sandbox/src/SandboxApp.cpp
    sandbox/src/Sandbox2D.hpp
    sandbox/src/Sandbox2D.cpp
    )
 
 target_link_libraries(sandbox
    PUBLIC
        hazel
 )

 file(COPY sandbox/assets DESTINATION ${CMAKE_BINARY_DIR})
 file(COPY sandbox/assets DESTINATION ${CMAKE_BINARY_DIR}/Debug)

