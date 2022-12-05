cmake_minimum_required(VERSION 3.5)
project(rail-client CXX)

add_executable(${PROJECT_NAME} main.cc)

aux_source_directory(api API_SRC)

target_sources(${PROJECT_NAME}
               PRIVATE
               ${API_SRC})