#include <paercebal/Graphics/maths/Matrix3D.hpp>

#include <gtest/gtest.h>

namespace paercebal::Graphics::world::tests
{
using namespace paercebal::Graphics::maths;

TEST(MatrixTests, OutputStreaming)
{
   Matrix3D<int> m;
   std::stringstream str;
   str << m;
   EXPECT_EQ("[ [0, 0, 0], [0, 0, 0], [0, 0, 0] ]", str.str());
}


TEST(MatrixTests, ThrowingAccessors)
{
   Matrix3D<int> m;
   EXPECT_EQ(0, m(0, 0));
   EXPECT_THROW(m(-1, 0), std::runtime_error);
   EXPECT_THROW(m(3, 0), std::runtime_error);
   EXPECT_THROW(m(1, -1), std::runtime_error);
   EXPECT_THROW(m(1, 3), std::runtime_error);
}


TEST(MatrixTests, Accessors)
{
   Matrix3D<int> m;

   for (auto x : std::array<int, 3>{0, 1, 2})
   {
      for (auto y : std::array<int, 3>{0, 1, 2})
      {
         EXPECT_EQ(0, m(x, y));
         m(x, y) = 42;
         EXPECT_EQ(42, m(x, y));
      }
   }
}


TEST(MatrixTests, Constructible)
{
   {
      Matrix3D<int> m;
      EXPECT_EQ(0, m(0, 0));
      EXPECT_EQ(0, m(0, 1));
      EXPECT_EQ(0, m(0, 2));
      EXPECT_EQ(0, m(1, 0));
      EXPECT_EQ(0, m(1, 1));
      EXPECT_EQ(0, m(1, 2));
      EXPECT_EQ(0, m(2, 0));
      EXPECT_EQ(0, m(2, 1));
      EXPECT_EQ(0, m(2, 2));
   }

   {
      Matrix3D<int> m(1, 2, 3, 4, 5, 6, 7, 8, 9);
      EXPECT_EQ(1, m(0, 0));
      EXPECT_EQ(2, m(0, 1));
      EXPECT_EQ(3, m(0, 2));
      EXPECT_EQ(4, m(1, 0));
      EXPECT_EQ(5, m(1, 1));
      EXPECT_EQ(6, m(1, 2));
      EXPECT_EQ(7, m(2, 0));
      EXPECT_EQ(8, m(2, 1));
      EXPECT_EQ(9, m(2, 2));
   }
}


TEST(MatrixTests, Equatable)
{
   Matrix3D<int> m0;
   EXPECT_EQ(0, m0(0, 0));
   EXPECT_EQ(0, m0(0, 1));
   EXPECT_EQ(0, m0(0, 2));
   EXPECT_EQ(0, m0(1, 0));
   EXPECT_EQ(0, m0(1, 1));
   EXPECT_EQ(0, m0(1, 2));
   EXPECT_EQ(0, m0(2, 0));
   EXPECT_EQ(0, m0(2, 1));
   EXPECT_EQ(0, m0(2, 2));

   Matrix3D<int> m00;
   EXPECT_EQ(0, m00(0, 0));
   EXPECT_EQ(0, m00(0, 1));
   EXPECT_EQ(0, m00(0, 2));
   EXPECT_EQ(0, m00(1, 0));
   EXPECT_EQ(0, m00(1, 1));
   EXPECT_EQ(0, m00(1, 2));
   EXPECT_EQ(0, m00(2, 0));
   EXPECT_EQ(0, m00(2, 1));
   EXPECT_EQ(0, m00(2, 2));

   Matrix3D<int> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
   EXPECT_EQ(1, m1(0, 0));
   EXPECT_EQ(2, m1(0, 1));
   EXPECT_EQ(3, m1(0, 2));
   EXPECT_EQ(4, m1(1, 0));
   EXPECT_EQ(5, m1(1, 1));
   EXPECT_EQ(6, m1(1, 2));
   EXPECT_EQ(7, m1(2, 0));
   EXPECT_EQ(8, m1(2, 1));
   EXPECT_EQ(9, m1(2, 2));

   Matrix3D<int> m11(1, 2, 3, 4, 5, 6, 7, 8, 9);
   EXPECT_EQ(1, m1(0, 0));
   EXPECT_EQ(2, m1(0, 1));
   EXPECT_EQ(3, m1(0, 2));
   EXPECT_EQ(4, m1(1, 0));
   EXPECT_EQ(5, m1(1, 1));
   EXPECT_EQ(6, m1(1, 2));
   EXPECT_EQ(7, m1(2, 0));
   EXPECT_EQ(8, m1(2, 1));
   EXPECT_EQ(9, m1(2, 2));

   EXPECT_EQ(m0, m00);
   EXPECT_EQ(m00, m0);
   EXPECT_EQ(m1, m11);
   EXPECT_EQ(m11, m1);

   EXPECT_NE(m0, m1);
   EXPECT_NE(m0, m11);
   EXPECT_NE(m1, m0);
   EXPECT_NE(m1, m00);
}


TEST(MatrixTests, Copyable)
{
   {
      Matrix3D<int> m0(1, 2, 3, 4, 5, 6, 7, 8, 9);

      Matrix3D<int> m1(m0);
      EXPECT_EQ(m0, m1);

      Matrix3D<int> m2 = m0;
      EXPECT_EQ(m0, m2);
   }

   {
      Matrix3D<int> m0;
      Matrix3D<int> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);

      Matrix3D<int> m2;

      EXPECT_EQ(m0, m2);
      EXPECT_NE(m1, m2);

      m2 = m1;

      EXPECT_NE(m0, m2);
      EXPECT_EQ(m1, m2);
   }
}


TEST(MatrixTests, Addition)
{
   // +
   {
      const Matrix3D<int> m0(1, 2, 3, 4, 5, 6, 7, 8, 9);
      Matrix3D<int> mResult;

      EXPECT_NE(m0, mResult);
      mResult = +m0;
      EXPECT_EQ(m0, mResult);
   }

   // +
   {
      Matrix3D<int> m0(1, 2, 3, 4, 5, 6, 7, 8, 9);
      const Matrix3D<int> m1(10, 20, 30, 40, 50, 60, 70, 80, 90);
      const Matrix3D<int> mExpected(11, 22, 33, 44, 55, 66, 77, 88, 99);

      m0 += m1;

      EXPECT_EQ(mExpected, m0);
   }

   // +
   {
      const Matrix3D<int> m0(1, 2, 3, 4, 5, 6, 7, 8, 9);
      const Matrix3D<int> m1(10, 20, 30, 40, 50, 60, 70, 80, 90);
      const Matrix3D<int> mExpected(11, 22, 33, 44, 55, 66, 77, 88, 99);

      Matrix3D<int> mResult = m0 + m1;

      EXPECT_EQ(mExpected, mResult);
   }
}


TEST(MatrixTests, Subtraction)
{
   // -
   {
      const Matrix3D<int> m0(1, 2, 3, 4, 5, 6, 7, 8, 9);
      const Matrix3D<int> mExpected(-1, -2, -3, -4, -5, -6, -7, -8, -9);
      Matrix3D<int> mResult;

      EXPECT_NE(mExpected, mResult);
      mResult = -m0;
      EXPECT_EQ(mExpected, mResult);
   }

   // -=
   {
      Matrix3D<int> m0(1, 2, 3, 4, 5, 6, 7, 8, 9);
      const Matrix3D<int> m1(10, 20, 30, 40, 50, 60, 70, 80, 90);
      const Matrix3D<int> mExpected(-9, -18, -27, -36, -45, -54, -63, -72, -81);

      m0 -= m1;

      EXPECT_EQ(mExpected, m0)
         << "       m0: " << m0 << "\n"
         << "mExpected: " << mExpected << "\n";
   }

   // -
   {
      const Matrix3D<int> m0(1, 2, 3, 4, 5, 6, 7, 8, 9);
      const Matrix3D<int> m1(10, 20, 30, 40, 50, 60, 70, 80, 90);
      const Matrix3D<int> mExpected(-9, -18, -27, -36, -45, -54, -63, -72, -81);

      Matrix3D<int> mResult = m0 - m1;

      EXPECT_EQ(mExpected, mResult)
         << "  mResult: " << mResult << "\n"
         << "mExpected: " << mExpected << "\n";
   }
}


TEST(MatrixTests, MultiplicationByScalars)
{
   // * by 0
   {
      const Matrix3D<int> m0;
      const Matrix3D<int> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);

      const Matrix3D<int> mResultA = m1 * 0;

      EXPECT_EQ(m0, mResultA);
      EXPECT_NE(m1, mResultA);

      const Matrix3D<int> mResultB = 0 * m1;

      EXPECT_EQ(m0, mResultB);
      EXPECT_NE(m1, mResultB);
   }

   // * by 1
   {
      const Matrix3D<int> m0;
      const Matrix3D<int> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);

      const Matrix3D<int> mResultA = m1 * 1;

      EXPECT_NE(m0, mResultA);
      EXPECT_EQ(m1, mResultA);

      const Matrix3D<int> mResultB = 1 * m1;

      EXPECT_NE(m0, mResultB);
      EXPECT_EQ(m1, mResultB);
   }

   // * By 10
   {
      const Matrix3D<int> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
      const Matrix3D<int> m10(10, 20, 30, 40, 50, 60, 70, 80, 90);

      const Matrix3D<int> mResultA = m1 * 10;

      EXPECT_EQ(m10, mResultA);
      EXPECT_NE(m1, mResultA);

      const Matrix3D<int> mResultB = 10 * m1;

      EXPECT_EQ(m10, mResultB);
      EXPECT_NE(m1, mResultB);
   }

   // *= By 10
   {
      Matrix3D<int> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
      const Matrix3D<int> m10(10, 20, 30, 40, 50, 60, 70, 80, 90);

      m1 *= 10;

      EXPECT_EQ(m10, m1);
   }
}


TEST(MatrixTests, MultiplicationByMatrix)
{
   // *
   {
      const Matrix3D<int> m0;
      const Matrix3D<int> mX(1, 2, 3, 4, 5, 6, 7, 8, 9);

      const Matrix3D<int> mResultA = m0 * mX;
      EXPECT_EQ(m0, mResultA);

      const Matrix3D<int> mResultB = mX * m0;
      EXPECT_EQ(m0, mResultB);
   }

   // *
   {
      const Matrix3D<int> m1(1, 0, 0, 0, 1, 0, 0, 0, 1);
      const Matrix3D<int> mX(1, 2, 3, 4, 5, 6, 7, 8, 9);

      const Matrix3D<int> mResultA = m1 * mX;
      EXPECT_EQ(mX, mResultA);

      const Matrix3D<int> mResultB = mX * m1;
      EXPECT_EQ(mX, mResultB);
   }

   // *
   {
      const Matrix3D<int> mA(1, 10, 100, 2, 20, 200, 3, 30, 300);
      const Matrix3D<int> mB(1, 2, 3, 4, 5, 6, 7, 8, 9);
      const Matrix3D<int> mExpected_A_B(741, 852, 963, 1482, 1704, 1926, 2223, 2556, 2889);
      const Matrix3D<int> mExpected_B_A(14, 140, 1400, 32, 320, 3200, 50, 500, 5000);

      const Matrix3D<int> mResult_A_B = mA * mB;
      EXPECT_EQ(mExpected_A_B, mResult_A_B);

      const Matrix3D<int> mResult_B_A = mB * mA;
      EXPECT_EQ(mExpected_B_A, mResult_B_A);
   }

   // *=
   {
      {
         Matrix3D<int> mA(1, 10, 100, 2, 20, 200, 3, 30, 300);
         const Matrix3D<int> mB(1, 2, 3, 4, 5, 6, 7, 8, 9);
         const Matrix3D<int> mExpected_A_B(741, 852, 963, 1482, 1704, 1926, 2223, 2556, 2889);

         mA *= mB;
         EXPECT_EQ(mExpected_A_B, mA);
      }

      {
         const Matrix3D<int> mA(1, 10, 100, 2, 20, 200, 3, 30, 300);
         Matrix3D<int> mB(1, 2, 3, 4, 5, 6, 7, 8, 9);
         const Matrix3D<int> mExpected_B_A(14, 140, 1400, 32, 320, 3200, 50, 500, 5000);

         mB *= mA;
         EXPECT_EQ(mExpected_B_A, mB);
      }
   }
}



}