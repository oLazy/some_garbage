//
// Created by eric on 06/10/18.
//

#include "PekSolver.h"
//#include <math.h>
#include <boost/units/cmath.hpp>
namespace bu = boost::units;
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

boost::tuple<conductivity, double, angle> PekSolver::cpanis(
        resistivity rop1,
        resistivity rop2,
        resistivity rop3,
        angle strike,
        angle dip,
        angle slant)
{
    double cps(bu::cos(strike));
    double cth(bu::cos(dip));
    double cfi(bu::cos(slant));
    double sps(bu::sin(strike));
    double sth(bu::sin(dip));
    double sfi(bu::sin(slant));

    double c2ps,s2ps,c2th,s2th,csps,csth;
    conductivity sgp1 = 1./rop1;
    conductivity sgp2 = 1./rop2;
    conductivity sgp3 = 1./rop3;
    conductivity pom1=sgp1*cfi*cfi+sgp2*sfi*sfi;
    conductivity pom2=sgp1*sfi*sfi+sgp2*cfi*cfi;
    conductivity pom3=(sgp1-sgp2)*sfi*cfi;

    c2ps=cps*cps;
    s2ps=sps*sps;
    c2th=cth*cth;
    s2th=sth*sth;
    csps=cps*sps;
    csth=cth*sth;

    conductivity sg11(pom1*c2ps+pom2*s2ps*c2th-2.*pom3*cth*csps+sgp3*s2th*s2ps);
    conductivity sg12(pom1*csps-pom2*c2th*csps+pom3*cth*(c2ps-s2ps)-sgp3*s2th*csps);
    conductivity sg13(-pom2*csth*sps+pom3*sth*cps+sgp3*csth*sps);
    conductivity sg22(pom1*s2ps+pom2*c2ps*c2th+2.*pom3*cth*csps+sgp3*s2th*c2ps);
    conductivity sg23(pom2*csth*cps+pom3*sth*sps-sgp3*csth*cps);
    conductivity sg33(pom2*s2th+sgp3*c2th);

    conductivity axx(sg11-sg13*sg13/sg33);
    conductivity axy(sg12-sg13*sg23/sg33);
    conductivity ayx(sg12-sg12*sg23/sg33);
    conductivity ayy(sg22-sg23*sg23/sg33);

    conductivity da12(bu::sqrt((axx-ayy)*(axx-ayy)+4.0*axy*ayx));
    conductivity al(0.5*(axx+ayy+da12));
    conductivity at(0.5*(axx+ayy-da12));

    angle blt(0.5 * bu::acos((axx-ayy)/da12) );

    if(axy<0.0*siemens_per_meter)blt*=-1.;
    return {(al+at)*0.5, at/al, blt};
}