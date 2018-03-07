cmake_minimum_required(VERSION 2.7)
project(controller)

set(CMAKE_CXX_STANDARD 11)

add_library(m4m_mbus
        Mbus.cpp Mbus.hpp
        exceptions.cpp exceptions.hpp
        )
target_link_libraries(m4m_mbus mbus)
