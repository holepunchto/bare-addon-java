cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)
find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)

project(bare_addon C CXX)

fetch_package("github:holepunchto/libjstl#387f6d0")
fetch_package("github:holepunchto/libjnitl#a8002df")

find_package(Java)

include(UseJava)

add_bare_module(bare_addon)

target_sources(
  ${bare_addon}
  PRIVATE
    binding.cc
)

target_link_libraries(
  ${bare_addon}
  PRIVATE
    jstl
    jnitl
)

set(ANDROID_JAR ${ANDROID_HOME}/platforms/${ANDROID_PLATFORM}/android.jar)

add_jar(
  bare_addon_classes
  SOURCES
    lib/Addon.java
  INCLUDE_JARS
    ${ANDROID_JAR}
  OUTPUT_NAME classes
)

find_program(d8 d8 PATHS ${ANDROID_HOME}/build-tools/* NO_DEFAULT_PATH)

add_custom_command(
  TARGET bare_addon_classes
  POST_BUILD
  COMMAND
    ${d8}
      $<IF:$<CONFIG:Debug>,--debug,--release>
      --lib ${ANDROID_JAR}
      --output ${CMAKE_BINARY_DIR}
      ${CMAKE_BINARY_DIR}/classes.jar
)

bare_target(target)

bare_module_target("." module NAME name)

install(
  FILES
    ${CMAKE_BINARY_DIR}/classes.jar
    ${CMAKE_BINARY_DIR}/classes.dex
  DESTINATION ${target}/${name}
)
