include_directories(${schmup_SOURCE_DIR}/includes)
include_directories(${schmup_SOURCE_DIR}/includes/my_objects_lib)

add_library(my_objects_lib
	Bullet.cpp
	Shooter.cpp
	Enemy.cpp
	Player.cpp
	Border.cpp
	Cursor.cpp
	SpriteButton.cpp
	Panel.cpp
	ObjectPool.cpp
	EnemiesPool.cpp)

target_link_libraries(my_objects_lib
	my_graph_lib)