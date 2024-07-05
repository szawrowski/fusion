#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, UnwrapOrElse) {
  const cait::result_t<int, std::string> result{
      cait::error_t<std::string>{"Error message"}};

  ASSERT_EQ(result.unwrap_or_else([](const std::string&) { return 42; }), 42);
}
