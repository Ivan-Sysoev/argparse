add_executable(app main.cpp)

set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/app"
)

target_link_libraries(app PRIVATE argparser)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
