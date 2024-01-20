#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! Brief Complex number struct
 *
 *  A complex number is a number that can be expressed in the form a + bi,
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two complex numbers together
 *  \param a The first summand
 *  \param b The second summand
 */
Complex add(Complex a, Complex b);

/*! Negate a complex number
 *  \param a The number to negate
 */
Complex negate(Complex a);

/*! Multiply two complex numbers together
 *  \param a The first factor
 *  \param b The second factor
 */
Complex multiply(Complex a, Complex b);

/*! Magnitude of a complex number
 *  \param a The number to find the magnitude of
 */
double magnitude(Complex a);
// Functions that return a scalar should return double.

/*! Print a complex number
 *  \param c The number to print
 */
void printComplex(Complex c);
// Print a complex number in the form a + bi

#endif