//
// Created by eric on 04/10/18.
//

#include "mat33.h"

mat33::mat33(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
        : a11(a11), a12(a12), a13(a13), a21(a21), a22(a22), a23(a23), a31(a31), a32(a32), a33(a33) {}

bool mat33::operator==(const mat33 &rhs) const {
    return a11 == rhs.a11 &&
           a12 == rhs.a12 &&
           a13 == rhs.a13 &&
           a21 == rhs.a21 &&
           a22 == rhs.a22 &&
           a23 == rhs.a23 &&
           a31 == rhs.a31 &&
           a32 == rhs.a32 &&
           a33 == rhs.a33;
}

bool mat33::operator!=(const mat33 &rhs) const {
    return !(rhs == *this);
}

mat33 mat33::T() const {
    return mat33(a11, a21, a31, a12, a22, a32, a13, a23, a33);
}

mat33 mat33::operator*(const mat33 &rhs) const {
    return mat33(a11*rhs.a11+ a12*rhs.a21 + a13*rhs.a31,
                 a11*rhs.a12+ a12*rhs.a22 + a13*rhs.a32,
                 a11*rhs.a13+ a12*rhs.a23 + a13*rhs.a33,
                 a21*rhs.a11+ a22*rhs.a21 + a23*rhs.a31,
                 a21*rhs.a12+ a22*rhs.a22 + a23*rhs.a32,
                 a21*rhs.a13+ a22*rhs.a23 + a23*rhs.a33,
                 a31*rhs.a11+ a32*rhs.a21 + a33*rhs.a31,
                 a31*rhs.a12+ a32*rhs.a22 + a33*rhs.a32,
                 a31*rhs.a13+ a32*rhs.a23 + a33*rhs.a33);
}

double mat33::det() const {
    return (a11*(a22*a33 - a23*a32) -
            a12*(a21*a33 - a23*a31) +
            a13*(a21*a32 - a22*a31));
}

std::ostream &operator<<(std::ostream &os, const mat33 &mat331) {
    os << "a11: " << mat331.a11 << " a12: " << mat331.a12 << " a13: " << mat331.a13 << " a21: " << mat331.a21
       << " a22: " << mat331.a22 << " a23: " << mat331.a23 << " a31: " << mat331.a31 << " a32: " << mat331.a32
       << " a33: " << mat331.a33;
    return os;
}
