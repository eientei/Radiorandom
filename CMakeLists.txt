<<<<<<< HEAD
option(USE_CLANG "build application with clang" OFF)
if(USE_CLANG)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/clang/toolchain.cmake)
endif(USE_CLANG)

cmake_minimum_required(VERSION 2.6)
project(RadioRandom)

include_directories(src)
add_definitions(-g)

#### controller ####
set(controller_sources
    src/radiorandom/controller/generic/superclass.cpp
    src/radiorandom/controller/generic/rpc.cpp
    src/radiorandom/controller/generic/controller.cpp
    src/radiorandom/controller/generic/server.cpp

    src/radiorandom/controller/core/controller.cpp

    src/radiorandom/controller/installer/controller.cpp
    src/radiorandom/controller/installer/rpc.cpp

    src/radiorandom/controller/js/controller.cpp

=======
cmake_minimum_required(VERSION 2.8)

########################################################################

add_definitions(-pedantic -Wall -g)
set(CMAKE_BUILD_TYPE Debug)
include_directories(
	../src
>>>>>>> parent of 711bf3a... Upcoming new release
)
add_library(controller ${controller_sources})
#### end controller ####

#### core ####
set(core_sources
    src/radiorandom/core/executor/core.cpp

<<<<<<< HEAD
=======
########################################################################

project(GenTemplates)
set (Templates_html
	../src/Templates/HTML/Master/Generic.tmpl
	../src/Templates/HTML/Master/Menu.tmpl
	../src/Templates/HTML/Master/Master.tmpl

	../src/Templates/HTML/Generic/TOS.tmpl
	../src/Templates/HTML/Generic/Index.tmpl
	../src/Templates/HTML/Generic/Setup.tmpl
	../src/Templates/HTML/Generic/Error.tmpl

	../src/Templates/HTML/Users/Users.tmpl
	../src/Templates/HTML/Users/UsersShow.tmpl
	../src/Templates/HTML/Users/UsersLogout.tmpl
	../src/Templates/HTML/Users/UsersLogin.tmpl
	../src/Templates/HTML/Users/UsersNew.tmpl
	../src/Templates/HTML/Users/UsersProfile.tmpl
	../src/Templates/HTML/Users/UsersSearch.tmpl
	../src/Templates/HTML/Users/UsersProfilePassword.tmpl
	../src/Templates/HTML/Users/UsersProfileSettings.tmpl
	../src/Templates/HTML/Users/UsersProfileEmail.tmpl

)
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp
	COMMAND cppcms_tmpl_cc ${Templates_html} -o ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp
	DEPENDS ${Templates_html}
)
add_library(templates SHARED ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp)
target_link_libraries(templates 
	Generic-data
	Generic-marukup
	
	-lcppcms
>>>>>>> parent of 711bf3a... Upcoming new release
)
add_library(core ${core_sources})
#### end core ####

#### manager ####
set(manager_sources
    src/radiorandom/manager/mutex/manager.cpp
    src/radiorandom/manager/sql/manager.cpp

<<<<<<< HEAD
=======
########################################################################

project (Generic)

add_library(Generic-io
	../src/Generic/IO/PIO/PIO.cpp
>>>>>>> parent of 711bf3a... Upcoming new release
)
add_library(manager ${manager_sources})
#### end manager ####

#### util ####
set(util_sources
    src/radiorandom/util/string/util.cpp
    src/radiorandom/util/fs/util.cpp
    src/radiorandom/util/sql/util.cpp
)
add_library(util ${util_sources})
#### end util ####


<<<<<<< HEAD
#### template ####
set(html_template_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/generic/view.tmpl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/generic/error.tmpl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/generic/please_install.tmpl

    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/js/index.tmpl

    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/core/index.tmpl

    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/installer/index.tmpl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/installer/install.tmpl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/installer/install_finished.tmpl

    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/user/index.tmpl
)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
    COMMAND cppcms_tmpl_cc ${html_template_sources} -o ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
    DEPENDS ${html_template_sources}
)
#### end template ####

#### wrapper ####
set(wrapper_sources
    src/radiorandom/wrapper/session/wrapper.cpp
)
add_library(wrapper ${wrapper_sources})
#### end wrapper ####

#### main ####
set(main_sources
    src/radiorandom/main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
)

set(main_libs
    cppcms
    booster
    cppdb

    core
    controller
    manager
    util
    wrapper
)

add_executable(radiorandom ${main_sources})
target_link_libraries(radiorandom ${main_libs})
#### end main ####
=======
add_library(Generic-data
	../src/Generic/Data/Content/ContentURL/ContentURL.cpp
	../src/Generic/Data/Content/Set/Set.cpp
	../src/Generic/Data/Content/SetMenu/SetMenu.cpp
	../src/Generic/Data/Content/SetUsers/SetUsers.cpp
	../src/Generic/Data/Format/Format.cpp
)

add_library(Generic-marukup
	../src/Generic/Markup/Menu/Menu.cpp
	../src/Generic/Markup/Navigation/Navigation.cpp
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
	../src/Generic/DB/TagParser/TagParser.cpp
	../src/Generic/DB/Users/Users.cpp
	../src/Generic/DB/Posts/Posts.cpp
	
)
target_link_libraries(Generic-db Generic-hash)


########################################################################

project (Static)
add_library(Static
	../src/Static/Static.cpp
	
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
	
	templates
	
	Static
	
	-lcppcms
	-lcppdb
	-lmagic
	-lssl
	-luriparser
)

add_executable(radiorandom-web-server
	../src/Apps/Web/Web.cpp


	../src/Apps/Web/Master/Get.cpp
	../src/Apps/Web/Master/Prepare.cpp
	../src/Apps/Web/Master/Constructor.cpp
	../src/Apps/Web/Master/Main.cpp

	../src/Apps/Web/Generic/Setup.cpp
	../src/Apps/Web/Generic/Error.cpp
	../src/Apps/Web/Generic/TOS.cpp
	../src/Apps/Web/Generic/Index.cpp

	
	../src/Apps/Web/Users/Users.cpp
	../src/Apps/Web/Users/UsersShow.cpp
	../src/Apps/Web/Users/UsersNew.cpp
	../src/Apps/Web/Users/UsersLogout.cpp
	../src/Apps/Web/Users/UsersLogin.cpp
	../src/Apps/Web/Users/UsersProfile.cpp
	../src/Apps/Web/Users/UsersProfileEmail.cpp
	../src/Apps/Web/Users/UsersProfilePassword.cpp
	../src/Apps/Web/Users/UsersProfileSettings.cpp
	../src/Apps/Web/Users/UsersSearch.cpp

	

)
target_link_libraries(radiorandom-web-server ${web-server_lib})
set_target_properties(radiorandom-web-server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")
>>>>>>> parent of 711bf3a... Upcoming new release
