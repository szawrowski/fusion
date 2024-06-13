#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, AndThen) {
  const fusion::Result<int, std::string> result{42};

  const auto next_result = result.AndThen([](const int value) {
    return fusion::Result<int, std::string>{value * 2};
  });

  ASSERT_TRUE(next_result.HasValue());
  ASSERT_EQ(next_result.Get(), 84);
}
