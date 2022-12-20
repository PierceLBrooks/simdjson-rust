cmake_minimum_required(VERSION 3.14)

project(simdjson_cxx)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  simdjson
  GIT_REPOSITORY https://github.com/simdjson/simdjson.git
  GIT_TAG  tags/v3.0.1
  GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(simdjson)

file(GLOB_RECURSE CXXBRIDGE_LIBS ${CMAKE_INSTALL_PREFIX}/../../cxx-*/out/*${CMAKE_STATIC_LIBRARY_SUFFIX})
set(SIMDJSON ${CMAKE_INSTALL_PREFIX}/../../../../..)
set(CXXBRIDGE ${SIMDJSON}/target/cxxbridge)
set(SIMDJSON_DIRS )
file(GLOB_RECURSE DIRS ${CMAKE_INSTALL_PREFIX}/../../**/*.h)
foreach(DIR ${DIRS})
  get_filename_component(SIMDJSON_DIR ${DIR} DIRECTORY)
  list(FIND SIMDJSON_DIRS ${SIMDJSON_DIR}/.. FOUND)
  if(FOUND LESS 0)
    list(APPEND SIMDJSON_DIRS ${SIMDJSON_DIR}/..)
    include_directories(${SIMDJSON_DIR}/..)
  endif()
endforeach()

include_directories(${SIMDJSON})
include_directories(${CXXBRIDGE})

add_library(cxxbridge STATIC IMPORTED)
set_target_properties(cxxbridge PROPERTIES IMPORTED_LOCATION ${CXXBRIDGE_LIBS})

add_library(simdjson_cxx SHARED src/simdjson_cxx.cc ${CXXBRIDGE}/simdjson-rust/src/bridge.rs.cc)
target_link_libraries(simdjson_cxx simdjson cxxbridge)

install(TARGETS simdjson_cxx)

