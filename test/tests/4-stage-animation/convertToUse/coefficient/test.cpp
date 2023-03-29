#include <gtest/gtest.h>
#include "ui/animation/convertToUse/coefficient/convertToUseCoefficient.hpp"

TEST(ConvertToUseCoefficient, operatop){
	ui::ConvertToUseCoefficient<float> coefficient1{0},
									   coefficient2{0.5},
									   coefficient3{1},
									   coefficient4{11};

	ASSERT_EQ(coefficient1(7), 0);
	ASSERT_EQ(coefficient2(7), 3.5);
	ASSERT_EQ(coefficient3(7), 7);
	ASSERT_EQ(coefficient4(7), 77);
}