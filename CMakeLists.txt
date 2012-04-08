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
    src/radiorandom/controller/generic/controller.cpp
    src/radiorandom/controller/core/controller.cpp
    src/radiorandom/controller/installer/controller.cpp

)
add_library(controller ${controller_sources})
#### end controller ####

#### executor ####
set(executor_sources
    src/radiorandom/executor/core.cpp
    src/radiorandom/executor/already_running.cpp
    src/radiorandom/executor/configuration_parse_error.cpp
    src/radiorandom/executor/file_not_found.cpp

)
add_library(executor ${executor_sources})
#### end executor ####

#### util ####
set(util_sources
    src/radiorandom/util/string/util.cpp
    src/radiorandom/util/fs/util.cpp
)
add_library(util ${util_sources})
#### end util ####

#### template ####
set(html_template_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/generic/view.tmpl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/generic/error.tmpl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/generic/please_install.tmpl

    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/core/index.tmpl

    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/installer/index.tmpl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/installer/install.tmpl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/radiorandom/view/html/installer/install_finished.tmpl
)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
    COMMAND cppcms_tmpl_cc ${html_template_sources} -o ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
    DEPENDS ${html_template_sources}
)
#### end template ####


#### main ####
set(main_sources
    src/radiorandom/main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
)

set(main_libs
    cppcms
    booster
    cppdb

    executor
    controller
    util
)

add_executable(radiorandom ${main_sources})
target_link_libraries(radiorandom ${main_libs})
#### end main ####
