#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, OrElse) {
  const cait::result_t<int, std::string> result{
      cait::error_t<std::string>{"Error message"}};

  const auto next_result = result.or_else(
      [](const std::string&) { return cait::result_t<int, std::string>{42}; });

  ASSERT_TRUE(next_result.has_value());
  ASSERT_EQ(next_result.get(), 42);
}
