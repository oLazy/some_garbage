//
// Created by eric on 04/10/18.
//

#ifndef Z1DAMT_MAT33_H
#define Z1DAMT_MAT33_H


struct mat33 {
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;

    mat33(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33);

    mat33 operator*(const mat33 & rhs) const;
    mat33 T() const;
    bool operator==(const mat33 &rhs) const;
    bool operator!=(const mat33 &rhs) const;
};


#endif //Z1DAMT_MAT33_H
