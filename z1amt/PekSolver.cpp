//
// Created by eric on 06/10/18.
//

#include "PekSolver.h"

mat22 PekSolver::rotz(const mat22 &za, const double betarad) const{
    dcplx
    sum1{za.xx + za.yy},
    sum2{za.xy + za.yx},
    dif1{za.xx - za.yy},
    dif2{za.xy - za.yx};

    double co2{cos(2.* betarad)};
    double si2{sin(2.* betarad)};

    return mat22{
        0.5*(sum1+dif1*co2+sum2*si2),
        0.5*(dif2+sum2*co2-dif1*si2),
        0.5*(-dif2+sum2*co2-dif1*si2),
        0.5*(sum1-dif1*co2-sum2*si2)};
}