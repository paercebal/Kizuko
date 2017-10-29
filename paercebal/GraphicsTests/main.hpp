#ifndef PAERCEBAL_x_GRAPHICSTESTS_x_MAIN_x_HPP
#define PAERCEBAL_x_GRAPHICSTESTS_x_MAIN_x_HPP

#include <paercebal/Graphics/world/DefaultObject.hpp>
#include <paercebal/Graphics/maths/utilities.hpp>

#include <cstdlib>
#include <cmath>
#include <limits>


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
bool is_mostly_equal(std::vector<sf::Vector3<T>> & lhs, std::vector<sf::Vector3<T>> & rhs)
{
   return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](const sf::Vector3<T> & lhs, const sf::Vector3<T> & rhs) {return is_mostly_equal(lhs, rhs); });
}


inline void calculateAbsolutePosition(DefaultObject & o)
{
   o.resetAbsolutePositions();
   auto & absolute = o.getAbsolutePositions();

   // Initialization
   {
      auto itS = begin(o.getRelativePositions()), itSEnd = end(o.getRelativePositions());
      auto itD = begin(o.getAbsolutePositions()), itDEnd = end(o.getAbsolutePositions());

      for (; (itS != itSEnd) && (itD != itDEnd); ++itS, ++itD)
      {
         *itD += *itS;
      }
   }

   // Rotation
   {
      auto itR = begin(o.getRelativeRotations()), itREnd = end(o.getRelativeRotations());

      for (; itR != itREnd; ++itR)
      {
         auto itD = begin(o.getAbsolutePositions()), itDEnd = end(o.getAbsolutePositions());

         for (; itD != itDEnd; ++itD)
         {
            {
               const maths::Matrix3D<float> & rotation = *itR;
               sf::Vector3f & position = *itD;

               position = rotation * position;
            }
         }
      }
   }

   // Translation
   {
      auto itD = begin(o.getAbsolutePositions()), itDEnd = end(o.getAbsolutePositions());

      for (; itD != itDEnd; ++itD)
      {
         *itD += o.getCenter();
      }
   }
}

} // namespace paercebal::Graphics::world::tests

#endif // PAERCEBAL_x_GRAPHICSTESTS_x_MAIN_x_HPP



