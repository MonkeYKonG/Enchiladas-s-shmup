include_directories(${schmup_SOURCE_DIR}/includes)
link_directories(${schmup_SOURCE_DIR}/lib)

add_executable(schmup
  main.cpp)
target_link_libraries(schmup
	my_menu_lib)
