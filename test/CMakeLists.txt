add_executable(
  property_test
  property_test.cc
)
target_link_libraries(
  property_test
  property
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(property_test)