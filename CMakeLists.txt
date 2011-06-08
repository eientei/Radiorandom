cmake_minimum_required(VERSION 2.8)

########################################################################

add_definitions(-pedantic -Wall -g)
set(CMAKE_BUILD_TYPE Debug)
include_directories(
	../src/templates/html
)

########################################################################

project(GenTemplates)
set (Templates_html
	../src/templates/html/menu.tmpl
	../src/templates/html/master.tmpl
	../src/templates/html/setup.tmpl
	../src/templates/html/index.tmpl
)
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp
	COMMAND cppcms_tmpl_cc ${Templates_html} -o ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp
	DEPENDS ${Templates_html}
)
add_library(templates_html SHARED ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp)
target_link_libraries(templates_html -lcppcms)

########################################################################

project(Server)

set(server_lib
	templates_html
	-lcppcms
	-lcppdb
)

add_executable(radiorandom-server ../src/apps/server.cpp)
target_link_libraries(radiorandom-server ${server_lib})
set_target_properties(radiorandom-server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")
