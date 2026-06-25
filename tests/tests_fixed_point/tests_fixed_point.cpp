#include <vector>

#include <gtest/gtest.h>

#include "FixedPoint32.h"

namespace Octree
{
    struct FixedPoint32TestCase
    {
        FixedPoint32 fixedPoint;
        fixedInt32 expectedInt;
        fixedFrac32 expectedFrac;
    };

    std::vector<FixedPoint32TestCase> kTestCases {
        {10.10, 10, 10},
        {-11.234, 11, 234}
    };

    class FixedPoint32ParameterizedTestFixture : public ::testing::TestWithParam<FixedPoint32TestCase> {};

    TEST_P(FixedPoint32ParameterizedTestFixture, TestIntegerIsCorrect)
    {
        auto params = GetParam();
        EXPECT_EQ(params.fixedPoint.getInteger(), params.expectedInt);
    }

    INSTANTIATE_TEST_SUITE_P(
        FixedPoint32TestIntegerIsCorrect,
        FixedPoint32ParameterizedTestFixture,
        ::testing::ValuesIn(
            kTestCases
        )
    );
}
