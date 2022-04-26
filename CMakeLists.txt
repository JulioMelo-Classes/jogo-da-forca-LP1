cmake_minimum_required(VERSION 3.5)
project(jogo_da_forca)

set ( CMAKE_CXX_FLAGS "-Wall" )

include_directories( include )

set( APP_NAME "forca" )

add_executable( ${APP_NAME}
                src/main.cpp
                src/Forca.cpp
                src/utils.cpp
                src/tabelas.cpp)

