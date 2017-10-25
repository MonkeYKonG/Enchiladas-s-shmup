include_directories(${schmup_SOURCE_SIR}/includes)
include_directories(${schmup_SOURCE_SIR}/includes/menu_lib)

add_library(menu_lib
	)

target_link_libraries(menu_lib
	my_graph_lib)