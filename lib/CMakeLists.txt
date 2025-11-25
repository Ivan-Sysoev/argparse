add_library(argparser_lib STATIC
    argparser.cpp
    argparser.h
)

target_include_directories(argparser_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
