//
// Created by eric on 29/09/18.
//
// configuration test, check if I can use GTest and link all appropriately


#include <gtest/gtest.h>
#include <z1amt_lib.h>

TEST(basic_check, test_eq){
    EXPECT_EQ(1, 1);
}

TEST(basic_check, test_neq){
    EXPECT_NE(0, 1);
}

TEST(can_link, trivial_test){
    cheers();
    ASSERT_TRUE(true);
}

