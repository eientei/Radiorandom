project(radiorandom)
cmake_minimum_required(VERSION 2.8)

include_directories(src/model)

set(html_template_sources
    src/view/html/base.tmpl
    src/view/html/error.tmpl
    src/view/html/index.tmpl
)

foreach(f ${html_template_sources})
    set(html_template_sources_realpath ${html_template_sources_realpath} ${CMAKE_CURRENT_SOURCE_DIR}/${f})
endforeach(f)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
    COMMAND cppcms_tmpl_cc ${html_template_sources_realpath} -o ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
    DEPENDS ${html_template_sources}
)


set(SRC_LIST
# main
    src/main.cpp

# core
    src/radiorandom.cpp

# controllers
    src/controller/base.cpp
    src/controller/root.cpp
    src/controller/index.cpp

# models
    src/model/base.h
    src/model/index.h
    src/model/error.h

# views
    ${CMAKE_CURRENT_BINARY_DIR}/html.cpp

# misc
    workenv/config.json

# templates
    ${html_template_sources}
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME}
    cppcms
    booster
    cppdb
)
