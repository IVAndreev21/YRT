cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME "YRT")
project(${PROJECT_NAME} LANGUAGES CXX)
cmake_policy(SET CMP0135 NEW)

include(FetchContent)

# Check the operating system
if(APPLE)
    # macOS-specific settings
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)

        FetchContent_Declare(
        mysql_connector_cpp
        URL "https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-8.2.0-macos13-arm64.tar.gz"
    )
elseif(WIN32)
    # Windows-specific settings
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)

        FetchContent_Declare(
        mysql_connector_cpp
        URL "https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-8.2.0-winx64.zip"
    )

        
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

FetchContent_MakeAvailable(SFML mysql_connector_cpp)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/res" "${CMAKE_SOURCE_DIR}/src")

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-network sfml-audio sfml-network sfml-system sfml-window ${CMAKE_SOURCE_DIR}/build/_deps/mysql_connector_cpp-src/lib64/vs14/mysqlcppconn.dylib)
    include_directories(${SFML}include)
    include_directories(${mysql_connector_cpp_SOURCE_DIR}/include/jdbc)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-network sfml-audio sfml-network sfml-system sfml-window ${CMAKE_SOURCE_DIR}/build/_deps/mysql_connector_cpp-src/lib64/libmysqlcppconn.dylib)
    include_directories(${CMAKE_SOURCE_DIR}/build/_deps/sfml-src/include)
    include_directories(${mysql_connector_cpp_SOURCE_DIR}/include/jdbc)
endif()

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS ${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)