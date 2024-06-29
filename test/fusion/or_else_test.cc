#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, OrElse) {
  const fus::result_t<int, std::string> result{
      fus::error_t<std::string>{"Error message"}};

  const auto next_result = result.or_else(
      [](const std::string&) { return fus::result_t<int, std::string>{42}; });

  ASSERT_TRUE(next_result.has_value());
  ASSERT_EQ(next_result.get(), 42);
}
