cmake_minimum_required(VERSION 2.8)

########################################################################

add_definitions(-pedantic -Wall -g)
set(CMAKE_BUILD_TYPE Debug)
include_directories(
	../src
)

########################################################################

project(GenTemplates)
set (Templates_html
	../src/Templates/HTML/Master/Generic.tmpl
	../src/Templates/HTML/Master/Menu.tmpl
	../src/Templates/HTML/Master/Master.tmpl

	#../src/Templates/HTML/Generic/TOS.tmpl
	#../src/Templates/HTML/Generic/Index.tmpl
	#../src/Templates/HTML/Generic/Setup.tmpl
	#../src/Templates/HTML/Generic/Error.tmpl

	#../src/Templates/HTML/Users/UsersLogout.tmpl
	#../src/Templates/HTML/Users/UsersLogin.tmpl
	#../src/Templates/HTML/Users/UsersSearch.tmpl
	#../src/Templates/HTML/Users/UsersNew.tmpl
	#../src/Templates/HTML/Users/UsersProfile.tmpl
	#../src/Templates/HTML/Users/Users.tmpl
	#../src/Templates/HTML/Users/UsersShow.tmpl
	#../src/Templates/HTML/Users/UsersProfilePassword.tmpl
	#../src/Templates/HTML/Users/UsersProfileSettings.tmpl
	#../src/Templates/HTML/Users/UsersProfileEmail.tmpl

)
#add_custom_command(
	#OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp
	#COMMAND cppcms_tmpl_cc ${Templates_html} -o ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp
	#DEPENDS ${Templates_html}
#)
#add_library(templates SHARED ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp)
#target_link_libraries(templates 
	#proto
	#helpers
	#-lcppcms
#)

########################################################################

project (Generic)

add_library(Generic-io
	../src/Generic/IO/PIO/PIO.cpp
)

add_library(Generic-data
	../src/Generic/Data/Content/ContentURL/ContentURL.cpp
	../src/Generic/Data/Content/Set/Set.cpp
	../src/Generic/Data/Content/SetMenu/SetMenu.cpp
	../src/Generic/Data/Content/SetUsers/SetUsers.cpp
	../src/Generic/Data/Format/Format.cpp
)

add_library(Generic-marukup
	../src/Generic/Markup/Menu/Menu.cpp
)

add_library(Generic-hash
	../src/Generic/Hash/Hash.cpp
	../src/Generic/Hash/SHA1/SHA1.cpp
)
add_library(Generic-filesystem
	../src/Generic/FileSystem/Check/Check.cpp
	../src/Generic/FileSystem/Create/Create.cpp
)
add_library(Generic-db
	../src/Generic/DB/Interact/Interact.cpp
	../src/Generic/DB/Users/Users.cpp
	
)



########################################################################

project(Apps)

set(web-server_lib
	Generic-io
	Generic-data
	Generic-hash
	Generic-filesystem
	Generic-db
	Generic-marukup
	
	-lcppcms
	-lcppdb
	-lmagic
	-lssl
	-luriparser
)

add_executable(radiorandom-web-server
	../src/Apps/Web/Web.cpp


	#../src/Apps/Web/Master/Get.cpp
	#../src/Apps/Web/Master/Prepare.cpp
	#../src/Apps/Web/Master/Constructor.cpp
	#../src/Apps/Web/Master/Main.cpp

	#../src/Apps/Web/Generic/Setup.cpp
	#../src/Apps/Web/Generic/Error.cpp
	#../src/Apps/Web/Generic/TOS.cpp
	#../src/Apps/Web/Generic/Index.cpp

	#../src/Apps/Web/Users/UsersLogin.cpp
	#../src/Apps/Web/Users/Users.cpp
	#../src/Apps/Web/Users/UsersProfile.cpp
	#../src/Apps/Web/Users/UsersLogout.cpp
	#../src/Apps/Web/Users/UsersProfileEmail.cpp
	#../src/Apps/Web/Users/UsersProfilePassword.cpp
	#../src/Apps/Web/Users/UsersProfileSettings.cpp
	#../src/Apps/Web/Users/UsersSearch.cpp
	#../src/Apps/Web/Users/UsersNew.cpp
	#../src/Apps/Web/Users/UsersShow.cpp

)
target_link_libraries(radiorandom-web-server ${web-server_lib})
set_target_properties(radiorandom-web-server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")
