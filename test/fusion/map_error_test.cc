#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, MapError) {
  const fusion::Result<int, std::string> result{
      fusion::Error<std::string>{"Error message"}};

  const auto mapped = result.MapError(
      [](const std::string& error) { return error + " fixed"; });

  ASSERT_TRUE(mapped.HasError());
  ASSERT_EQ(mapped.GetError(), "Error message fixed");
}
