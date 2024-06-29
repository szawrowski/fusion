#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, InspectValue) {
  const fus::result_t<int, std::string> success_result{42};

  success_result.inspect(
      [](const int value) { ASSERT_EQ(value, 42); },
      [](const std::string&) { FAIL() << "Expected success"; });
}

TEST(ResultTest, InspectError) {
  const fus::result_t<int, std::string> error_result{
      fus::error_t<std::string>{"Error message"}};

  error_result.inspect(
      [](int) { FAIL() << "Expected error"; },
      [](const std::string& error) { ASSERT_EQ(error, "Error message"); });
}
