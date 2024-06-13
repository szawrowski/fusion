#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, OrElse) {
  const fusion::Result<int, std::string> result{
      fusion::Error<std::string>{"Error message"}};

  const auto next_result = result.OrElse([](const std::string&) {
    return fusion::Result<int, std::string>{42};
  });

  ASSERT_TRUE(next_result.HasValue());
  ASSERT_EQ(next_result.Get(), 42);
}
