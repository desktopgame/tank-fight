cmake_minimum_required(VERSION 2.8)
project(TankFight CXX)
#
#opengl
#   glfw
#   glew
#   glut
#openal
#   alut
#other
#   png
#   fbxsdk
#

if(APPLE)
    set(FBXSDK_ROOT "/Applications/Autodesk/FBX SDK/2019.2" CACHE PATH "Path to FBXSDK")
else()
    set(FBXSDK_ROOT "YOUR_FBXSDK" CACHE PATH "Path to FBXSDK")
endif()

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
if(APPLE)
    set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address -O0 -DDEBUG -MMD -Wall -lstdc++ -std=c++17 -Wc++11-extensions")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -MMD -Wall -lstdc++ -std=c++17 -Wc++11-extensions")
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
set(TF_EXECUTABLE "TankFight" CACHE STRING "executable file name")
set(TF_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/TankFight CACHE PATH "Path to install")
set(TF_IGNORE_COMPILE "CMakeCXXCompilerId.cpp" "feature_tests.cpp")

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(GLFW REQUIRED)
find_package(PNG REQUIRED)
find_package(ALUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)


message(STATUS "TF_INSTALL_DIR=${TF_INSTALL_DIR}")
message(STATUS "OPENGL_INCLUDE_DIR=${OPENGL_INCLUDE_DIR}")
message(STATUS "OPENGL_LIBRARIES=${OPENGL_LIBRARIES}")

message(STATUS "OPENAL_INCLUDE_DIR=${OPENAL_INCLUDE_DIR}")
message(STATUS "OPENAL_LIBRARY=${OPENAL_LIBRARY}")

message(STATUS "GLFW_INCLUDE_DIR=${GLFW_INCLUDE_DIR}")
message(STATUS "GLFW_LIBRARIES=${GLFW_LIBRARIES}")

message(STATUS "PNG_INCLUDE_DIR=${PNG_INCLUDE_DIR}")
message(STATUS "PNG_LIBRARY=${PNG_LIBRARY}")

message(STATUS "ALUT_INCLUDE_DIR=${ALUT_INCLUDE_DIR}")
message(STATUS "ALUT_LIBRARY=${ALUT_LIBRARY}")

message(STATUS "GLEW_INCLUDE_DIRS=${GLEW_INCLUDE_DIRS}")
message(STATUS "GLEW_LIBRARIES=${GLEW_LIBRARIES}")

message(STATUS "GLUT_INCLUDE_DIR=${GLUT_INCLUDE_DIR}")
message(STATUS "GLUT_LIBRARY=${GLUT_LIBRARY}")

message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

# enable_testing()
# add_test(
#     NAME test
#     COMMAND ruby auto/test.rb
#     #CONFIGURATIONS Debug
#     WORKING_DIRECTORY .
# )

install(DIRECTORY DESTINATION ${TF_INSTALL_DIR})
install(
    DIRECTORY ./../bin
    DESTINATION ${TF_INSTALL_DIR}
)
add_custom_target(_uninstall rm -r ${TF_INSTALL_DIR})
add_custom_target(_clean rm -rf ./CMakeCache.txt && rm -r CMakeFiles)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "**/*.cpp")
foreach(e IN LISTS SOURCES)
    foreach(pat IN LISTS TF_IGNORE_COMPILE)
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
    ${FBXSDK_ROOT}/lib/clang/debug/libfbxsdk.dylib
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARY}
)
add_definitions (
    ${OpenGL_DEFINITIONS}
    ${GLEW_DEFINITIONS}
    ${GLUT_DEFINITIONS}
    ${FBX_BUILD_DEFINES}
    ${FBX_DEPENDENTS_DEFINES}
)
add_executable(${TF_EXECUTABLE} ${SOURCES})

if(APPLE)
    # for libpng
    target_include_directories(
        ${TF_EXECUTABLE}
        PRIVATE
        ${ALUT_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${OPENGL_EGL_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIR}
        ${OPENAL_INCLUDE_DIR}
        #${PNG_INCLUDE_DIR}
        /usr/local/include
        ${FBXSDK_ROOT}/include
        ${FBX_REQUIRED_LIBS_DEPENDENCY}
        ${GLEW_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIR}
    )
else()
    target_include_directories(
        ${TF_EXECUTABLE}
        PRIVATE
        ${ALUT_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${OPENGL_EGL_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIR}
        ${OPENAL_INCLUDE_DIR}
        ${PNG_INCLUDE_DIR}
        ${FBXSDK_ROOT}/include
        ${GLEW_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIR}
    )
endif()

target_link_libraries(
    ${TF_EXECUTABLE}
    PRIVATE
    ${ALUT_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${OPENAL_LIBRARY}
    ${PNG_LIBRARY}
    ${FBXSDK_ROOT}/lib/clang/debug/libfbxsdk.dylib
    ${FBX_REQUIRED_LIBS_DEPENDENCY}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARY}
)