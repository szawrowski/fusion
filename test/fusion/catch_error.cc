#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, CatchError) {
  const fus::result_t<int, std::string> result{
      fus::error_t<std::string>{"Error message"}};

  const auto caught_result = result.catch_error([](const std::string& error) {
    return fus::result_t<int, std::string>{static_cast<int>(error.length())};
  });

  ASSERT_TRUE(caught_result.has_value());
  ASSERT_EQ(caught_result.get(), 13);
}
