#include "complex.h"
#include <math.h>

Complex Complex::operator+(const Complex& other) const {
    return Complex(re + other.re, im + other.im);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(re * other.re - im * other.im,
                   re * other.im + im * other.re);
}

bool Complex::operator==(const Complex& other) const {
    return re == other.re && im == other.im;
}

double Complex::magnitude() const {
    return sqrt(re * re + im * im);
}

double Complex::real() const {
    return re;
}

double Complex::imaginary() const {
    return im;
}

Complex Complex::conjugate() const {
    return Complex(re, -im);
}