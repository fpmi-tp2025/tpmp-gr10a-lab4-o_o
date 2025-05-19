cmake_minimum_required(VERSION 3.10)
project(HelicopterTransport)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)

add_executable(helicopter_transport
    src/main.cpp
    src/database.cpp
    src/ui.cpp
    src/service.cpp
)

target_link_libraries(helicopter_transport SQLite::SQLite3)