cmake_minimum_required(VERSION 3.5)
project(rail-ticket-system_test CXX)

add_executable(${PROJECT_NAME} test_main.cc ../client/api/client.cc)

find_path(CPP_HTTPLIB_INCLUDE_DIRS "httplib.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS})

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# target_link_libraries(${PROJECT_NAME}_test PRIVATE drogon)
#
# and comment out the following lines
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

ParseAndAddDrogonTests(${PROJECT_NAME})
