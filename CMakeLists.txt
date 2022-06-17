cmake_minimum_required(VERSION 3.21)
project(ft_containers)

set(CMAKE_CXX_STANDARD 14)

add_executable(ft_containers main.cpp vector.hpp random_access_iterator.hpp iterator_traits.hpp utils.hpp)
