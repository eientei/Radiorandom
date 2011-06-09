cmake_minimum_required(VERSION 2.8)

########################################################################

add_definitions(-pedantic -Wall -g)
set(CMAKE_BUILD_TYPE Debug)
include_directories(
	../src/Templates/layouts
	../src/Data
)

########################################################################

project(GenTemplates)
set (Templates_html
	../src/Templates/HTML/menu.html.tmpl

	../src/Templates/HTML/master.html.tmpl
	../src/Templates/HTML/error.html.tmpl
	../src/Templates/HTML/setup.html.tmpl
	../src/Templates/HTML/index.html.tmpl
	../src/Templates/HTML/tos.html.tmpl
	
	../src/Templates/HTML/users.html.tmpl
	../src/Templates/HTML/users_new.html.tmpl
	../src/Templates/HTML/users_show.html.tmpl
	../src/Templates/HTML/users_login.html.tmpl
	../src/Templates/HTML/users_profile.html.tmpl
	../src/Templates/HTML/users_profile_password.html.tmpl
	../src/Templates/HTML/users_profile_settings.html.tmpl

	../src/Templates/HTML/posts.html.tmpl
	../src/Templates/HTML/posts_new.html.tmpl
)
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp
	COMMAND cppcms_tmpl_cc ${Templates_html} -o ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp
	DEPENDS ${Templates_html}
)
add_library(templates_html SHARED ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp)
target_link_libraries(templates_html -lcppcms)

########################################################################

project(Data)
add_library(data-pstring STATIC 
	../src/Data/PString/PString.cpp
	../src/Data/PString/PlainIOHighLevel.cpp
)

########################################################################

project(Server)

set(server_lib
	data-pstring
	templates_html
	-lcppcms
	-lcppdb
	-lmagic
	-lssl
	-lcrypto
)

add_executable(radiorandom-server 
	../src/Apps/Server/Server.cpp
	../src/Apps/Server/Users.cpp
	../src/Apps/Server/Posts.cpp
	../src/Templates/layouts/helperfuncs.cpp
)
target_link_libraries(radiorandom-server ${server_lib})
set_target_properties(radiorandom-server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")
