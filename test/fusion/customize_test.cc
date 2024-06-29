#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, Customize) {
  const fus::result_t<int, std::string> result{42};

  const auto custom_result =
      result.customize([](const fus::result_t<int, std::string>& res) {
        if (res.has_value()) {
          return fus::result_t<int, std::string>{res.get() * 2};
        }
        return fus::result_t<int, std::string>{
            fus::error_t<std::string>{"Custom error"}};
      });

  ASSERT_TRUE(custom_result.has_value());
  ASSERT_EQ(custom_result.get(), 84);
}
