#ifndef PAERCEBAL_x_KIZUKOLIB_x_MARTICES_x_MATRIX3D_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_MARTICES_x_MATRIX3D_x_HPP

#include <SFML/Graphics.hpp>

#include <array>
#include <iostream>
#include <cmath>

namespace paercebal::KizukoLib::matrices
{

template <typename T>
class Matrix3D;

template <typename T>
bool operator == (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> operator + (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);

template <typename T>
Matrix3D<T> operator * (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);

template <typename T>
sf::Vector3<T> operator * (const Matrix3D<T> & lhs, const sf::Vector3<T> & rhs);

template <typename T>
std::iostream & operator << (std::iostream & str, const Matrix3D<T> & matrix);



template <typename T>
class Matrix3D
{
public:
   Matrix3D() = default;
   Matrix3D(T vxx_, T vxy_, T vxz_, T vyx_, T vyy_, T vyz_, T vzx_, T vzy_, T vzz_);

   const T &            operator () (int i, int j) const;
   T &                  operator () (int i, int j);

   template <typename TT>
   explicit operator Matrix3D<TT>() const;

private:

   std::array<T, 9> values = {};

   friend bool operator == <> (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   friend Matrix3D<T> operator + <> (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   friend Matrix3D<T> operator * <> (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs);
   friend sf::Vector3<T> operator * <> (const Matrix3D<T> & lhs, const sf::Vector3<T> & rhs);
   friend std::iostream & operator << <> (std::iostream & str, const Matrix3D<T> & matrix);
};


template <typename T>
inline bool operator == (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
{
   return lhs.values == rhs.values;
}


template <typename T>
inline bool operator != (const Matrix3D<T> & lhs, const Matrix3D<T> & rhs)
{
   return !(lhs == rhs);
}


template <typename T>
inline std::iostream & operator << (std::iostream & str, const Matrix3D<T> & matrix)
{
   str << "[ [" << matrix.value[0] << ", " << matrix.value[1] << ", " << matrix.value[2] << "], [" << matrix.value[3] << ", " << matrix.value[4] << ", " << matrix.value[5] << "], [" << matrix.value[6] << ", " << matrix.value[7] << ", " << matrix.value[8] << "] ]";
   return str;
}


template <typename T>
inline Matrix3D<T>::Matrix3D(T vxx_, T vxy_, T vxz_, T vyx_, T vyy_, T vyz_, T vzx_, T vzy_, T vzz_)
   : values{ vxx_, vxy_, vxz_, vyx_, vyy_, vyz_, vzx_, vzy_, vzz_ }
{
}

template <typename T>
inline const T & Matrix3D<T>::operator () (int row, int column) const
{
   if ((row < 0) || (row > 2) || (column < 0) || (column > 2)) throw std::runtime_error("Wrong rows/columns for matrix");

   return this->values[row * 3 + column];
}

template <typename T>
inline T & Matrix3D<T>::operator () (int row, int column)
{
   if ((row < 0) || (row > 2) || (column < 0) || (column > 2)) throw std::runtime_error("Wrong rows/columns for matrix");

   return this->values.at[row * 3 + column];
}

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

template <typename T>
inline sf::Vector3<T> operator * (const Matrix3D<T> & lhs, const sf::Vector3<T> & rhs)
{
   return sf::Vector3<T>{
        lhs.values[0] * rhs.x + lhs.values[1] * rhs.y + lhs.values[2] * rhs.z
      , lhs.values[3] * rhs.x + lhs.values[4] * rhs.y + lhs.values[5] * rhs.z
      , lhs.values[6] * rhs.x + lhs.values[7] * rhs.y + lhs.values[8] * rhs.z
   };
}


template <typename T>
inline Matrix3D<T> createRotationMatrixAroundX(const T angle)
{
   const T cosA = std::cos(angle);
   const T sinA = std::sin(angle);
   return { 1, 0, 0, 0, cosA, -sinA, 0, sinA, cosA };
}

template <typename T>
inline Matrix3D<T> createRotationMatrixAroundY(const T angle)
{
   const T cosA = std::cos(angle);
   const T sinA = std::sin(angle);
   return { cosA, 0, sinA, 0, 1, 0, -sinA, 0, cosA };
}

template <typename T>
inline Matrix3D<T> createRotationMatrixAroundZ(const T angle)
{
   const T cosA = std::cos(angle);
   const T sinA = std::sin(angle);
   return {cosA, -sinA, 0, sinA, cosA, 0, 0, 0, 1 };
}





} // namespace paercebal::KizukoLib::shapes





#endif // PAERCEBAL_x_KIZUKOLIB_x_MARTICES_x_MATRIX3D_x_HPP

