cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

project(NetworkChat)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

include_directories(include)
file(GLOB project_SRCS src/*.cpp)

add_executable(NetworkChat ${project_SRCS})
target_link_libraries(NetworkChat ${wxWidgets_LIBRARIES})
target_include_directories(NetworkChat PRIVATE ${wxWidgets_INCLUDE_DIRS})
