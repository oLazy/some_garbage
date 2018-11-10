//
// Created by eric on 06/10/18.
//

#ifndef Z1DAMT_PEKSOLVER_H
#define Z1DAMT_PEKSOLVER_H

#include <boost/tuple/tuple.hpp>
#include "UnitsSetup.h"
#include "mat22.h"
#include <set>
//#include "d1node.h"
class d1node;

class PekSolver {
    int max_n_layers{32}; // tmp construct with 32 layers max
public:
    mat22 rotz(const mat22 &za, const double betarad) const;
    impedance_tensor rotz(
            const impedance_tensor &za,
            const angle &beta) const;
    boost::tuple<conductivity, double, angle> cpanis(
            resistivity rop1,
            resistivity rop2,
            resistivity rop3,
            angle strike,
            angle dip,
            angle slant);
    void operator()(const std::set<d1node> &m, const int) const;

};


#endif //Z1DAMT_PEKSOLVER_H
