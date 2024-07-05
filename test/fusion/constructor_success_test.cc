#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, ConstructorSuccess) {
  const cait::result_t<int, std::string> result{64};

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result.get(), 64);
}
