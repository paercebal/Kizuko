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
void PrintTo(const Vector2<T> & object, ::std::ostream * os)
{
   *os << "{" << object.x << ", " << object.y << "}";
}

template <typename T>
void PrintTo(const Vector3<T> & object, ::std::ostream * os)
{
   *os << "{" << object.x << ", " << object.y << ", " << object.z << "}";
}

}

namespace paercebal::Graphics::world
{

//void PrintTo(const Object & object, ::std::ostream * os)
//{
//   *os << bar.DebugString();  // whatever needed to print bar to os
//}

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
bool is_mostly_equal(std::vector<sf::Vector3<T>> & lhs, std::vector<sf::Vector3<T>> & rhs)
{
   return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](const sf::Vector3<T> & lhs, const sf::Vector3<T> & rhs) {return is_mostly_equal(lhs, rhs); });
}


inline void initializeAbsolutePositions(Object & o)
{
   o.getAbsolutePositions() = o.getRelativePositions();
}

inline void rotateAbsolutePositionsAroundCenter(const Object & center, Object & o)
{
   for (const auto & rotation : center.getRelativeRotations())
   {
      for (auto & position : o.getAbsolutePositions())
      {
         position = rotation * position;
      }
   }
}

inline void translateAbsolutePositionToCenterCoordinates(const Object & center, Object & o)
{
   for (auto & position : o.getAbsolutePositions())
   {
      position += center.getCenter();
   }
}

inline void calculateAbsolutePosition(Object & o)
{
   rotateAbsolutePositionsAroundCenter(o, o);
   translateAbsolutePositionToCenterCoordinates(o, o);
}

inline void initializeAndCalculateAbsolutePosition(Object & o)
{
   initializeAbsolutePositions(o);
   calculateAbsolutePosition(o);
}

inline void initializeAbsolutePositionsOfCurrentAndDescendants(Object & o)
{
   for (auto & c : o.getChildren())
   {
      initializeAbsolutePositionsOfCurrentAndDescendants(*c);
   }

   initializeAbsolutePositions(o);
}

inline void RotateAndTranslateAbsolutePositionsOfObjectAccordingToAncestors(std::vector<Object *> & ancestors, Object & o)
{
   auto applyTranslateAndRotate = [&o](Object * origin)
   {
      rotateAbsolutePositionsAroundCenter(*origin, o);
      translateAbsolutePositionToCenterCoordinates(*origin, o);
   };

   std::for_each(ancestors.rbegin(), ancestors.rend(), applyTranslateAndRotate);
}

inline void RotateAndTranslateAbsolutePositionsOfObjectAndDescendantsAccordingToAncestors(std::vector<Object *> & ancestors, Object & o)
{
   ancestors.push_back(&o);

   for (auto & c : o.getChildren())
   {
      RotateAndTranslateAbsolutePositionsOfObjectAndDescendantsAccordingToAncestors(ancestors, *c);
   }

   RotateAndTranslateAbsolutePositionsOfObjectAccordingToAncestors(ancestors, o);

   ancestors.pop_back();
}

inline void RotateAndTranslateAbsolutePositionsOfDescendants(Object & o)
{
   std::vector<Object *> ancestors;
   ancestors.push_back(&o);

   for (auto & c : o.getChildren())
   {
      RotateAndTranslateAbsolutePositionsOfObjectAndDescendantsAccordingToAncestors(ancestors, *c);
   }
}

inline void calculateAbsolutePositionRecursive(Object & o)
{
   initializeAbsolutePositionsOfCurrentAndDescendants(o);
   RotateAndTranslateAbsolutePositionsOfDescendants(o);
}


} // namespace paercebal::Graphics::world::tests

#endif // PAERCEBAL_x_GRAPHICSTESTS_x_MAIN_x_HPP



