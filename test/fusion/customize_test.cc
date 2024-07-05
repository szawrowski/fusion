#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, Customize) {
  const cait::result_t<int, std::string> result{42};

  const auto custom_result =
      result.customize([](const cait::result_t<int, std::string>& res) {
        if (res.has_value()) {
          return cait::result_t<int, std::string>{res.get() * 2};
        }
        return cait::result_t<int, std::string>{
            cait::error_t<std::string>{"Custom error"}};
      });

  ASSERT_TRUE(custom_result.has_value());
  ASSERT_EQ(custom_result.get(), 84);
}
