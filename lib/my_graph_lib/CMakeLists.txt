include_directories(${schmup_SOURCE_DIR}/includes/my_graph_lib)

add_library(my_graph_lib
  Node.cpp)
target_link_libraries(my_graph_lib 
  sfml-graphics-s
  sfml-window-s
  sfml-system-s)
