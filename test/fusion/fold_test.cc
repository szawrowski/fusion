#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, FoldValue) {
  const fusion::Result<int, std::string> result{42};

  const auto folded = result.Fold(
      10, [](const int acc, const int value) { return acc + value; });

  ASSERT_EQ(folded, 52);
}

TEST(ResultTest, FoldError) {
  const fusion::Result<int, std::string> result{
      fusion::Error<std::string>{"Error message"}};

  const auto folded = result.Fold(
      10, [](const int acc, const int value) { return acc + value; });

  ASSERT_EQ(folded, 10);  // Initial value should remain unchanged
}
