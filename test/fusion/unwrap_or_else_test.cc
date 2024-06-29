#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, UnwrapOrElse) {
  const fus::result_t<int, std::string> result{
      fus::error_t<std::string>{"Error message"}};

  ASSERT_EQ(result.unwrap_or_else([](const std::string&) { return 42; }), 42);
}
