include_directories(${schmup_SOURCE_DIR}/includes)
include_directories(${schmup_SOURCE_DIR}/includes/my_menu_lib)

add_library(my_menu_lib
	MainMenu.cpp
	SchmupScene.cpp)

target_link_libraries(my_menu_lib
	my_objects_lib)