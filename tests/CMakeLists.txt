set(headers ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(googletest EXCLUDE_FROM_ALL)

add_executable(words_repository_test words_repository_test.cc)

target_include_directories(words_repository_test PUBLIC "${headers}")

target_link_libraries(words_repository_test words_repository gtest_main)

add_test(NAME words_repository_test COMMAND words_repository_test)
