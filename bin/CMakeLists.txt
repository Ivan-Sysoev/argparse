add_executable(argparser main.cpp)

target_link_libraries(argparser PRIVATE argparser_lib)

target_include_directories(argparser PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
