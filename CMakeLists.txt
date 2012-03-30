cmake_minimum_required (VERSION 2.6)
project (RadioRandom)

include_directories (src)

add_definitions(-g)

set (radiorandom_html_templates
	${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/generic_view.tmpl
	
	${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/core/index.tmpl

	${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/user/index.tmpl

	${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/post/index.tmpl
	${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/post/upload.tmpl

	${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/installer/index.tmpl
	${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/installer/install.tmpl
	${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/installer/please_install.tmpl
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
	COMMAND cppcms_tmpl_cc ${radiorandom_html_templates} -o ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
	DEPENDS ${radiorandom_html_templates}
)

set (radiorandom_util_sources
	src/radiorandom/util/fs/fs.cpp
	src/radiorandom/util/string/string.cpp
)

add_library(radiorandom-util ${radiorandom_util_sources})

set (radiorandom_sources 
	src/radiorandom/main.cpp
	src/radiorandom/controller/generic_controller.cpp
	src/radiorandom/controller/http_error_codes.cpp
	src/radiorandom/controller/core/core.cpp
	src/radiorandom/controller/post/post.cpp
	src/radiorandom/controller/user/user.cpp
	src/radiorandom/controller/installer/installer.cpp

	${CMAKE_CURRENT_BINARY_DIR}/html.cpp
)
set (radiorandom_libs 
	-lcppcms
	-lbooster
	radiorandom-util
)

add_executable(radiorandom ${radiorandom_sources})
target_link_libraries(radiorandom ${radiorandom_libs})
