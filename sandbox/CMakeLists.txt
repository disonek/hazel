add_executable(sandbox 
  src/SandboxApp.cpp 
  src/Sandbox2D.hpp 
  src/Sandbox2D.cpp
  src/ExampleLayer.hpp 
  src/ExampleLayer.cpp
  src/ParticleSystem.hpp
  src/ParticleSystem.cpp)

target_link_libraries(
  sandbox
  PUBLIC hazel
  PRIVATE project_warnings project_options)
  
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/Debug)
