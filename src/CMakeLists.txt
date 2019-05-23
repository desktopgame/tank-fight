cmake_minimum_required(VERSION 2.8)
project(varAppName CXX)

if(APPLE)
    set(FBXSDK_ROOT "/Applications/Autodesk/FBX SDK/2019.2")
else()
    if(NOT FBXSDK_ROOT)
        message(FATAL_ERROR "should be set a `FBXSDK_ROOT`")
    endif()
endif()

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address -O0 -DDEBUG -MMD -Wall -lstdc++ -std=c++17 -Wc++11-extensions")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
set(varExecutable "varAppName" CACHE STRING "executable file name")
set(varInstallDir ${CMAKE_INSTALL_PREFIX}/varAppName CACHE PATH "Path to install")
set(varIgnoreCompile "CMakeCXXCompilerId.cpp" "feature_tests.cpp")
set(varSrcRootDir "app")
message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(GLFW REQUIRED)
find_package(PNG REQUIRED)
find_package(ALUT REQUIRED)

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

link_directories (
    ${ALUT_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${OPENAL_LIBRARY}
    ${PNG_LIBRARY}
    ${FBXSDK_ROOT}/lib
)
add_executable(${varExecutable} ${SOURCES})
#add_definitions (${GLIB_CFLAGS_OTHER})
if(APPLE)
    # for libpng
    target_include_directories(
        ${varExecutable}
        PRIVATE
        ${ALUT_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${OPENGL_EGL_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIR}
        ${OPENAL_INCLUDE_DIR}
        ${PNG_INCLUDE_DIR}
        /usr/local/include
        ${FBXSDK_ROOT}/include
    )
else()
    target_include_directories(
        ${varExecutable}
        PRIVATE
        ${ALUT_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${OPENGL_EGL_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIR}
        ${OPENAL_INCLUDE_DIR}
        ${PNG_INCLUDE_DIR}
        ${FBXSDK_ROOT}/include
    )
endif()

target_link_libraries(
    ${varExecutable}
    PRIVATE
    ${ALUT_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${OPENAL_LIBRARY}
    ${PNG_LIBRARY}
    ${FBXSDK_ROOT}/lib
)