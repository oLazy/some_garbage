//
// Created by eric on 06/10/18.
//

#ifndef Z1DAMT_PEKSOLVER_H
#define Z1DAMT_PEKSOLVER_H

#include <boost/tuple/tuple.hpp>
#include "UnitsSetup.h"
#include "mat22.h"

class PekSolver {
    int nlmax;
    mat22 rotz(const mat22 &za, const double betarad) const;
    boost::tuple<conductivity, double, angle> cpanis(
            resistivity rop1,
            resistivity rop2,
            resistivity rop3,
            angle strike,
            angle dip,
            angle slant);
public:

};


#endif //Z1DAMT_PEKSOLVER_H
