#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, ConstructorError) {
  const cait::result_t<int, std::string> result{
      cait::error_t<std::string>{"Error message"}};

  ASSERT_TRUE(result.has_error());
  ASSERT_EQ(result.get_error(), "Error message");
}
