#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, OnError) {
  const fusion::Result<int, std::string> result{
      fusion::Error<std::string>{"Error message"}};

  bool error_handled = false;

  result.OnError([&error_handled](const std::string& error) {
    error_handled = true;
    ASSERT_EQ(error, "Error message");
  });

  ASSERT_TRUE(error_handled);
}
