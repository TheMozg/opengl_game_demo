cmake_minimum_required(VERSION 3.0)

project(Game)

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /wd4201")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")
endif()

file(GLOB VENDORS_SOURCES thirdparty/glad/src/glad.c sources/stb_image.c)
file(GLOB PROJECT_HEADERS sources/*.hpp)
file(GLOB PROJECT_SOURCES sources/*.cpp)
file(GLOB PROJECT_SHADERS shaders/*)
file(GLOB PROJECT_TEXTURS textures/*)
file(GLOB PROJECT_MAPS    maps/*)

source_group("Headers"               FILES ${PROJECT_HEADERS})
source_group("Sources"               FILES ${PROJECT_SOURCES})
source_group("Sources (thirdparty)"  FILES ${VENDORS_SOURCES})
source_group("Shaders"               FILES ${PROJECT_SHADERS})
source_group("Textures"              FILES ${PROJECT_TEXTURS})
source_group("Maps"                  FILES ${PROJECT_MAPS})

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_SHADERS}
    ${PROJECT_TEXTURS}
	${PROJECT_MAPS}
    ${VENDORS_SOURCES}
)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC thirdparty/glfw/include)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC thirdparty/glad/include)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC thirdparty/glm)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC thirdparty/stb)

target_link_libraries(${PROJECT_NAME} glfw)

set_target_properties (${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
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
install(DIRECTORY maps DESTINATION .)
