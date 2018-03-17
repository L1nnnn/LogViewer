cmake_minimum_required(VERSION 3.0.0)
project(LogViewer_src)

set(BASE_SRC
	main.cpp
	window.cpp
	headerbar.cpp
	main_menu_button.cpp
        tree_view.cpp
        text_view.cpp
)

set(SRC
	${BASE_SRC}
)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(LogViewer ${SRC})

target_link_libraries(LogViewer
	${GTKMM_LIBRARIES}
)
