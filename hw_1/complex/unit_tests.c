#include "complex.h"
#include "gtest/gtest.h"

namespace
{

    TEST(ComplexNumbers, Add)
    {
        Complex a = {3.0, 2.0};
        Complex b = {1.5, -1.0};
        Complex result = add(a, b);

        EXPECT_DOUBLE_EQ(result.real, 4.5);
        EXPECT_DOUBLE_EQ(result.im, 1.0);
    }

    TEST(ComplexNumbers, Negate)
    {
        Complex a = {3.0, 2.0};
        Complex result = negate(a);

        EXPECT_DOUBLE_EQ(result.real, -3.0);
        EXPECT_DOUBLE_EQ(result.im, -2.0);
    }

    TEST(ComplexNumbers, Multiply)
    {
        Complex a = {3.0, 2.0};
        Complex b = {1.5, -1.0};
        Complex result = multiply(a, b);

        EXPECT_DOUBLE_EQ(result.real, 6.5);
        EXPECT_DOUBLE_EQ(result.im, 0);
    }

    TEST(ComplexNumbers, Magnitude)
    {
        Complex a = {3.0, 4.0};
        double result = magnitude(a);

        EXPECT_DOUBLE_EQ(result, 5.0); //  3^2 + 4^2 = 5^2
    }

} // namespace
