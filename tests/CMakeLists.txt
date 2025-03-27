# Find testing framework (e.g., Google Test)
find_package(GTest REQUIRED)

# Create test executable
add_executable(my_tests ScannerTests.cpp main.cpp)  # Use the correct test file path

# Link with your library and GTest
target_link_libraries(my_tests
  PRIVATE
  tunnl_test
  GTest::GTest
  GTest::Main
)

# Register tests with CTest
add_test(NAME my_tests COMMAND my_tests)

# Optional: Use the gtest_discover_tests function for better test discovery
include(GoogleTest)
gtest_discover_tests(my_tests)