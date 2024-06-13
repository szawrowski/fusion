#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, ConstructorError) {
  const fusion::Result<int, std::string> result{
      fusion::Error<std::string>{"Error message"}};

  ASSERT_TRUE(result.HasError());
  ASSERT_EQ(result.GetError(), "Error message");
}
