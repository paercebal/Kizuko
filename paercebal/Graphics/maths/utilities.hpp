#ifndef PAERCEBAL_x_GRAPHICS_x_MATHS_x_UTILITIES_x_HPP
#define PAERCEBAL_x_GRAPHICS_x_MATHS_x_UTILITIES_x_HPP

#include <paercebal/Graphics/maths/Matrix3D.hpp>

#include <SFML/Graphics.hpp>

#include <array>
#include <iostream>
#include <cmath>

namespace paercebal::Graphics::maths::utilities
{
template <typename T>
constexpr T pi = T(3.141592653589793238462643383279502884L);

template <typename T>
constexpr T pi_1_2 = T(3.141592653589793238462643383279502884L / 2);

template <typename T>
constexpr T pi_1_4 = T(3.141592653589793238462643383279502884L / 4);

template <typename T>
constexpr T pi_3_4 = T(3 * 3.141592653589793238462643383279502884L / 4);


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

template <typename T>
inline sf::Vector3<T> createTranslationVector(const T x, const T y, const T z)
{
   return { x, y, z };
}

template <typename T>
inline sf::Vector3<T> createTranslationVectorOnX(const T value)
{
   return { x, 0, 0 };
}

template <typename T>
inline sf::Vector3<T> createTranslationVectorOnY(const T value)
{
   return { 0, y, 0 };
}

template <typename T>
inline sf::Vector3<T> createTranslationVectorOnZ(const T value)
{
   return { 0, 0, z };
}

template <typename T>
inline Matrix3D<T> createScaleMatrix(const T x, const T y, const T z)
{
   return { x, 0, 0, 0, y, 0, 0, 0, z };
}

template <typename T>
inline Matrix3D<T> createScaleMatrixOnX(const T value)
{
   return { x, 0, 0, 0, 0, 0, 0, 0, 0 };
}

template <typename T>
inline Matrix3D<T> createScaleMatrixOnY(const T value)
{
   return { 0, 0, 0, 0, y, 0, 0, 0, 0 };
}

template <typename T>
inline Matrix3D<T> createScaleMatrixOnZ(const T value)
{
   return { 0, 0, 0, 0, 0, 0, 0, 0, z };
}


} // namespace paercebal::Graphics::maths::utilities



#endif // PAERCEBAL_x_GRAPHICS_x_MATHS_x_UTILITIES_x_HPP

