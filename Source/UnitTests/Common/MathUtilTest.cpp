// Copyright 2014 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include <gtest/gtest.h>

#include "Common/MathUtil.h"

TEST(MathUtil, Clamp)
{
  EXPECT_EQ(1, MathUtil::Clamp(1, 0, 2));
  EXPECT_EQ(1.0, MathUtil::Clamp(1.0, 0.0, 2.0));

  EXPECT_EQ(2, MathUtil::Clamp(4, 0, 2));
  EXPECT_EQ(2.0, MathUtil::Clamp(4.0, 0.0, 2.0));

  EXPECT_EQ(0, MathUtil::Clamp(-1, 0, 2));
  EXPECT_EQ(0.0, MathUtil::Clamp(-1.0, 0.0, 2.0));
}

TEST(MathUtil, IntLog2)
{
  EXPECT_EQ(0, IntLog2(1));
  EXPECT_EQ(1, IntLog2(2));
  EXPECT_EQ(2, IntLog2(4));
  EXPECT_EQ(3, IntLog2(8));
  EXPECT_EQ(63, IntLog2(0x8000000000000000ull));

  // Rounding behavior.
  EXPECT_EQ(3, IntLog2(15));
  EXPECT_EQ(63, IntLog2(0xFFFFFFFFFFFFFFFFull));
}
