//
// Created by eric on 06/10/18.
//

#include "PekSolver.h"
#include <math.h>

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

boost::tuple<conductivity, conductivity, angle>
PekSolver::cpanis(
        resistivity rop1,
        resistivity rop2,
        resistivity rop3,
        angle strike,
        angle dip,
        angle slant)
        {
            return boost::tuple <conductivity, conductivity, angle > ();
        }

//boost::tuple<
//        boost::units::si::conductivity,
//        boost::units::si::conductivity,
//        boost::units::si::plane_angle> PekSolver::cpanis(boost::units::quantity<boost::units::si::resistivity> rop1,
//                                                         boost::units::quantity<boost::units::si::resistivity> rop2,
//                                                         boost::units::quantity<boost::units::si::resistivity> rop3,
//                                                         boost::units::quantity<boost::units::si::plane_angle> strike,
//                                                         boost::units::quantity<boost::units::si::plane_angle> dip,
//                                                         boost::units::quantity<boost::units::si::plane_angle> slant) {
//    quantity<conductivity> sgp[3] = {1./rop1, 1./rop2, 1./rop3};
//    quantity<plane_angle> rstr = static_cast<quantity<radians> >(strike);
//    return boost::tuple<boost::units::si::conductivity, boost::units::si::conductivity, boost::units::si::plane_angle>();
//}
//
