cmake_minimum_required(VERSION 2.7)
project(m4m_controller)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(mbus)

add_executable(m4m_controller
        main.cpp
)
set_target_properties(m4m_controller PROPERTIES LINK_FLAGS "-static")
target_link_libraries(m4m_controller m4m_mbus)
