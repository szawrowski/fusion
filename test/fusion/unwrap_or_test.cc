#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, UnwrapOr) {
  const fus::result_t<int, std::string> result{
      fus::error_t<std::string>{"Error message"}};

  ASSERT_EQ(result.unwrap_or(42), 42);
}
