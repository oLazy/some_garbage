//
// Created by eric on 06/10/18.
//

#ifndef Z1DAMT_PEKSOLVER_H
#define Z1DAMT_PEKSOLVER_H


#include "mat22.h"

class PekSolver {
    int nlmax;
    mat22 rotz(const mat22 &za, const double betarad) const;

public:
    mat22 z1anis(double h[], double al[], double at[], double blt[], int nl, double per[]) const;
};


#endif //Z1DAMT_PEKSOLVER_H
