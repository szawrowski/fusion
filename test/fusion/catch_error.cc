#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, CatchError) {
  const fusion::Result<int, std::string> result{
      fusion::Error<std::string>{"Error message"}};

  const auto caught_result = result.CatchError([](const std::string& error) {
    return fusion::Result<int, std::string>{static_cast<int>(error.length())};
  });

  ASSERT_TRUE(caught_result.HasValue());
  ASSERT_EQ(caught_result.Get(), 13);  // Length of "Error message"
}
