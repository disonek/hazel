add_executable(hazelnut
  src/HazelNutApp.cpp 
  src/EditorLayer.hpp 
  src/EditorLayer.cpp
  )

target_link_libraries(
  hazelnut
  PUBLIC hazel
  PRIVATE project_warnings project_options)
  
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/Debug)
