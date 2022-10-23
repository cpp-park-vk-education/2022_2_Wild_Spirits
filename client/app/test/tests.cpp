#include <gmock/gmock.h>

#include <mathlib.h>

TEST(MathLib, Max)
{
	EXPECT_EQ(10, LM::Max(1,  4, 10));
	EXPECT_EQ(15, LM::Max(15, 4, 10));
	EXPECT_EQ(44, LM::Max(1, 44, 10));
	EXPECT_EQ(10, LM::Max(10, 4, 10));
}

TEST(MathLib, Min)
{
	EXPECT_EQ(1,  LM::Min(1,  4,  10));
	EXPECT_EQ(4,  LM::Min(15, 4,  10));
	EXPECT_EQ(10, LM::Min(14, 44, 10));
	EXPECT_EQ(4,  LM::Min(10, 4,  10));
}