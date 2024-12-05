
add_executable(pd main.cpp)

add_library(lexer lexer.cpp include/lexer.hpp)
target_include_directories(lexer PUBLIC include)
add_library(parser parser.cpp include/parser.hpp)
target_include_directories(parser PUBLIC include)
target_link_libraries(pd PUBLIC lexer)
target_link_libraries(pd PUBLIC parser)