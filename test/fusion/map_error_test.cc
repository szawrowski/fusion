#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, MapError) {
  const fus::result_t<int, std::string> result{
      fus::error_t<std::string>{"Error message"}};

  const auto mapped = result.map_error(
      [](const std::string& error) { return error + " fixed"; });

  ASSERT_TRUE(mapped.has_error());
  ASSERT_EQ(mapped.get_error(), "Error message fixed");
}
