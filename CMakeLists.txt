cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(CumNormal VERSION 1.0)

set(CMAKE_DEBUG_POSTFIX d)

add_library(cumnorm_compiler_flags INTERFACE)
target_compile_features(cumnorm_compiler_flags INTERFACE cxx_std_11)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(cumnorm_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

if(APPLE)
  set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
elseif(UNIX)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif()

# configure a header file to pass the version number only
configure_file(CumNormalConfig.h.in CumNormalConfig.h)

# add the CumFunctions library
add_subdirectory(CumFunctions)

# add the executable
add_executable(CumNormal CumNormal.cpp)
set_target_properties(CumNormal PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(CumNormal PUBLIC CumFunctions)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(CumNormal PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# add the install targets
install(TARGETS CumNormal DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/CumNormalConfig.h"
  DESTINATION include
  )

# enable testing
enable_testing()

# does the application run
add_test(NAME Runs COMMAND CumNormal 25)

# does the usage message work?
add_test(NAME Usage COMMAND CumNormal)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
  )

# define a function to simplify adding tests
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)

# do a bunch of result based tests
do_test(CumNormal 4 "4 is 2")
do_test(CumNormal 9 "9 is 3")
do_test(CumNormal 5 "5 is 2.236")
do_test(CumNormal 7 "7 is 2.645")
do_test(CumNormal 25 "25 is 5")
do_test(CumNormal -25 "-25 is [-nan|nan|0]")
do_test(CumNormal 0.0001 "0.0001 is 0.01")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License")
set(CPACK_PACKAGE_VERSION_MAJOR "${CumNormal_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CumNormal_VERSION_MINOR}")
include(CPack)

# install the configuration targets
install(EXPORT CumFunctionsTargets
  FILE CumFunctionsTargets.cmake
  DESTINATION lib/cmake/CumNorm
)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/CumFunctionsConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/example"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/CumFunctionsConfigVersion.cmake"
  VERSION "${CumNormal_VERSION_MAJOR}.${CumNormal_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

# install the configuration file
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/CumFunctionsConfig.cmake
  DESTINATION lib/cmake/CumNorm
  )

# generate the export targets for the build tree
# needs to be after the install(TARGETS ) command
export(EXPORT CumFunctionsTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/CumFunctionsTargets.cmake"
)
