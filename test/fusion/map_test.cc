#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, Map) {
  const fus::result_t<int, std::string> result{42};
  const auto mapped = result.map([](const int value) { return value + 1; });

  ASSERT_TRUE(mapped.has_value());
  ASSERT_EQ(mapped.get(), 43);
}
