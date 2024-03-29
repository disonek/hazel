
add_subdirectory(vendor/glm)
add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/Glad)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/yaml-cpp)

target_compile_options(spdlog PRIVATE ${disable_warrnings}) 
target_compile_options(imgui PRIVATE ${disable_warrnings}) 
target_compile_options(Glad PRIVATE ${disable_warrnings}) 
target_compile_options(glfw PRIVATE ${disable_warrnings}) 
target_compile_options(yaml-cpp PRIVATE ${disable_warrnings})  

add_library(
  hazel
  src/Hazel.hpp
  src/hzpch.h
  src/hazel/core/Application.cpp
  src/hazel/core/Application.hpp
  src/hazel/core/Timestep.hpp
  src/hazel/core/Base.hpp
  src/hazel/core/EntryPoint.hpp
  src/hazel/events/ApplicationEvent.hpp
  src/hazel/events/Event.hpp
  src/hazel/events/KeyEvent.hpp
  src/hazel/events/MouseEvent.hpp
  src/hazel/ImGui/ImGuiBuild.cpp
  src/hazel/ImGui/ImGuiLayer.cpp
  src/hazel/ImGui/ImGuiLayer.hpp
  src/hazel/core/Input.hpp
  src/hazel/core/KeyCodes.hpp
  src/hazel/core/Layer.cpp
  src/hazel/core/Layer.hpp
  src/hazel/core/LayerStack.cpp
  src/hazel/core/LayerStack.hpp
  src/hazel/core/Log.cpp
  src/hazel/core/Log.hpp
  src/hazel/core/MouseCodes.hpp
  src/hazel/core/Window.cpp
  src/hazel/core/Window.hpp
  src/hazel/debug/Instrumentor.hpp
  src/hazel/renderer/OrthographicCameraController.cpp
  src/hazel/renderer/OrthographicCameraController.hpp
  src/hazel/renderer/Buffer.cpp
  src/hazel/renderer/Buffer.hpp
  src/hazel/renderer/Camera.hpp
  src/hazel/renderer/Framebuffer.cpp
  src/hazel/renderer/Framebuffer.hpp
  src/hazel/renderer/GraphicsContext.cpp
  src/hazel/renderer/GraphicsContext.hpp
  src/hazel/renderer/OrthographicCamera.cpp
  src/hazel/renderer/OrthographicCamera.hpp
  src/hazel/renderer/RenderCommand.cpp
  src/hazel/renderer/RenderCommand.hpp
  src/hazel/renderer/Renderer.cpp
  src/hazel/renderer/Renderer.hpp
  src/hazel/renderer/RendererAPI.cpp
  src/hazel/renderer/RendererAPI.hpp
  src/hazel/renderer/Shader.cpp
  src/hazel/renderer/Shader.hpp
  src/hazel/renderer/Texture.cpp
  src/hazel/renderer/Texture.hpp
  src/hazel/renderer/SubTexture2D.cpp
  src/hazel/renderer/SubTexture2D.hpp
  src/hazel/renderer/VertexArray.cpp
  src/hazel/renderer/VertexArray.hpp
  src/hazel/renderer/Renderer2D.cpp
  src/hazel/renderer/Renderer2D.hpp
  src/hazel/scene/Scene.cpp
  src/hazel/scene/Scene.hpp
  src/hazel/scene/SceneCamera.cpp
  src/hazel/scene/SceneCamera.hpp
  src/hazel/scene/ScriptableEntity.hpp
  src/hazel/scene/SceneSerializer.cpp
  src/hazel/scene/SceneSerializer.hpp
  src/hazel/scene/Components.hpp
  src/hazel/scene/Entity.cpp
  src/hazel/scene/Entity.hpp
  src/hazel/utils/PlatformUtils.hpp
  src/platform/OpenGL/OpenGLBuffer.cpp
  src/platform/OpenGL/OpenGLBuffer.hpp 
  src/platform/OpenGL/OpenGLFramebuffer.cpp
  src/platform/OpenGL/OpenGLFramebuffer.hpp 
  src/platform/OpenGL/OpenGLContext.cpp
  src/platform/OpenGL/OpenGLContext.hpp
  src/platform/OpenGL/OpenGLRendererAPI.cpp
  src/platform/OpenGL/OpenGLRendererAPI.hpp
  src/platform/OpenGL/OpenGLShader.cpp
  src/platform/OpenGL/OpenGLShader.hpp
  src/platform/OpenGL/OpenGLTexture.cpp
  src/platform/OpenGL/OpenGLTexture.hpp
  src/platform/OpenGL/OpenGLVertexArray.cpp
  src/platform/OpenGL/OpenGLVertexArray.hpp
  src/platform/windows/WindowsInput.cpp
  src/platform/windows/WindowsWindow.cpp
  src/platform/windows/WindowsWindow.hpp
  src/platform/windows/WindowsPlatformUtils.cpp
  vendor/stb_image/stb_image.hpp
  vendor/stb_image/stb_image.cpp)



 
  
target_compile_definitions(
  hazel PUBLIC HZ_DEBUG=1 HZ_PLATFORM_WINDOWS=1 GLFW_INCLUDE_NONE=1
               _CRT_SECURE_NO_WARNINGS=1 HZ_ENABLE_ASSERTS=1 _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING=1)

target_precompile_headers(hazel PUBLIC src/hzpch.h)

target_link_libraries(
  hazel
  PUBLIC glm::glm spdlog CONAN_PKG::entt imgui
  PRIVATE project_warnings project_options glfw Glad yaml-cpp )
  
target_include_directories(
  hazel
  PUBLIC src src/hazel/core src/hazel
  PRIVATE vendor/stb_image)
