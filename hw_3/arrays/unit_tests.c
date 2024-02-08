#include <float.h> /* defines DBL_EPSILON */
#include <math.h>
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

/**
 * @file example_test.cpp
 * @brief Test suite for DynamicArray class functionality.
 * 
 * This suite tests the creation, manipulation, and destruction of dynamic arrays
 * using the DynamicArray class. It covers basic operations such as push, pop,
 * and access, as well as advanced operations like map, min, max, and statistical
 * functions.
 */

namespace {

/**
 * @brief Test creation and destruction of a dynamic array.
 */
TEST(DynamicArray, CreateAndDestroy) {
    DynamicArray* a = DynamicArray_new();
    DynamicArray_destroy(a);
}

/**
 * @brief Test for expected failures when popping from an empty dynamic array.
 */
TEST(DynamicArray, DeathTests) {
    DynamicArray* a = DynamicArray_new();
    ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
    ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
    DynamicArray_destroy(a);
    ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
}

/**
 * @brief Test setting and retrieving small index values.
 */
TEST(DynamicArray, SmallIndex) {
    DynamicArray* da = DynamicArray_new();
    ASSERT_EQ(DynamicArray_size(da), 0);
    DynamicArray_set(da, 0, -X);
    DynamicArray_set(da, 3, X);
    ASSERT_EQ(DynamicArray_size(da), 4);
    ASSERT_EQ(DynamicArray_get(da, 0), -X);
    ASSERT_EQ(DynamicArray_get(da, 3), X);
    DynamicArray_destroy(da);
}

/**
 * @brief Test setting and retrieving a value at a large index.
 */
TEST(DynamicArray, BigIndex) {
    DynamicArray* da = DynamicArray_new();
    DynamicArray_set(da, 8, X);
    ASSERT_EQ(DynamicArray_get(da, 8), X);
    DynamicArray_destroy(da);
}

/**
 * @brief Test setting values at very large indices.
 */
TEST(DynamicArray, ReallyBig) {
    DynamicArray* da = DynamicArray_new();
    DynamicArray_set(da, 400, X);
    DynamicArray_set(da, 200, X / 2);
    ASSERT_EQ(DynamicArray_get(da, 200), X / 2);
    ASSERT_EQ(DynamicArray_get(da, 400), X);
    DynamicArray_destroy(da);
}

/**
 * @brief Test pushing values to the end of the dynamic array.
 */
TEST(DynamicArray, Push) {
    DynamicArray* da = DynamicArray_new();
    double x = 0;
    while (x < 10) {
        DynamicArray_push(da, x);
        x += 0.25;
    }
    ASSERT_EQ(DynamicArray_size(da), 40);
    printf("Push test Intermediate Result: %s\n", DynamicArray_to_string(da));
    while (DynamicArray_size(da) > 0) {
        DynamicArray_pop(da);
    }
    ASSERT_EQ(DynamicArray_size(da), 0);
    DynamicArray_destroy(da);
}

/**
 * @brief Test pushing values to the front of the dynamic array.
 */
TEST(DynamicArray, PushFront) {
    DynamicArray* da = DynamicArray_new();
    double x = 0;
    while (x < 10) {
        DynamicArray_push_front(da, x);
        x += 0.25;
    }
    ASSERT_EQ(DynamicArray_size(da), 40);
    while (DynamicArray_size(da) > 0) {
        DynamicArray_pop_front(da);
    }
    ASSERT_EQ(DynamicArray_size(da), 0);
    DynamicArray_destroy(da);
}

/**
 * @brief Test converting the dynamic array to a string representation.
 */
TEST(DynamicArray, ToString) {
    DynamicArray* da = DynamicArray_new();
    double x = 1.0;
    while (x <= 5) {
        DynamicArray_push(da, x);
        x += 1.0;
    }
    char* str = DynamicArray_to_string(da);
    printf("ToString Example: %s\n", str);
    ASSERT_STREQ(str, "[1.00000,2.00000,3.00000,4.00000,5.00000]");
    DynamicArray_destroy(da);
    free(str);
}

/**
 * @brief Test popping values from the end of the dynamic array.
 */
TEST(DynamicArray, Pop) {
    DynamicArray* da = DynamicArray_new();
    double x;
    DynamicArray_push(da, X);
    DynamicArray_push(da, X);
    x = DynamicArray_pop(da);
    ASSERT_EQ(DynamicArray_size(da), 1);
    ASSERT_EQ(x, X);
    ASSERT_EQ(DynamicArray_get(da, 1), 0.0);
    DynamicArray_destroy(da);
}

/**
 * @brief Test applying a function to each element of the dynamic array.
 */
TEST(DynamicArray, Map) {
    DynamicArray *t = DynamicArray_new(), *y;
    double s = 0.0;
    for (int i = 0; i < 628; i++) {
        DynamicArray_set(t, i, s);
        s = s + 0.1;
    }
    y = DynamicArray_map(t, sin);
    for (int i = 0; i < DynamicArray_size(t); i++) {
        ASSERT_NEAR(DynamicArray_get(y, i), sin(0.1 * i), 0.0001);
    }
    DynamicArray_destroy(t);
    DynamicArray_destroy(y);
}

/**
 * @brief Test finding the minimum value in the dynamic array.
 */
TEST(DynamicArray, Min) {
    DynamicArray* da = DynamicArray_range(0, 10, 1);
    ASSERT_EQ(DynamicArray_min(da), 0);
    DynamicArray_destroy(da);
}

/**
 * @brief Test finding the maximum value in the dynamic array.
 */
TEST(DynamicArray, Max) {
    DynamicArray* da = DynamicArray_range(0, 10, 1);
    ASSERT_EQ(DynamicArray_max(da), 9);
    DynamicArray_destroy(da);
}

/**
 * @brief Test calculating the mean of values in the dynamic array.
 */
TEST(DynamicArray, Mean) {
    DynamicArray* da = DynamicArray_range(1, 5, 1);
    ASSERT_DOUBLE_EQ(DynamicArray_mean(da), 2.5);
    DynamicArray_destroy(da);
}

/**
 * @brief Test calculating the sum of values in the dynamic array.
 */
TEST(DynamicArray, Sum) {
    DynamicArray* da = DynamicArray_range(1, 5, 1);
    ASSERT_EQ(DynamicArray_sum(da), 10);
    DynamicArray_destroy(da);
}

/**
 * @brief Test calculating the median of values in the dynamic array.
 */
TEST(DynamicArray, Median) {
    DynamicArray* da = DynamicArray_range(1, 6, 1);
    ASSERT_DOUBLE_EQ(DynamicArray_median(da), 3);
    DynamicArray* da_odd = DynamicArray_range(1, 5, 1);
    ASSERT_DOUBLE_EQ(DynamicArray_median(da_odd), 2.5);
    DynamicArray_destroy(da);
    DynamicArray_destroy(da_odd);
}

/**
 * @brief Test extracting a subset of values from the dynamic array.
 */
TEST(DynamicArray, Take) {
    DynamicArray* da = DynamicArray_range(1, 6, 1);
    DynamicArray* da_take = DynamicArray_take(da, 3);
    ASSERT_EQ(DynamicArray_get(da_take, 0), 1);
    ASSERT_EQ(DynamicArray_get(da_take, 2), 3);
    DynamicArray_destroy(da);
    DynamicArray_destroy(da_take);
}

/**
 * @brief Test concatenating two dynamic arrays into one.
 */
TEST(DynamicArray, Concat) {
    DynamicArray* da1 = DynamicArray_range(1, 4, 1);
    DynamicArray* da2 = DynamicArray_range(4, 6, 1);
    DynamicArray* da_concat = DynamicArray_concat(da1, da2);
    ASSERT_EQ(DynamicArray_get(da_concat, 0), 1);
    ASSERT_EQ(DynamicArray_get(da_concat, 4), 5);
    DynamicArray_destroy(da1);
    DynamicArray_destroy(da2);
    DynamicArray_destroy(da_concat);
}

/**
 * @brief Test creating a dynamic array with a range of values.
 */
TEST(DynamicArray, Range) {
    DynamicArray* da = DynamicArray_range(1, 4, 1);
    ASSERT_EQ(DynamicArray_size(da), 3);
    ASSERT_EQ(DynamicArray_get(da, 0), 1);
    ASSERT_EQ(DynamicArray_get(da, 2), 3);
    DynamicArray_destroy(da);
}

/**
 * @brief Test copying a dynamic array.
 */
TEST(DynamicArray, Copy) {
    DynamicArray* da = DynamicArray_range(1, 4, 1);
    DynamicArray* da_copy = DynamicArray_copy(da);
    ASSERT_EQ(DynamicArray_get(da_copy, 0), 1);
    DynamicArray_destroy(da);
    DynamicArray_destroy(da_copy);
}

/**
 * @brief Test retrieving the first and last value of the dynamic array.
 */
TEST(DynamicArray, FirstLast) {
    DynamicArray* da = DynamicArray_range(1, 4, 1);
    ASSERT_EQ(DynamicArray_first(da), 1);
    ASSERT_EQ(DynamicArray_last(da), 3);
    DynamicArray_destroy(da);
}

/**
 * @brief Test managing multiple dynamic arrays and their validity.
 */
TEST(DynamicArray, ArrayManagement) {
    DynamicArray_destroy_all();
    DynamicArray* a = DynamicArray_range(0, 1, 0.1);
    DynamicArray* b = DynamicArray_range(1.1, 2, 0.1);
    DynamicArray* c = DynamicArray_concat(a, b);
    ASSERT_EQ(DynamicArray_is_valid(a), 1);
    ASSERT_EQ(DynamicArray_num_arrays(), 3);
    DynamicArray_destroy_all();
    ASSERT_EQ(DynamicArray_is_valid(a), 0);
    ASSERT_EQ(DynamicArray_num_arrays(), 0);
    free(a);
    free(b);
    free(c);
}

}  // namespace
