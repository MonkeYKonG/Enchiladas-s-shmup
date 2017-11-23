include_directories(${schmup_SOURCE_DIR}/includes)
include_directories(${schmup_SOURCE_DIR}/includes/schmup)
link_directories(${schmup_SOURCE_DIR}/lib)
link_directories("E:/EPITECH/lib/SFML-2.3.2/lib")
link_directories("C:/Users/Alexis/Desktop/Lib/SFML-2.3.2/lib")

add_executable(schmup
	SchmupMainMenu.cpp
	ScenePool.cpp
	SchmupGameManager.cpp
  	main.cpp)
target_link_libraries(schmup
	my_menu_lib)
