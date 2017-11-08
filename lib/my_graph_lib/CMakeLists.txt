include_directories(${schmup_SOURCE_DIR}/includes)
include_directories(${schmup_SOURCE_DIR}/includes/my_graph_lib)

add_library(my_graph_lib
  Node.cpp
  SpriteObject.cpp
  TextObject.cpp
  AnimatedObject.cpp
  MoovableObject.cpp
  ResourcesLoader.cpp
  Scene.cpp
  GameManager.cpp
  XMLNode.cpp
  XMLParser.cpp
  MessagesException.cpp)

target_link_libraries(my_graph_lib
  sfml-graphics-d
  sfml-window-d
  sfml-system-d)
