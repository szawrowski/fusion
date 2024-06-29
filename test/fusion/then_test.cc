#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, Then) {
  const fus::result_t<int, std::string> result{42};

  const auto next_result = result.then([](const int value) {
    return fus::result_t<int, std::string>{value * 2};
  });

  ASSERT_TRUE(next_result.has_value());
  ASSERT_EQ(next_result.get(), 84);
}
