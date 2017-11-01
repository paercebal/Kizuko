#ifndef PAERCEBAL_x_GRAPHICSTESTS_x_MAIN_x_HPP
#define PAERCEBAL_x_GRAPHICSTESTS_x_MAIN_x_HPP

#include <paercebal/Graphics/world/DefaultObject.hpp>
#include <paercebal/Graphics/maths/utilities.hpp>

#include <cstdlib>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>
#include <iostream>


namespace sf
{

template <typename T>
::std::ostream & operator << (::std::ostream & os, const Vector2<T> & object)
{
   os << "{" << object.x << ", " << object.y << "}";
   return os;
}

template <typename T>
::std::ostream & operator << (::std::ostream & os, const Vector3<T> & object)
{
   os << "{" << object.x << ", " << object.y << ", " << object.z << "}";
   return os;
}

}

namespace paercebal::Graphics::world
{

template <typename T>
struct AnythingPrinter
{
   AnythingPrinter(const T & t_) :t(t_) {}
   const T & t;
};

template <typename T>
inline AnythingPrinter<T> anythingPrinter(const T & t)
{
   return AnythingPrinter<T>(t);
}

template <typename T>
::std::ostream & operator << (::std::ostream & os, const AnythingPrinter<T> & object)
{
   os << object.t;
   return os;
}


inline ::std::ostream & operator << (::std::ostream & os, const Object::Positions & object)
{
   os << "{ ";

   for (const auto & position : object)
   {
      os << position;
   }

   os << " }";

   return os;
}

}

namespace paercebal::Graphics::world::tests
{

inline bool is_mostly_equal(float lhs, float rhs)
{
   return std::abs(lhs - rhs) < 10 * std::numeric_limits<float>::epsilon();
}

inline bool is_mostly_equal(double lhs, double rhs)
{
   return std::abs(lhs - rhs) < 10 * std::numeric_limits<double>::epsilon();
}

inline bool is_mostly_equal(long double lhs, long double rhs)
{
   return std::abs(lhs - rhs) < 10 * std::numeric_limits<long double>::epsilon();
}

template <typename T>
bool is_mostly_equal(const sf::Vector2<T> & lhs, const sf::Vector2<T> & rhs)
{
   return is_mostly_equal(lhs.x, rhs.x) && is_mostly_equal(lhs.y, rhs.y);
}

template <typename T>
bool is_mostly_equal(const sf::Vector3<T> & lhs, const sf::Vector3<T> & rhs)
{
   return is_mostly_equal(lhs.x, rhs.x) && is_mostly_equal(lhs.y, rhs.y) && is_mostly_equal(lhs.z, rhs.z);
}

template <typename T>
bool is_mostly_equal(const std::vector<sf::Vector3<T>> & lhs, const std::vector<sf::Vector3<T>> & rhs)
{
   return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](const sf::Vector3<T> & lhs, const sf::Vector3<T> & rhs) {return is_mostly_equal(lhs, rhs); });
}

} // namespace paercebal::Graphics::world::tests

#endif // PAERCEBAL_x_GRAPHICSTESTS_x_MAIN_x_HPP



