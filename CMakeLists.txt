########################################

### Constants ###

cmake_minimum_required(VERSION 3.10)

project(
  webview-pixi
  VERSION 0.1.0
  HOMEPAGE_URL "https://github.com/decipaliz/webview-pixi"
  LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

########################################

### Modules ###

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(internal_colors)

########################################

### External libraries and programs ###

find_program(NPM_EXECUTABLE npm)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext)

FetchContent_Declare(
  webview
  GIT_REPOSITORY https://github.com/webview/webview.git
  GIT_TAG 0.12.0
)
FetchContent_MakeAvailable(webview)

FetchContent_Declare(
  base64
  GIT_REPOSITORY https://github.com/aklomp/base64.git
  GIT_TAG v0.5.2
)
FetchContent_MakeAvailable(base64)

########################################

### Target: html ###

if(NPM_EXECUTABLE)
  file(GLOB_RECURSE HTML_SOURCES "app/index.html" "app/src/*")

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/index_html.h
    COMMAND npm --prefix ${CMAKE_CURRENT_SOURCE_DIR}/app i
    COMMAND npm --prefix ${CMAKE_CURRENT_SOURCE_DIR}/app run build
    COMMAND npm --prefix ${CMAKE_CURRENT_SOURCE_DIR}/scripts i
    COMMAND npm --prefix ${CMAKE_CURRENT_SOURCE_DIR}/scripts run create-index-html --
      ${CMAKE_CURRENT_SOURCE_DIR}/app/dist/index.html
      ${CMAKE_CURRENT_BINARY_DIR}/index_html.h
    DEPENDS ${HTML_SOURCES}
    COMMENT "Generating the index_html.h file"
  )
else()
  message(WARNING "${BOLD}npm${RESET} is required to generate the index_html.h file")
  message(WARNING "Building the JavaScript code will be unavailable")
endif()

add_custom_target(
  html
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/index_html.h
)

########################################

### Target: resources ###

if(NPM_EXECUTABLE)
  file(GLOB_RECURSE HTML_SOURCES "app/index.html" "app/src/*")

  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/resources.bin
      ${CMAKE_CURRENT_BINARY_DIR}/resources.h
    COMMAND npm --prefix ${CMAKE_CURRENT_SOURCE_DIR}/scripts i
    COMMAND npm --prefix ${CMAKE_CURRENT_SOURCE_DIR}/scripts run bundle-resources --
      ${CMAKE_CURRENT_SOURCE_DIR}/resources
      ${CMAKE_CURRENT_BINARY_DIR}/resources.bin
      ${CMAKE_CURRENT_BINARY_DIR}/resources-map.h
    DEPENDS ${HTML_SOURCES}
    COMMENT "Generating the resources.bin and resources-map.h files"
  )
else()
  message(WARNING "${BOLD}npm${RESET} is required to generate the resources.bin and resources-map.h files")
  message(WARNING "Bundling resources will be unavailable")
endif()

add_custom_target(
  resources
  DEPENDS
  ${CMAKE_CURRENT_BINARY_DIR}/resources.bin
  ${CMAKE_CURRENT_BINARY_DIR}/resources-map.h
)

########################################

### Target: webview-pixi ###

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(webview-pixi ${SOURCES})
add_dependencies(webview-pixi html resources)
target_include_directories(webview-pixi PRIVATE "src" PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(webview-pixi PRIVATE webview::core_static PRIVATE base64)

########################################
