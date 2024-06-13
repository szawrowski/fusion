#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, Map) {
  const fusion::Result<int, std::string> result{42};
  const auto mapped = result.Map([](const int value) { return value + 1; });

  ASSERT_TRUE(mapped.HasValue());
  ASSERT_EQ(mapped.Get(), 43);
}
