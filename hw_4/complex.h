#ifndef COMPLEX
#define COMPLEX

#include <iostream>

//You should include the following methods. - double real(); -- returns the real part of the number. The actual datum storing the real part should be private. - double imaginary(); -- returns the imaginary part of the number. The actual datum storing the imaginary part should be private. - Complex conjugate() -- returns the complex conjugate of the number. In addition, you should overload *, +, and == operators for your class. Note that overloading the == operator will make your class work with Google Test's ASSERT_EQ method. Don't forget to write tests first. Also, ask yourself why we don't need to overload the assigment operation = and why we do not need a destructor for this class. Finally, a hint: You should declare the overloaded binary operators in your .h file and implement them in your .cc file to avoid linker errors when compiling.

class Complex {
    public:
    Complex(double x, double y) : re(x), im(y) {}
    Complex(double a) : re(a), im(0) {};
    Complex() : re(0), im(0) {};

    Complex operator+(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    bool operator==(const Complex& other) const;

    double real() const;
    double imaginary() const;
    Complex conjugate() const;
    double magnitude() const;

    private:
    double re, im;
    
}; 


#endif