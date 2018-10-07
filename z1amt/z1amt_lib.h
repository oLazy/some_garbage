//
// Created by eric on 29/09/18.
//
#pragma once
#ifndef Z1DAMT_Z1AMT_LIB_H
#define Z1DAMT_Z1AMT_LIB_H

#include <mat22.h>
#include <mat33.h>
#include <PekSolver.h>
#include <boost/units/systems/si.hpp>
void cheers();
namespace mt{
    using  namespace boost::units;
    using  namespace boost::units::si;
    const static double pi = 3.14159265358979323846264338327950288;
    const static quantity<permeability> mu0{pi*4.e-7 * henry / meter};
    const static quantity<permittivity> epsilon0{8.854187817e-12 * farad / meter};
}
#endif //Z1DAMT_Z1AMT_LIB_H
