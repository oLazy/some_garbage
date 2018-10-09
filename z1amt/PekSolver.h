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
    boost::tuple<conductivity, conductivity, angle> cpanis(
            resistivity rop1,
            resistivity rop2,
            resistivity rop3,
            angle strike,
            angle dip,
            angle slant);
//    boost::tuple<
//    boost::units::si::conductivity,
//    boost::units::si::conductivity,
//    boost::units::si::plane_angle> cpanis (
//            boost::units::quantity<boost::units::si::resistivity> rop1,
//            boost::units::quantity<boost::units::si::resistivity> rop2,
//            boost::units::quantity<boost::units::si::resistivity> rop3,
//            boost::units::quantity<boost::units::si::plane_angle> strike,
//            boost::units::quantity<boost::units::si::plane_angle> dip,
//            boost::units::quantity<boost::units::si::plane_angle> slant);
public:

};


#endif //Z1DAMT_PEKSOLVER_H
