//
// Created by eric on 29/09/18.
//

#include <gtest/gtest.h>
#include <z1amt_lib.h>

TEST(mat22_can_manipulate, mat22_can_manipulate_determinant_Test){
    dcplx unit{1,0};
    dcplx imUnit{0,1};
    dcplx zero{0,0};

    mat22 z{unit, {0,0}, {0,0}, unit};

    ASSERT_DOUBLE_EQ(1, std::real(z.det()));
    z.xx = imUnit;
    z.yy = imUnit;

    ASSERT_DOUBLE_EQ(-1, std::real(z.det()));

    z.yy = zero;
    z.xy = imUnit;

    ASSERT_DOUBLE_EQ(0, std::real(z.det()));
}

TEST(mat22_can_manipulate, mat22_can_manipulate_matrix_product_Test){
    dcplx unit{1,0};
    dcplx imUnit{0,1};
    dcplx zero{0,0};

    mat22 A{zero, zero, zero, zero};
    mat22 B{zero, zero, zero, zero};

    A.xx = unit;
    A.yy = unit;

    ASSERT_DOUBLE_EQ(0, std::real((A*B).xx));
    ASSERT_DOUBLE_EQ(0, std::real((A*B).xy));
    ASSERT_DOUBLE_EQ(0, std::real((A*B).yx));
    ASSERT_DOUBLE_EQ(0, std::real((A*B).yy));
    ASSERT_DOUBLE_EQ(0, std::imag((A*B).xx));
    ASSERT_DOUBLE_EQ(0, std::imag((A*B).xy));
    ASSERT_DOUBLE_EQ(0, std::imag((A*B).yx));
    ASSERT_DOUBLE_EQ(0, std::imag((A*B).yy));

    B.xx = double(2)*unit;
    B.yy = double(-2)*unit;

    ASSERT_DOUBLE_EQ(2, std::real((A*B).xx));
    ASSERT_DOUBLE_EQ(0, std::real((A*B).xy));
    ASSERT_DOUBLE_EQ(0, std::real((A*B).yx));
    ASSERT_DOUBLE_EQ(-2, std::real((A*B).yy));
    ASSERT_DOUBLE_EQ(0, std::imag((A*B).xx));
    ASSERT_DOUBLE_EQ(0, std::imag((A*B).xy));
    ASSERT_DOUBLE_EQ(0, std::imag((A*B).yx));
    ASSERT_DOUBLE_EQ(0, std::imag((A*B).yy));

    A.xx = double(-3)*unit - 4.0*imUnit;
    A.xy = 4.44 * unit - 3.44 * imUnit;
    A.yx = 12.23 * unit - 0.25 * imUnit;
    A.yy = 11.1 * imUnit;

    B.xx = double(2)*unit + imUnit;
    B.xy = 1.23 * unit - 3.21 * imUnit;
    B.yx = -2.23 * unit - 3.25 * imUnit;
    B.yy = double(-2)*unit + 11.1 * imUnit;

//    ASSERT_NEAR(-23.0812, std::real((A*B).xx), double(1E-12));
    ASSERT_DOUBLE_EQ(-23.08120, std::real((A*B).xx));
    ASSERT_DOUBLE_EQ(12.77400, std::real((A*B).xy));
    ASSERT_DOUBLE_EQ(60.78500, std::real((A*B).yx));
    ASSERT_DOUBLE_EQ(-108.96960, std::real((A*B).yy));
    ASSERT_DOUBLE_EQ(-17.75880, std::imag((A*B).xx));
    ASSERT_DOUBLE_EQ(60.87400, std::imag((A*B).xy));
    ASSERT_DOUBLE_EQ(-13.02300, std::imag((A*B).yx));
    ASSERT_DOUBLE_EQ(-61.76580, std::imag((A*B).yy));
}

TEST(mat22_can_manipulate, mat22_can_manipulate_can_subtract_Test){
    dcplx unit{1,0};
    dcplx imUnit{0,1};
    dcplx zero{0,0};

    mat22 A{zero, zero, zero, zero};
    mat22 B{zero, zero, zero, zero};
    A.xx = double(-3)*unit - 4.0*imUnit;
    A.xy = 4.44 * unit - 3.44 * imUnit;
    A.yx = 12.23 * unit - 0.25 * imUnit;
    A.yy = 11.1 * imUnit;

    B.xx = double(2)*unit + imUnit;
    B.xy = 1.23 * unit - 3.21 * imUnit;
    B.yx = -2.23 * unit - 3.25 * imUnit;
    B.yy = double(-2)*unit + 11.1 * imUnit;

    mat22 C = A-B;
//    ASSERT_NEAR(-23.0812, std::real((A*B).xx), double(1E-12));
    ASSERT_DOUBLE_EQ(std::real(A.xx)- std::real(B.xx), std::real((C).xx));
    ASSERT_DOUBLE_EQ(std::real(A.xy)- std::real(B.xy), std::real((C).xy));
    ASSERT_DOUBLE_EQ(std::real(A.yx)- std::real(B.yx), std::real((C).yx));
    ASSERT_DOUBLE_EQ(std::real(A.yy)- std::real(B.yy), std::real((C).yy));
    ASSERT_DOUBLE_EQ(std::imag(A.xx)- std::imag(B.xx), std::imag((C).xx));
    ASSERT_DOUBLE_EQ(std::imag(A.xy)- std::imag(B.xy), std::imag((C).xy));
    ASSERT_DOUBLE_EQ(std::imag(A.yx)- std::imag(B.yx), std::imag((C).yx));
    ASSERT_DOUBLE_EQ(std::imag(A.yy)- std::imag(B.yy), std::imag((C).yy));
}

TEST(mat22_can_manipulate, mat22_can_manipulate_can_transpose_Test){
    dcplx unit{1,0};
    dcplx imUnit{0,1};
    dcplx zero{0,0};

    mat22 A{zero, zero, zero, zero};
    A.xx = double(-3)*unit - 4.0*imUnit;
    A.xy = 4.44 * unit - 3.44 * imUnit;
    A.yx = 12.23 * unit - 0.25 * imUnit;
    A.yy = 11.1 * imUnit;

    ASSERT_TRUE(A.T().T()==A);
    ASSERT_TRUE(A.T()!=A);
    ASSERT_EQ((A.T()).xy,A.yx);
    ASSERT_EQ((A.T()).yx,A.xy);
}