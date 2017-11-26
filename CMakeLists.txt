cmake_minimum_required(VERSION 3.0)

project(Game)

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")
endif()

include_directories(thirdparty/glfw/include)
include_directories(thirdparty/glad/include)
include_directories(thirdparty/glm)
include_directories(thirdparty/stb)

file(GLOB VENDORS_SOURCES thirdparty/glad/src/glad.c)
file(GLOB PROJECT_HEADERS sources/*.h sources/*.hpp)
file(GLOB PROJECT_SOURCES sources/*.c sources/*.cpp)
file(GLOB PROJECT_SHADERS shaders/*)
file(GLOB PROJECT_TEXTURS textures/*)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_SHADERS}
	${PROJECT_TEXTURS}
    ${VENDORS_SOURCES}
)

target_link_libraries(${PROJECT_NAME} glfw)

set_target_properties (${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
)

set_target_properties (${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin
)

set_target_properties (${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin
)

install(PROGRAMS ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} DESTINATION .)
install(DIRECTORY shaders DESTINATION .)
install(DIRECTORY textures DESTINATION .)