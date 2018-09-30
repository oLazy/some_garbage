//
// Created by eric on 29/09/18.
//

#include "mat22.h"

mat22 mat22::operator*(mat22 const &rhs) const {
    return mat22{{xx*rhs.xx + xy*rhs.yx},
                 {xx*rhs.xy + xy*rhs.yy},
                 {yx*rhs.xx + yy*rhs.yx},
                 {yx*rhs.xy + yy*rhs.yy}};
}

std::complex<double> mat22::det() const {

    return this->xx * this->yy - this->xy * this->yx;
}

mat22::mat22(const std::complex<double> &xx, const std::complex<double> &xy, const std::complex<double> &yx,
             const std::complex<double> &yy) : xx(xx), xy(xy), yx(yx), yy(yy) {}

std::ostream &operator<<(std::ostream &os, const mat22 &mat221) {
    os << "xx: " << mat221.xx << " xy: " << mat221.xy << std::endl << "yx: " << mat221.yx << " yy: " << mat221.yy;
    return os;
}

mat22 mat22::operator-(mat22 const &rhs) const {
    return mat22{{xx-rhs.xx},
                 {xy-rhs.xy},
                 {yx-rhs.yx},
                 {yy-rhs.yy}};
}
