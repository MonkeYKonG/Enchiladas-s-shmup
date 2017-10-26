include_directories(${schmup_SOURCE_DIR}/includes)
include_directories(${schmup_SOURCE_DIR}/includes/my_objects_lib)

add_library(my_objects_lib
	Cursor.cpp
	MousePointer.cpp
	Panel.cpp)

target_link_libraries(my_objects_lib
	my_graph_lib)