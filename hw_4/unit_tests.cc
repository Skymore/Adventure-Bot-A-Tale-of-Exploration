#include <assert.h>
#include <iostream>
#include "gtest/gtest.h"
#include "typed_array.h"
#include "complex.h"
#include "point.h"

namespace {

TEST(TypedArray, Construction) {
    TypedArray<Point> b;
    b.set(0, Point(1, 2, 3));
    b.set(1, Point(2, 3, 4));
    b.set(20, Point(3, 4, 5));
    EXPECT_EQ(b.get(0).x, 1);
    EXPECT_EQ(b.get(1).y, 3);
    EXPECT_EQ(b.get(20).z, 5);
}

TEST(TypedArray, Defaults) {
    TypedArray<Point> x;
    Point& y = x.get(3);
    std::cout << x << "\n";
    EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
}

TEST(TypedArray, Matrix) {
    TypedArray<TypedArray<double>> m;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m.get(i).set(j, 3 * i + j);
        }
    }

    // std::cout << m << "\n";

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_DOUBLE_EQ(m.get(i).get(j), 3 * i + j);
        }
    }
}

TEST(TypedArray, CopyElementsInSet1) {
    TypedArray<Point> b;
    Point p(1, 2, 3);
    b.set(0, p);
    p.x = 4;
    EXPECT_DOUBLE_EQ(b.get(0).x, 1);
}

TEST(TypedArray, CopyElementsInSet2) {
    TypedArray<TypedArray<double>> m;
    TypedArray<double> x;
    x.set(0, 0);
    m.set(0, x);
    x.set(0, -1);
    EXPECT_DOUBLE_EQ(m.get(0).get(0), 0.0);  // If set didn't make a copy
                                             // then we would expect m[0][0]
                                             // to be x[0], which we changed
                                             // to -1.
}

TEST(TypedArray, Push) {
    TypedArray<Point> b;
    b.push(Point(1, 2, 3));
    b.push(Point(2, 3, 4));
    b.push(Point(3, 4, 5));
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.get(0).x, 1);
    EXPECT_EQ(b.get(1).y, 3);
    EXPECT_EQ(b.get(2).z, 5);
}

TEST(TypedArray, Pop) {
    TypedArray<Point> b;
    b.push(Point(1, 2, 3));
    b.push(Point(2, 3, 4));
    b.push(Point(3, 4, 5));
    Point x = b.pop();
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(x.z, 5);
}

TEST(TypedArray, PushFront) {
    TypedArray<Point> b;
    b.push_front(Point(1, 2, 3));
    b.push_front(Point(2, 3, 4));
    b.push_front(Point(3, 4, 5));
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.get(0).x, 3);
    EXPECT_EQ(b.get(1).y, 3);
    EXPECT_EQ(b.get(2).z, 3);
}

TEST(TypedArray, PopFront) {
    TypedArray<Point> b;
    b.push_front(Point(1, 2, 3));
    b.push_front(Point(2, 3, 4));
    b.push_front(Point(3, 4, 5));
    Point p = b.pop_front();
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(p.z, 5);
    EXPECT_EQ(p.x, 3);
}

TEST(TypedArray, Concat) {
    TypedArray<int> a;
    a.set(0, 0);
    a.set(1, 1);
    TypedArray<int> b = a.concat(a).concat(a);  // yields a new array [0,1,0,1,0,1]
    EXPECT_EQ(b.size(), 6);
    EXPECT_EQ(b.get(0), 0);
    EXPECT_EQ(b.get(1), 1);
    EXPECT_EQ(b.get(2), 0);
    EXPECT_EQ(b.get(3), 1);
    EXPECT_EQ(b.get(4), 0);
    EXPECT_EQ(b.get(5), 1);
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a.get(0), 0);
    EXPECT_EQ(a.get(1), 1);
}

TEST(TypedArray, Reverse) {
    TypedArray<int> a;
    a.set(0, 0);
    a.set(1, 1);
    TypedArray<int> b = a.reverse(); 
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b.get(0), 1);
    EXPECT_EQ(b.get(1), 0);
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a.get(0), 1);
    EXPECT_EQ(a.get(1), 0);
}

TEST(TypedArray, Addition) {
    TypedArray<int> a;
    a.set(0, 0);
    a.set(1, 1);
    TypedArray<int> b = a + a + a;  // yields a new array [0,1,0,1,0,1]
    EXPECT_EQ(b.size(), 6);
    EXPECT_EQ(b.get(0), 0);
    EXPECT_EQ(b.get(1), 1);
    EXPECT_EQ(b.get(2), 0);
    EXPECT_EQ(b.get(3), 1);
    EXPECT_EQ(b.get(4), 0);
    EXPECT_EQ(b.get(5), 1);
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a.get(0), 0);
    EXPECT_EQ(a.get(1), 1);
}

TEST(Complex, Construction) {
    Complex a(1, 2);
    EXPECT_DOUBLE_EQ(a.real(), 1);
    EXPECT_DOUBLE_EQ(a.imaginary(), 2);
}

TEST(Complex, Conjugate) {
    Complex a(1, 2);
    Complex b = a.conjugate();
    EXPECT_DOUBLE_EQ(b.real(), 1);
    EXPECT_DOUBLE_EQ(b.imaginary(), -2);
}

TEST(Complex, Magnitude) {
    Complex a(3, 4);
    EXPECT_DOUBLE_EQ(a.magnitude(), 5);
}

TEST(Complex, Addition) {
    Complex a(1, 2);
    Complex b(3, 4);
    Complex c = a + b;
    EXPECT_DOUBLE_EQ(c.real(), 4);
    EXPECT_DOUBLE_EQ(c.imaginary(), 6);
}

TEST(Complex, Multiplication) {
    Complex a(1, 2);
    Complex b(3, 4);
    Complex c = a * b;
    EXPECT_DOUBLE_EQ(c.real(), -5);
    EXPECT_DOUBLE_EQ(c.imaginary(), 10);
}

TEST(Complex, Equality) {
    Complex a(1, 2);
    Complex b(1, 2);
    Complex c(3, 4);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}


}  // namespace