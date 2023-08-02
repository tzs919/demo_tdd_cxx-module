set(headers ${CMAKE_SOURCE_DIR}/src)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(words_repository_test words_repository_test.cc)

target_include_directories(words_repository_test PUBLIC "${headers}")

target_link_libraries(words_repository_test words_repository gtest_main)

add_test(NAME words_repository_test COMMAND words_repository_test)
