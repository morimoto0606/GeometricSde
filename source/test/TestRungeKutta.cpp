#include <gtest/gtest.h>
#include <functional>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "../src/RungeKutta.hpp"
#include "../src/sde.h"

using namespace std;
using namespace Eigen;

class RungeKuttaTest : public ::testing::Test {
public:
    virtual void SetUp() {
        _a << 0.,0.,0.,
              1.,0.,0.,
              2.,3.,0.;

        _h = 0.1;

    }
    Matrix3d _a;
    double _h;
};

TEST_F(RungeKuttaTest, exp) {
    sde::RungeKutta5 rk;
    auto vecField = [this](const Eigen::Matrix<double, 3, 1>& x){return _a * x;};
    Eigen::Vector3d x;
    x << 3.,2.,1.;   
    auto actual = rk.solve(_h, vecField, x);

    sde::RungeKutta4 rk4;
    auto actual2 = rk4.solve(_h, vecField, x);

    sde::RungeKutta2 rk2;
    auto actual3 = rk2.solve(_h, vecField, x);

    Eigen::Vector3d y;
    y << 3.,2.,1.;   
 
    auto expected = (Eigen::MatrixXd::Identity(3,3)
        + _h * _a + 0.5 * _h * _h * _a * _a) * y;

    for (int i = 0; i < 3; ++i) {
        EXPECT_NEAR(expected(i, 0), static_cast<double>(actual(i, 0)), 1e-4);
        EXPECT_NEAR(expected(i, 0), static_cast<double>(actual2(i, 0)), 1e-4);
        EXPECT_NEAR(expected(i, 0), static_cast<double>(actual3(i, 0)), 1e-4);
    }
}
  

