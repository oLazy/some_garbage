//
// Created by eric on 29/09/18.
//

#include <gtest/gtest.h>
#include <z1amt_lib.h>
#include <boost/tuple/tuple_io.hpp>
#include <boost/units/systems/si/io.hpp>

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

    ASSERT_DOUBLE_EQ(-23.08120, std::real((A*B).xx));
    ASSERT_DOUBLE_EQ(12.77400, std::real((A*B).xy));
    ASSERT_DOUBLE_EQ(60.78500, std::real((A*B).yx));
    ASSERT_DOUBLE_EQ(-108.96960, std::real((A*B).yy));
    ASSERT_DOUBLE_EQ(-17.75880, std::imag((A*B).xx));
    ASSERT_DOUBLE_EQ(60.87400, std::imag((A*B).xy));
    ASSERT_DOUBLE_EQ(-13.02300, std::imag((A*B).yx));
    ASSERT_DOUBLE_EQ(-61.76580, std::imag((A*B).yy));
}

TEST(mat22_can_manipulate, mat22_can_manipulate_multiply_by_scalar_Test){
    dcplx unit{1,0};
    dcplx imUnit{0,1};
    dcplx zero{0,0};

    mat22 A{unit+imUnit, unit-imUnit, -unit+imUnit, -unit-imUnit};
    mat22 B = A*-2.9;
    ASSERT_EQ(dcplx(-2.9,-2.9),B.xx);
    ASSERT_EQ(dcplx(-2.9,2.9),B.xy);
    ASSERT_EQ(dcplx(2.9,-2.9),B.yx);
    ASSERT_EQ(dcplx(2.9,2.9),B.yy);
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

TEST(mat33_can_manipulate, mat33_can_manipulate_can_multiply_Test){
    mat33 eye(1,0,0,0,1,0,0,0,1);
    mat33 A(1., 2., 3.,
            4., 5., 6.,
            7., 8., 9.);
    mat33 B(1.2, 2.5, 4.7,
            5.6, 3.4, 6.7,
            3.1, 3.2, 7.1);
    mat33 res(21.7, 18.9, 39.4,
              51.4, 46.2, 94.9,
              81.1, 73.5, 150.4);
    ASSERT_TRUE(A*B!=B*A);
    ASSERT_TRUE(A*eye==A);
    ASSERT_TRUE(A*eye==eye*A);
    mat33 C=A*B;
    ASSERT_DOUBLE_EQ(res.a11, C.a11);
    ASSERT_DOUBLE_EQ(res.a12, C.a12);
    ASSERT_DOUBLE_EQ(res.a13, C.a13);
    ASSERT_DOUBLE_EQ(res.a21, C.a21);
    ASSERT_DOUBLE_EQ(res.a22, C.a22);
    ASSERT_DOUBLE_EQ(res.a23, C.a23);
    ASSERT_DOUBLE_EQ(res.a31, C.a31);
    ASSERT_DOUBLE_EQ(res.a32, C.a32);
    ASSERT_DOUBLE_EQ(res.a33, C.a33);
}

TEST(mat33_can_manipulate, mat33_can_manipulate_can_transpose_Test){
    mat33 A(1.2, 2.5, 4.7,
            5.6, 3.4, 6.7,
            3.1, 3.2, 7.1);

    ASSERT_TRUE(A!=A.T());
    ASSERT_TRUE(A==A.T().T());
    ASSERT_DOUBLE_EQ(A.a12,(A.T()).a21);
    ASSERT_DOUBLE_EQ(A.a13,(A.T()).a31);
    ASSERT_DOUBLE_EQ(A.a23,(A.T()).a32);
    ASSERT_DOUBLE_EQ(A.T().a12, A.a21);
    ASSERT_DOUBLE_EQ(A.T().a13, A.a31);
    ASSERT_DOUBLE_EQ(A.T().a23, A.a32);
}

TEST(mat33_can_manipulate, mat33_can_manipulate_determinant_Test){
    mat33 A(1, 0 ,0,
            0, 1, 0,
            0, 0, 1);

    mat33 B( 1, 2, 3,
             4, 5, 6,
             7, 8, 9);

    ASSERT_DOUBLE_EQ(1, A.det());
    ASSERT_DOUBLE_EQ(B.T().det(), B.det());
    B.a12 = -2.;
    ASSERT_DOUBLE_EQ(-24, B.det());
//    std::cout << std::endl << B << std::endl << B.det() << std::endl;
}

TEST(pek_solver, pek_solver_cpanis_Test){
    PekSolver solver;
    const resistivity rho(1000.0 * Ohms_meter);
    const angle zero(0.0 * degree);
    const angle ninety(90.0 * degree);
    boost::tuple<conductivity, double, angle> res;
    res = solver.cpanis(rho, rho, rho, zero, zero, zero);
    conductivity mean = res.get<0>();
    double ratio = res.get<1>();
    ASSERT_DOUBLE_EQ(1.0, ratio);


}