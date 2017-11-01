#ifndef PAERCEBAL_x_GRAPHICS_x_WORLD_x_MATRIX3D_x_HPP
#define PAERCEBAL_x_GRAPHICS_x_WORLD_x_MATRIX3D_x_HPP

#include <SFML/Graphics.hpp>

#include <array>
#include <iostream>
#include <cmath>

namespace paercebal::Graphics::maths
{

template <typename T>
class Matrix3D;

template <typename T>
bool operator == (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> & operator += (Matrix3D<T> & lhs, const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> operator + (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> operator + (const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> operator - (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> & operator -= (Matrix3D<T> & lhs, const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> operator - (const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> & operator *= (Matrix3D<T> & lhs, const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> & operator *= (Matrix3D<T> & lhs, const T & rhs);

template <typename T>
Matrix3D<T> operator * (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> operator * (const Matrix3D<T> & lhs, const T & rhs);

template <typename T>
Matrix3D<T> operator * (const T & lhs, const Matrix3D<T> & rhs);

template <typename T>
sf::Vector3<T> operator * (const Matrix3D<T> & lhs, const sf::Vector3<T> & rhs);

//template <typename T>
//T determinant (const Matrix3D<T> & rhs);
//
//template <typename T>
//Matrix3D<T> transpose(const Matrix3D<T> & rhs);
//
//template <typename T>
//Matrix3D<T> invert(const Matrix3D<T> & rhs);
//
//template <typename T>
//Matrix3D<T> & operator /= (Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
//
//template <typename T>
//Matrix3D<T> & operator /= (Matrix3D<T> & lhs, const T & rhs);
//
//template <typename T>
//Matrix3D<T> operator / (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
//
//template <typename T>
//Matrix3D<T> operator / (const Matrix3D<T> & lhs, const T & rhs);
//
//template <typename T>
//Matrix3D<T> operator / (const T & lhs, const Matrix3D<T> & rhs);

template <typename T>
std::iostream & operator << (std::iostream & str, const Matrix3D<T> & matrix);


/// @brief 3D matrix class, complete with operators
///
/// The matrix has the following "layout": [xx, xy, yz, yx, yy, yz, zx, zy, zz] which,
/// put into a familiar matrix notations, is:
///
/// | xx  xy  xz |
/// | yx  yy  yz |
/// | zx  zy  zz |
///
/// @tparam T the underlying type (usually, float)
///
/// @todo reflect on possible use of +=, etc. operators. There's a single problem of operator += (int, Matrix&lt,int&gt;) which should return a copy, not a reference... or simply not exist.

template <typename T>
class Matrix3D
{
public:

   using underlying_type = T;

   Matrix3D() = default;         ///< default constructor
   Matrix3D(T vxx_, T vxy_, T vxz_, T vyx_, T vyy_, T vyz_, T vzx_, T vzy_, T vzz_);

   const T &            operator () (int i, int j) const;
   T &                  operator () (int i, int j);

   template <typename TT>
   explicit operator Matrix3D<TT>() const;

private:

   std::array<T, 9> values = {};    ///< values of the 3D matrix

   friend bool operator == <> (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   friend Matrix3D<T> & operator += <> (Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   friend Matrix3D<T> operator + <> (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   friend Matrix3D<T> operator + <> (const Matrix3D<T> & rhs);
   friend Matrix3D<T> & operator -= <> (Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   friend Matrix3D<T> operator - <> (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   friend Matrix3D<T> operator - <> (const Matrix3D<T> & rhs);
   friend Matrix3D<T> & operator *= <> (Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   friend Matrix3D<T> & operator *= <> (Matrix3D<T> & lhs, const T & rhs);
   friend Matrix3D<T> operator * <> (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   friend Matrix3D<T> operator * <> (const Matrix3D<T> & lhs, const T & rhs);
   friend Matrix3D<T> operator * <> (const T & lhs, const Matrix3D<T> & rhs);
   friend sf::Vector3<T> operator * <> (const Matrix3D<T> & lhs, const sf::Vector3<T> & rhs);
   //friend T determinant<>(const Matrix3D<T> & rhs);
   //friend Matrix3D<T> transpose<>(const Matrix3D<T> & rhs);
   //friend Matrix3D<T> invert<>(const Matrix3D<T> & rhs);
   //friend Matrix3D<T> & operator /= <> (Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   //friend Matrix3D<T> & operator /= <> (Matrix3D<T> & lhs, const T & rhs);
   //friend Matrix3D<T> operator / <> (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   //friend Matrix3D<T> operator / <> (const Matrix3D<T> & lhs, const T & rhs);
   //friend Matrix3D<T> operator / <> (const T & lhs, const Matrix3D<T> & rhs);
   friend std::iostream & operator << <> (std::iostream & str, const Matrix3D<T> & matrix);
};

/// @brief equality operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand
/// @param rhs the right-hand-side operand
///
/// @return true if both matrices are equal, else false
///
/// @note exception guarantee: Nothrow

template <typename T>
inline bool operator == (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
{
   return lhs.values == rhs.values;
}

/// @brief inequality operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand
/// @param rhs the right-hand-side operand
///
/// @return true if both matrices are not equal, else false
///
/// @note exception guarantee: Nothrow

template <typename T>
inline bool operator != (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
{
   return !(lhs == rhs);
}

/// @brief output stream operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param str the output stream object
/// @param matrix the matrix to be output
///
/// @return the stream object
///
/// @note exception guarantee: Basic

template <typename T>
inline std::iostream & operator << (std::iostream & str, const Matrix3D<T> & matrix)
{
   str << "[ [" << matrix.values[0] << ", " << matrix.values[1] << ", " << matrix.values[2] << "], [" << matrix.values[3] << ", " << matrix.values[4] << ", " << matrix.values[5] << "], [" << matrix.values[6] << ", " << matrix.values[7] << ", " << matrix.values[8] << "] ]";
   return str;
}

/// @brief constructor
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param vxx_ the xx parameter
/// @param vxy_ the xy parameter
/// @param vxz_ the xz parameter
/// @param vyx_ the yx parameter
/// @param vyy_ the yy parameter
/// @param vyz_ the yz parameter
/// @param vzx_ the zx parameter
/// @param vzy_ the zy parameter
/// @param vzz_ the zz parameter
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T>::Matrix3D(T vxx_, T vxy_, T vxz_, T vyx_, T vyy_, T vyz_, T vzx_, T vzy_, T vzz_)
   : values{ vxx_, vxy_, vxz_, vyx_, vyy_, vyz_, vzx_, vzy_, vzz_ }
{
}

/// @brief const getter for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param row the index of the row (from [0 to 2[)
/// @param column the index of the column (from [0 to 2[)
///
/// @return the const reference to the actual value
///
/// @throw std::runtime_exception if the row of columns are out of range
///
/// @note exception guarantee: Strong

template <typename T>
inline const T & Matrix3D<T>::operator () (int row, int column) const
{
   if ((row < 0) || (row > 2) || (column < 0) || (column > 2)) throw std::runtime_error("Wrong rows/columns for matrix");

   return this->values[row * 3 + column];
}

/// @brief getter for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param row the index of the row (from [0 to 2[)
/// @param column the index of the column (from [0 to 2[)
///
/// @return the reference to the actual value
///
/// @throw std::runtime_exception if the row of columns are out of range
///
/// @note exception guarantee: Strong

template <typename T>
inline T & Matrix3D<T>::operator () (int row, int column)
{
   if ((row < 0) || (row > 2) || (column < 0) || (column > 2)) throw std::runtime_error("Wrong rows/columns for matrix");

   return this->values[row * 3 + column];
}

/// @brief cast operator from one type of Matrix3D to another
///
/// @tparam T the underlying type of the current Matrix3D object
/// @tparam TT the underlying type of the desired Matrix3D object
///
/// @return the desired Matrix3D object
///
/// @note exception guarantee: Nothrow

template <typename T>
template <typename TT>
Matrix3D<T>::operator Matrix3D<TT>() const
{
   return Matrix3D<TT>
   {
        static_cast<TT>(this->values[0]), static_cast<TT>(this->values[1]), static_cast<TT>(this->values[2])
      , static_cast<TT>(this->values[3]), static_cast<TT>(this->values[4]), static_cast<TT>(this->values[5])
      , static_cast<TT>(this->values[6]), static_cast<TT>(this->values[7]), static_cast<TT>(this->values[8])
   }
}

/// @brief addition-assignment operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand (a matrix)
/// @param rhs the right-hand-side operand (a matrix)
///
/// @return the left-hand-side operand
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> & operator += (Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
{
   lhs.values[0] += rhs.values[0];
   lhs.values[1] += rhs.values[1];
   lhs.values[2] += rhs.values[2];
   lhs.values[3] += rhs.values[3];
   lhs.values[4] += rhs.values[4];
   lhs.values[5] += rhs.values[5];
   lhs.values[6] += rhs.values[6];
   lhs.values[7] += rhs.values[7];
   lhs.values[8] += rhs.values[8];
   return lhs;
}

/// @brief addition operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand (a matrix)
/// @param rhs the right-hand-side operand (a matrix)
///
/// @return the resulting Matrix3D
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> operator + (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
{
   return Matrix3D<T>{
        lhs.values[0] + rhs.values[0]
      , lhs.values[1] + rhs.values[1]
      , lhs.values[2] + rhs.values[2]
      , lhs.values[3] + rhs.values[3]
      , lhs.values[4] + rhs.values[4]
      , lhs.values[5] + rhs.values[5]
      , lhs.values[6] + rhs.values[6]
      , lhs.values[7] + rhs.values[7]
      , lhs.values[8] + rhs.values[8]
   };
}

/// @brief addition operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param rhs the right-hand-side operand (a matrix)
///
/// @return the resulting Matrix3D
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> operator + (const Matrix3D<T> & rhs)
{
   return rhs;
}

/// @brief subtraction-assignment operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand (a matrix)
/// @param rhs the right-hand-side operand (a matrix)
///
/// @return the left-hand-side operand
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> & operator -= (Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
{
   lhs.values[0] -= rhs.values[0];
   lhs.values[1] -= rhs.values[1];
   lhs.values[2] -= rhs.values[2];
   lhs.values[3] -= rhs.values[3];
   lhs.values[4] -= rhs.values[4];
   lhs.values[5] -= rhs.values[5];
   lhs.values[6] -= rhs.values[6];
   lhs.values[7] -= rhs.values[7];
   lhs.values[8] -= rhs.values[8];
   return lhs;
}

/// @brief subtraction operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand (a matrix)
/// @param rhs the right-hand-side operand (a matrix)
///
/// @return the resulting Matrix3D
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> operator - (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
{
   return Matrix3D<T>{
        lhs.values[0] - rhs.values[0]
      , lhs.values[1] - rhs.values[1]
      , lhs.values[2] - rhs.values[2]
      , lhs.values[3] - rhs.values[3]
      , lhs.values[4] - rhs.values[4]
      , lhs.values[5] - rhs.values[5]
      , lhs.values[6] - rhs.values[6]
      , lhs.values[7] - rhs.values[7]
      , lhs.values[8] - rhs.values[8]
   };
}

/// @brief subtraction operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param rhs the right-hand-side operand (a matrix)
///
/// @return the resulting Matrix3D
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> operator - (const Matrix3D<T> & rhs)
{
   return Matrix3D<T>{
        - rhs.values[0]
      , - rhs.values[1]
      , - rhs.values[2]
      , - rhs.values[3]
      , - rhs.values[4]
      , - rhs.values[5]
      , - rhs.values[6]
      , - rhs.values[7]
      , - rhs.values[8]
   };
}

/// @brief multiplication-assignment operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand (a matrix)
/// @param lhs the right-hand-side operand (a matrix)
///
/// @return the resulting Matrix3D
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> & operator *= (Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
{
   Matrix3D<T> tmp{
        lhs.values[0] * rhs.values[0] + lhs.values[1] * rhs.values[3] + lhs.values[2] * rhs.values[6]
      , lhs.values[0] * rhs.values[1] + lhs.values[1] * rhs.values[4] + lhs.values[2] * rhs.values[7]
      , lhs.values[0] * rhs.values[2] + lhs.values[1] * rhs.values[5] + lhs.values[2] * rhs.values[8]
      , lhs.values[3] * rhs.values[0] + lhs.values[4] * rhs.values[3] + lhs.values[5] * rhs.values[6]
      , lhs.values[3] * rhs.values[1] + lhs.values[4] * rhs.values[4] + lhs.values[5] * rhs.values[7]
      , lhs.values[3] * rhs.values[2] + lhs.values[4] * rhs.values[5] + lhs.values[5] * rhs.values[8]
      , lhs.values[6] * rhs.values[0] + lhs.values[7] * rhs.values[3] + lhs.values[8] * rhs.values[6]
      , lhs.values[6] * rhs.values[1] + lhs.values[7] * rhs.values[4] + lhs.values[8] * rhs.values[7]
      , lhs.values[6] * rhs.values[2] + lhs.values[7] * rhs.values[5] + lhs.values[8] * rhs.values[8]
   };

   lhs = tmp;
   return lhs;
}

/// @brief multiplication-assignment operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand (a matrix)
/// @param rhs the right-hand-side operand (a scalar)
///
/// @return the resulting Matrix3D
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> & operator *= (Matrix3D<T> & lhs, const T & rhs)
{
   lhs.values[0] *= rhs;
   lhs.values[1] *= rhs;
   lhs.values[2] *= rhs;
   lhs.values[3] *= rhs;
   lhs.values[4] *= rhs;
   lhs.values[5] *= rhs;
   lhs.values[6] *= rhs;
   lhs.values[7] *= rhs;
   lhs.values[8] *= rhs;
   return lhs;
}

/// @brief multiplication operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand (a matrix)
/// @param lhs the right-hand-side operand (a matrix)
///
/// @return the resulting Matrix3D
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> operator * (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
{
   return Matrix3D<T>{
        lhs.values[0] * rhs.values[0] + lhs.values[1] * rhs.values[3] + lhs.values[2] * rhs.values[6]
      , lhs.values[0] * rhs.values[1] + lhs.values[1] * rhs.values[4] + lhs.values[2] * rhs.values[7]
      , lhs.values[0] * rhs.values[2] + lhs.values[1] * rhs.values[5] + lhs.values[2] * rhs.values[8]
      , lhs.values[3] * rhs.values[0] + lhs.values[4] * rhs.values[3] + lhs.values[5] * rhs.values[6]
      , lhs.values[3] * rhs.values[1] + lhs.values[4] * rhs.values[4] + lhs.values[5] * rhs.values[7]
      , lhs.values[3] * rhs.values[2] + lhs.values[4] * rhs.values[5] + lhs.values[5] * rhs.values[8]
      , lhs.values[6] * rhs.values[0] + lhs.values[7] * rhs.values[3] + lhs.values[8] * rhs.values[6]
      , lhs.values[6] * rhs.values[1] + lhs.values[7] * rhs.values[4] + lhs.values[8] * rhs.values[7]
      , lhs.values[6] * rhs.values[2] + lhs.values[7] * rhs.values[5] + lhs.values[8] * rhs.values[8]
   };
}

/// @brief multiplication operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand (a matrix)
/// @param rhs the right-hand-side operand (a scalar)
///
/// @return the resulting Matrix3D
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> operator * (const Matrix3D<T> & lhs, const T & rhs)
{
   return Matrix3D<T>{
      lhs.values[0] * rhs
      , lhs.values[1] * rhs
      , lhs.values[2] * rhs
      , lhs.values[3] * rhs
      , lhs.values[4] * rhs
      , lhs.values[5] * rhs
      , lhs.values[6] * rhs
      , lhs.values[7] * rhs
      , lhs.values[8] * rhs
   };
}

/// @brief multiplication operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand (a scalar)
/// @param rhs the right-hand-side operand (a matrix)
///
/// @return the resulting Matrix3D
///
/// @note exception guarantee: Nothrow

template <typename T>
inline Matrix3D<T> operator * (const T & lhs, const Matrix3D<T> & rhs)
{
   return Matrix3D<T>{
      rhs.values[0] * lhs
      , rhs.values[1] * lhs
      , rhs.values[2] * lhs
      , rhs.values[3] * lhs
      , rhs.values[4] * lhs
      , rhs.values[5] * lhs
      , rhs.values[6] * lhs
      , rhs.values[7] * lhs
      , rhs.values[8] * lhs
   };
}

/// @brief multiplication operator for the Matrix3D
///
/// @tparam T the underlying type of the Matrix3D object
///
/// @param lhs the left-hand-side operand (a matrix)
/// @param rhs the right-hand-side operand (a vector3)
///
/// @return the resulting Matrix3D
///
/// @note exception guarantee: Nothrow

template <typename T>
inline sf::Vector3<T> operator * (const Matrix3D<T> & lhs, const sf::Vector3<T> & rhs)
{
   return sf::Vector3<T>{
        lhs.values[0] * rhs.x + lhs.values[1] * rhs.y + lhs.values[2] * rhs.z
      , lhs.values[3] * rhs.x + lhs.values[4] * rhs.y + lhs.values[5] * rhs.z
      , lhs.values[6] * rhs.x + lhs.values[7] * rhs.y + lhs.values[8] * rhs.z
   };
}


//template <typename T>
//T determinant(const Matrix3D<T> & rhs)
//{
//   return T(
//      (rhs.values[0] * (rhs.values[4] * rhs.values[8] - rhs.values[5] - rhs.values[7]))
//      - (rhs.values[1] * (rhs.values[3] * rhs.values[8] - rhs.values[5] - rhs.values[6]))
//      + (rhs.values[2] * (rhs.values[3] * rhs.values[7] - rhs.values[4] - rhs.values[6]))
//   );
//}
//
//template <typename T>
//Matrix3D<T> transpose(const Matrix3D<T> & rhs)
//{
//   return Matrix3D<T>(
//        rhs.values[0], rhs.values[3], rhs.values[3]
//      , rhs.values[1], rhs.values[4], rhs.values[7]
//      , rhs.values[2], rhs.values[5], rhs.values[8]
//   );
//}
//
//template <typename T>
//Matrix3D<T> invert(const Matrix3D<T> & rhs)
//{
//
//}
//
//
//template <typename T>
//Matrix3D<T> & operator /= (Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
//{
//
//}
//
//template <typename T>
//Matrix3D<T> & operator /= (Matrix3D<T> & lhs, const T & rhs);
//
//template <typename T>
//Matrix3D<T> operator / (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
//
//template <typename T>
//Matrix3D<T> operator / (const Matrix3D<T> & lhs, const T & rhs);
//
//template <typename T>
//Matrix3D<T> operator / (const T & lhs, const Matrix3D<T> & rhs);


} // namespace paercebal::Graphics::maths


#endif // PAERCEBAL_x_GRAPHICS_x_WORLD_x_MATRIX3D_x_HPP

