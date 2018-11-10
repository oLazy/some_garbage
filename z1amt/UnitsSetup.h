//
// Created by eric on 08/10/18.
//

#ifndef Z1DAMT_UNITSSETUP_H
#define Z1DAMT_UNITSSETUP_H

#include <boost/units/systems/si/conductivity.hpp>
#include <boost/units/systems/si/resistivity.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/si/permeability.hpp>
#include <boost/units/systems/si/permittivity.hpp>
#include <boost/units/systems/si/capacitance.hpp>
#include <boost/units/systems/si/inductance.hpp>
#include <boost/units/systems/si/impedance.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/frequency.hpp>
#include <boost/units/quantity.hpp>
#include <boost/tuple/tuple.hpp>
#include <complex>

//define unit quantities in the global namespace

#include <boost/units/base_units/angle/radian.hpp>
typedef boost::units::angle::radian_base_unit::unit_type radian_unit;
BOOST_UNITS_STATIC_CONSTANT(radian, radian_unit);
BOOST_UNITS_STATIC_CONSTANT(radians, radian_unit);

#include <boost/units/base_units/angle/degree.hpp>
typedef boost::units::angle::degree_base_unit::unit_type degree_unit;
BOOST_UNITS_STATIC_CONSTANT(degree, degree_unit);
BOOST_UNITS_STATIC_CONSTANT(degrees, degree_unit);

#include <boost/units/base_units/si/kilogram.hpp>
typedef boost::units::si::kilogram_base_unit::unit_type kilogram_unit;
BOOST_UNITS_STATIC_CONSTANT(kilogram, kilogram_unit);
BOOST_UNITS_STATIC_CONSTANT(kg, kilogram_unit);

#include <boost/units/base_units/si/ampere.hpp>
typedef boost::units::si::ampere_base_unit::unit_type current_unit;
BOOST_UNITS_STATIC_CONSTANT(Ampere, current_unit);

#include <boost/units/base_units/si/second.hpp>
typedef boost::units::si::second_base_unit::unit_type second_unit;
BOOST_UNITS_STATIC_CONSTANT(second, second_unit);
BOOST_UNITS_STATIC_CONSTANT(seconds, second_unit);

#include <boost/units/base_units/si/meter.hpp>
typedef boost::units::si::meter_base_unit::unit_type meter_unit;
BOOST_UNITS_STATIC_CONSTANT(meter, meter_unit);
BOOST_UNITS_STATIC_CONSTANT(meters, meter_unit);

typedef boost::units::quantity<boost::units::si::resistivity> resistivity;
BOOST_UNITS_STATIC_CONSTANT(Ohm_meter, boost::units::si::resistivity);
BOOST_UNITS_STATIC_CONSTANT(Ohms_meter, boost::units::si::resistivity);

typedef boost::units::quantity<boost::units::si::conductivity> conductivity;
BOOST_UNITS_STATIC_CONSTANT(siemens_per_meter, boost::units::si::conductivity);

typedef boost::units::quantity<boost::units::si::impedance,std::complex<double> > impedance;
BOOST_UNITS_STATIC_CONSTANT(Ohm, boost::units::si::impedance);
BOOST_UNITS_STATIC_CONSTANT(ohm, boost::units::si::impedance);

typedef boost::tuple<impedance, impedance, impedance, impedance> impedance_tensor;
enum {xx=0, xy=1, yx=2, yy=3}; // should be able to call boost::get<xx>(impedance_tensor) and retreive the correct value

typedef boost::units::quantity<boost::units::si::capacitance> capacitance;
BOOST_UNITS_STATIC_CONSTANT(farad, boost::units::si::capacitance);

typedef boost::units::quantity<boost::units::si::inductance> inductance;
BOOST_UNITS_STATIC_CONSTANT(Henry, boost::units::si::inductance);
BOOST_UNITS_STATIC_CONSTANT(henry, boost::units::si::inductance);

typedef boost::units::quantity<boost::units::si::frequency, std::complex<double> > frequency;
BOOST_UNITS_STATIC_CONSTANT(Hertz, boost::units::si::frequency);
BOOST_UNITS_STATIC_CONSTANT(Hz, boost::units::si::frequency);

typedef boost::units::quantity<boost::units::si::permeability> permeability;

typedef boost::units::quantity<boost::units::si::permittivity> permittivity;

typedef boost::units::quantity<boost::units::si::plane_angle> angle;

typedef boost::units::quantity<boost::units::si::length> length;



#endif //Z1DAMT_UNITSSETUP_H