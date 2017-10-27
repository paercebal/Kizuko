#include <paercebal/KizukoLib/matrices/Matrix3D.hpp>

#include <gtest/gtest.h>

TEST(MatricesTest, Equatable)
{
   using namespace paercebal::KizukoLib::matrices;

   const Matrix3D<int> a{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   const Matrix3D<int> b{ 100, 200, 300, 400, 500, 600, 700, 800, 900 };
   const Matrix3D<int> c{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

   EXPECT_NE(a, b);
   EXPECT_NE(b, c);
   EXPECT_EQ(a, c);
}

TEST(MatricesTest, Addition)
{
   using namespace paercebal::KizukoLib::matrices;

   const Matrix3D<int> lhs{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   const Matrix3D<int> rhs{ 100, 200, 300, 400, 500, 600, 700, 800, 900 };
   const Matrix3D<int> expected_result{ 101, 202, 303, 404, 505, 606, 707, 808, 909 };
   const Matrix3D<int> result = lhs + rhs;

   EXPECT_EQ(expected_result, result);
}


TEST(MatricesTest, Multiplication)
{
   using namespace paercebal::KizukoLib::matrices;

   {
      const Matrix3D<int> lhs{ 10, 20, 30, 40, 50, 60, 70, 80, 90 };
      const Matrix3D<int> rhs{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      const Matrix3D<int> expected_result{ 300, 360, 420, 660, 810, 960, 1020, 1260, 1500 };
      const Matrix3D<int> result = lhs * rhs;

      EXPECT_EQ(expected_result, result);
   }

   {
      const Matrix3D<int> lhs{ 10, 20, 30, 40, 50, 60, 70, 80, 90 };
      const sf::Vector3<int> rhs{ 1, 4, 7 };
      const sf::Vector3<int> expected_result{ 300, 660, 1020 };
      const sf::Vector3<int> result = lhs * rhs;

      EXPECT_EQ(expected_result, result);
   }
}

