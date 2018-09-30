//
// Created by eric on 29/09/18.
//

#ifndef Z1DAMT_MAT22_H
#define Z1DAMT_MAT22_H

#include <complex>
#include <ostream>

typedef std::complex<double> dcplx;
struct mat22 {
    std::complex<double> xx, xy, yx, yy;

    mat22(const std::complex<double> &xx, const std::complex<double> &xy, const std::complex<double> &yx,
          const std::complex<double> &yy);

    mat22 operator*(mat22 const & rhs) const;
    std::complex<double> det() const ;

    friend std::ostream &operator<<(std::ostream &os, const mat22 &mat221);
};


#endif //Z1DAMT_MAT22_H
