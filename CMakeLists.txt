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

)
add_library(controller ${controller_sources})
#### end controller ####

#### core ####
set(core_sources
    src/radiorandom/core/executor/core.cpp

)
add_library(core ${core_sources})
#### end core ####

#### manager ####
set(manager_sources
    src/radiorandom/manager/mutex/manager.cpp
    src/radiorandom/manager/sql/manager.cpp

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
