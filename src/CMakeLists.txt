cmake_minimum_required(VERSION 2.8)
project(varAppName CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_CXX_FLAGS_DEBUG "-g -coverage -fsanitize=address -O0 -DDEBUG -MMD -Wall -lstdc++")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
set(varExecutable "varAppName" CACHE STRING "executable file name")
set(varInstallDir ${CMAKE_INSTALL_PREFIX}/varAppName CACHE PATH "Path to install")
set(varIgnoreCompile "CMakeCXXCompilerId.cpp" "feature_tests.cpp")
set(varSrcRootDir "app")

message(STATUS "varInstallDir=${varInstallDir}")
message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

# enable_testing()
# add_test(
#     NAME test
#     COMMAND ruby auto/test.rb
#     #CONFIGURATIONS Debug
#     WORKING_DIRECTORY .
# )

install(DIRECTORY DESTINATION ${varInstallDir})
install(
    DIRECTORY ./../bin
    DESTINATION ${varInstallDir}
)
add_custom_target(_uninstall rm -r ${varInstallDir})
add_custom_target(_clean rm -rf ./CMakeCache.txt && rm -r CMakeFiles)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "**/*.cpp")
foreach(e IN LISTS SOURCES)
    foreach(pat IN LISTS varIgnoreCompile)
        if(${e} MATCHES ${pat})
            message("remove compile target: ${e}")
            list(REMOVE_ITEM SOURCES ${e})
            break()
        endif()
    endforeach()
endforeach()

add_executable(${varExecutable} ${SOURCES})
