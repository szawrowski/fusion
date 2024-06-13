#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, UnwrapOr) {
  const fusion::Result<int, std::string> result{
      fusion::Error<std::string>{"Error message"}};

  ASSERT_EQ(result.UnwrapOr(42), 42);
}
