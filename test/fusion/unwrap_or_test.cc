#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, UnwrapOr) {
  const cait::result_t<int, std::string> result{
      cait::error_t<std::string>{"Error message"}};

  ASSERT_EQ(result.unwrap_or(42), 42);
}
