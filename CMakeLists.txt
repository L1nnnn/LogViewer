cmake_minimum_required(VERSION 3.0.0)
project(LogViewer)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM gtkmm-3.0)

add_compile_options(-std=c++11)
include_directories("${CMAKE_BINARY_DIR}/src")

add_subdirectory(src)

if (UNIX)
	if (APPLE)
	else()
		install(FILES log-viewer.desktop DESTINATION /usr/share/applications)
		install(CODE "execute_process(COMMAND update-desktop-database)")
	endif()
endif()
