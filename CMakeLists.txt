cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)
find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-android REQUIRED PATHS node_modules/cmake-android)

project(bare_addon C CXX)

use_java()

fetch_package("github:holepunchto/libjstl#387f6d0")
fetch_package("github:holepunchto/libjnitl#a6824b4")

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

find_android_jar(android_jar)

add_dex(
  bare_addon_classes
  SOURCES
    lib/Addon.java
  INCLUDE_JARS
    ${android_jar}
)

bare_target(target)

bare_module_target("." module NAME name)

install(
  FILES
    $<TARGET_PROPERTY:bare_addon_classes,JAR_FILE>
    $<TARGET_PROPERTY:bare_addon_classes,DEX_FILE>
  DESTINATION ${target}/${name}
)
