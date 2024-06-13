#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, Customize) {
  const fusion::Result<int, std::string> result{42};

  const auto custom_result =
      result.Customize([](const fusion::Result<int, std::string>& res) {
        if (res.HasValue()) {
          return fusion::Result<int, std::string>{res.Get() * 2};
        }
        return fusion::Result<int, std::string>{
            fusion::Error<std::string>{"Custom error"}};
      });

  ASSERT_TRUE(custom_result.HasValue());
  ASSERT_EQ(custom_result.Get(), 84);
}
