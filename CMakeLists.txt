cmake_minimum_required(VERSION 3.16.3)

project(Survival-Game)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(
	"${PROJECT_NAME}" ${SOURCES} 
	external/Tily/Tily.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

target_include_directories(
	"${PROJECT_NAME}" PUBLIC
	include/
	external/Tily
)

target_link_directories(
	"${PROJECT_NAME}" PUBLIC
	libs
)

target_link_libraries(
	"${PROJECT_NAME}" PUBLIC
	sfml-graphics
	sfml-window
	sfml-system
	TGUI
)

set_target_properties("${PROJECT_NAME}"
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_NAME}"
	LIBRARY_OUTPUT_DIRECTORY "${PROJECT_NAME}"
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_NAME}"
)

file(COPY assets DESTINATION "${CMAKE_BINARY_DIR}/${PROJECT_NAME}")
