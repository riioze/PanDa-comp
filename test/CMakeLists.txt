include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


add_executable(test_lexer LexerTest.cpp)
target_link_libraries(test_lexer PRIVATE GTest::GTest lexer)
add_test(test_lexer_gtests test_lexer)

add_executable(test_parser ParserTest.cpp)
target_link_libraries(test_parser PRIVATE GTest::GTest parser)
add_test(test_parser_gtests test_parser)