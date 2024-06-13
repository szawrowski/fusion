#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, UnwrapOrElse) {
  const fusion::Result<int, std::string> result{
      fusion::Error<std::string>{"Error message"}};

  ASSERT_EQ(result.UnwrapOrElse([](const std::string&) { return 42; }), 42);
}
