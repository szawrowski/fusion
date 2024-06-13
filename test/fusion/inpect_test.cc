#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, InspectValue) {
  const fusion::Result<int, std::string> success_result{42};

  success_result.Inspect(
      [](const int value) { ASSERT_EQ(value, 42); },
      [](const std::string&) { FAIL() << "Expected success"; });
}

TEST(ResultTest, InspectError) {
  const fusion::Result<int, std::string> error_result{
      fusion::Error<std::string>{"Error message"}};

  error_result.Inspect(
      [](int) { FAIL() << "Expected error"; },
      [](const std::string& error) { ASSERT_EQ(error, "Error message"); });
}
