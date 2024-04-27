add_executable(
  property_test
  property_test.cc
)
target_link_libraries(
  property_test
  property
  GTest::gtest_main
)

add_executable(
  user_test
  user_test.cc
)
target_link_libraries(
  user_test
  user
  GTest::gtest_main
  gmock
)

add_executable(
  cryptography_test
  cryptography_test.cc
)
target_link_libraries(
  cryptography_test
  cryptography
  GTest::gtest_main
  gmock
)

add_executable(
  person_test
  person_test.cc
)
target_link_libraries(
  person_test
  person
  GTest::gtest_main
)

add_executable(
  purchase_test
  purchase_test.cc
)
target_link_libraries(
  purchase_test
  purchase
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(property_test)
gtest_discover_tests(user_test)
gtest_discover_tests(cryptography_test)
gtest_discover_tests(person_test)
gtest_discover_tests(purchase_test)