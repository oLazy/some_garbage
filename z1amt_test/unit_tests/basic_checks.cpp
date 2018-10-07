//
// Created by eric on 29/09/18.
//
// configuration test, check if I can use GTest and link all appropriately


#include <gtest/gtest.h>
#include <z1amt_lib.h>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/cmath.hpp>
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

