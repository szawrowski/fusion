#include <gtest/gtest.h>

#include "fusion/fusion.h"

TEST(ResultTest, ConstructorSuccess) {
  const fusion::Result<int, std::string> result{64};

  ASSERT_TRUE(result.HasValue());
  ASSERT_EQ(result.Get(), 64);
}
