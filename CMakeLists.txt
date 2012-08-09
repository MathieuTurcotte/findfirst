# Copyright (C) 2011 Mathieu Turcotte (mathieuturcotte.ca)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see http://www.gnu.org/licenses/.

# Use "cmake -D CMAKE_BUILD_TYPE=Debug" to build in debug mode.
# Use "cmake -D CMAKE_BUILD_TYPE=Release" to build in release mode.

cmake_minimum_required(VERSION 2.6.4)
project(findfirst C)

if (${CMAKE_COMPILER_IS_GNUCC})
    add_definitions(-Wall -Wextra)
    add_definitions(-pedantic)
endif()

add_executable(test_spec test_spec.c spec.c)

if (${WIN32})
    add_executable(findfirst main.c)
    add_executable(test_findfirst test_findfirst.c)
else()
    add_executable(findfirst main.c spec.c findfirst.c)
    add_executable(test_findfirst test_findfirst.c spec.c findfirst.c)
endif()
