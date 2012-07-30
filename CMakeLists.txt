project(radiorandom)
cmake_minimum_required(VERSION 2.8)

include_directories(src/model)

set(CONTROLLER_SRC)
set(MODEL_SRC)
set(TMPL_SRC)
set(VIEW_SRC)
set(DATA_SRC)
set(MISC_SRC)
set(CORE_SRC)

file(GLOB_RECURSE PARTS cmake.d/*.cmake)

foreach(PART ${PARTS})
  include(${PART})
endforeach()

foreach(f ${VIEW_SRC})
    set(VIEW_SRC_PREFIXED ${VIEW_SRC_PREFIXED} ${CMAKE_CURRENT_SOURCE_DIR}/${f})
endforeach(f)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
    COMMAND cppcms_tmpl_cc ${VIEW_SRC_PREFIXED} -o ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
    DEPENDS ${VIEW_SRC}
)


set(ALL_SRC
  ${CONTROLLER_SRC}
  ${MODEL_SRC}
  ${TMPL_SRC}
  ${VIEW_SRC}
  ${DATA_SRC}
  ${MISC_SRC}
  ${CORE_SRC}
  ${CMAKE_CURRENT_BINARY_DIR}/html.cpp
  src/main.cpp

)

set(ALL_LIB
  cppcms
  booster
  cppdb
)

add_executable(${PROJECT_NAME} ${ALL_SRC})
target_link_libraries(${PROJECT_NAME} ${ALL_LIB})
