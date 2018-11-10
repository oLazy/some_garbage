//
// Created by eric on 29/09/18.
//
// configuration test, check if I can use GTest and link all appropriately


#include <gtest/gtest.h>
#include <z1amt_lib.h>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/cmath.hpp>
#include <UnitsSetup.h>
#include <d1node.h>
TEST(basic_check, test_eq){
    EXPECT_EQ(1, 1);
}

TEST(basic_check, test_neq){
    EXPECT_NE(0, 1);
}

TEST(can_link, trivial_test){
    cheers();

    std::cout << std::endl << "pi = " << mt::pi << std::endl;
    std::cout << std::endl << "mu0 = " << mt::mu0 << std::endl;
    std::cout << std::endl << "epsilon0 = " << mt::epsilon0 << std::endl;
    std::cout << std::endl << "c = " << 1./boost::units::sqrt(mt::mu0 * mt::epsilon0)<< std::endl;
    ASSERT_TRUE(true);
}

TEST(matrix22, matrix22_can_declare_matrix_with_units_Test){
    constexpr dcplx z(1.4, -1.4);
    constexpr dcplx zero(0., 0.);
    boost::units::matrix22<dcplx> mc(zero,z,-z,zero);
    boost::units::matrix22<double> m(0.,1.,-1.,0.);
    boost::units::quantity<boost::units::si::length, boost::units::matrix22<double> > mat(m*meters);
    //boost::units::quantity<boost::units::si::length, boost::units::matrix22<dcplx> > matc(mc*meters);

    std::cout << std::endl << m << std::endl;
    std::cout << std::endl << mat << std::endl;
}


TEST(d1node, d1node_can_print_out_Test){
    length zcoord{1.0*meters};
    conductivity s_mean{2.0*siemens_per_meter};
    double ratio{0.5};
    angle beta{90*degrees};

    d1node generic_node{zcoord, s_mean, ratio, beta};
    std::cout << std::endl << generic_node << std::endl;

    std::cout << std::endl << generic_node.sigma_h() << std::endl;
    std::cout << std::endl << generic_node.sigma_l() << std::endl;
    std::cout << std::endl << generic_node.beta_s() << std::endl;
}

TEST(pek_solver, pek_solver_units_zrot_print_Test){
    PekSolver s;

    impedance one{dcplx{1.0,0.0}*Ohm};
    impedance zero{dcplx{0.0,0.0}*Ohm};
    angle pi_rot{0.5*M_PI*radians};

    impedance_tensor z{one, zero, zero, one}; // identity
    impedance_tensor zb = s.rotz(z, pi_rot);

    std::cout << std::endl << boost::get<xx>(zb) << std::endl;
    std::cout << std::endl << boost::get<xy>(zb) << std::endl;
    std::cout << std::endl << boost::get<yx>(zb) << std::endl;
    std::cout << std::endl << boost::get<yy>(zb) << std::endl;
}