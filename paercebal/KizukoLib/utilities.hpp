#ifndef PAERCEBAL_x_KIZUKOLIB_x_UTILITIES_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_UTILITIES_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>

#include <paercebal/Graphics/maths/Matrix3D.hpp>
#include <paercebal/Graphics/maths/utilities.hpp>
#include <paercebal/KizukoLib/Exception.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
#include <fstream>
#include <string>

#define PAERCEBAL_x_KIZUKOLIB_x_ASSERT_POINTER_IS_NOT_NULL(p) assertPointIsNotNull(p, paercebal::KizukoLib::utilities::SeparatorTypeForMacros(), __FUNCTION__, __FILE__, __LINE__)
#define PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(...) assertResourceLoading(__VA_ARGS__, paercebal::KizukoLib::utilities::SeparatorTypeForMacros(), __FUNCTION__, __FILE__, __LINE__)

namespace paercebal::KizukoLib::utilities
{

struct SeparatorTypeForMacros {};

template <typename T>
void assertPointIsNotNull(const T * t, SeparatorTypeForMacros, const char * function, const char * file, const int line)
{
   if (t == nullptr)
   {
      throw ResourceLoadingException() << "Pointer is null at file " << file << " (line: " << line << ")";
   }
}

namespace private_
{

template <typename T>
bool loadResourceFromFile(T & t, const std::string & path)
{
   return t.loadFromFile(path);
}

inline bool loadResourceFromFile(sf::Music & t, const std::string & path)
{
   return t.openFromFile(path);
}

template <typename T>
void initializeResourceWithDefaultParameters(T & t)
{
}

inline void initializeResourceWithDefaultParameters(sf::Music & t)
{
   t.setPosition(0, 0, 0);    // change its 3D position
   t.setPitch(1);             // increase the pitch
   t.setVolume(50);           // reduce the volume
   t.setLoop(true);           // make it loop
}

}

template <typename T>
void assertResourceLoading(T & t, const std::string & path, SeparatorTypeForMacros, const char * function, const char * file, const int line)
{
   using private_::loadResourceFromFile;
   using private_::initializeResourceWithDefaultParameters;

   if (!loadResourceFromFile(t, path))
   {
      throw ResourceLoadingException() << "Failed to load resource\"" << path << "\" at file " << file << " (line: " << line << ")";
   }

   initializeResourceWithDefaultParameters(t);
}

template <typename T>
void assertResourceLoading(T & t, const std::string & path, const std::string & pathForError, SeparatorTypeForMacros, const char * function, const char * file, const int line)
{
   using private_::loadResourceFromFile;
   using private_::initializeResourceWithDefaultParameters;

   if (!loadResourceFromFile(t, path))
   {
      if (!loadResourceFromFile(t, pathForError))
      {
         throw ResourceLoadingException() << "Failed to load resource\"" << path << "\", and even its replacement \"" << pathForError << "\" at file " << file << " (line: " << line << ")";
      }
   }

   initializeResourceWithDefaultParameters(t);
}

template <typename T>
void assertResourceLoading(T & t, const std::string & copyrightedPath, const std::string & path, const std::string & pathForError, SeparatorTypeForMacros, const char * function, const char * file, const int line)
{
   using private_::loadResourceFromFile;
   using private_::initializeResourceWithDefaultParameters;

   if (!loadResourceFromFile(t, copyrightedPath))
   {
      if (!loadResourceFromFile(t, path))
      {
         if (!loadResourceFromFile(t, pathForError))
         {
            throw ResourceLoadingException() << "Failed to load copyrighted resource\"" << copyrightedPath << "\", its free resource\"" << path << "\", and even its replacement \"" << pathForError << "\" at file " << file << " (line: " << line << ")";
         }
      }
   }

   initializeResourceWithDefaultParameters(t);
}

template <typename T>
inline Graphics::maths::Matrix3D<T> createRotationToIsometricMatrix()
{
   static const T pi = Graphics::maths::utilities::pi<T>;
   static const auto firstAngle = pi / 4;
   static const auto secondAngle = pi / 3;

   static const auto identity = Graphics::maths::utilities::createIdentityMatrix<T>();
   static const auto mirrorMatrix = Graphics::maths::utilities::createMirrorMatrixAroundY<T>();
   static const auto firstMatrix = Graphics::maths::utilities::createRotationMatrixAroundZ(firstAngle);
   static const auto secondMatrix = Graphics::maths::utilities::createRotationMatrixAroundX(secondAngle);
   static const auto isoMatrix = secondMatrix * firstMatrix * mirrorMatrix * identity;

   return isoMatrix;
}

inline sf::Vector2<long double> convert_3D_to_iso2D(const sf::Vector3<long double> value)
{
   static const auto isoMatrix = createRotationToIsometricMatrix<long double>();

   const auto resultDouble = isoMatrix * value;

   return { resultDouble.x, resultDouble.y };
}

template <typename T>
sf::Vector2<T> convert_3D_to_iso2D(const sf::Vector3<T> value)
{
   const auto valueDouble = sf::Vector3<long double>{ value.x, value.y, value.z };
   const auto resultDouble = convert_3D_to_iso2D(valueDouble);

   return { static_cast<T>(resultDouble.x), static_cast<T>(resultDouble.y) };
}

inline sf::Vector3<long double> getBarycenter(const sf::Vector3<long double> begin_, const sf::Vector3<long double> end_, long double relativePosition)
{
   auto result = (begin_ + end_) * relativePosition;
   return result;
}

template <typename T>
sf::Vector3<T> getBarycenter(const sf::Vector3<T> begin_, const sf::Vector3<T> end_, long double relativePosition)
{
   const auto beginDouble = sf::Vector3<long double>{ begin_.x, begin_.y, begin_.z };
   const auto endDouble = sf::Vector3<long double>{ end_.x, end_.y, end_.z };
   const auto resultDouble = getBarycenter(beginDouble, endDouble, relativePosition);

   return { static_cast<T>(resultDouble.x), static_cast<T>(resultDouble.y), static_cast<T>(resultDouble.z) };
}

inline long double getDistance(const sf::Vector3<long double> begin_, const sf::Vector3<long double> end_)
{
   auto result = std::sqrt(std::pow(end_.x - begin_.x, 2.) + std::pow(end_.y - begin_.y, 2.) + std::pow(end_.z - begin_.z, 2.));
   return result;
}

template <typename T>
T getDistance(const sf::Vector3<T> begin_, const sf::Vector3<T> end_)
{
   const auto beginDouble = sf::Vector3<long double>{ begin_.x, begin_.y, begin_.z };
   const auto endDouble = sf::Vector3<long double>{ end_.x, end_.y, end_.z };
   const auto resultDouble = getDistance(beginDouble, endDouble);

   return static_cast<T>(resultDouble);
}

inline std::string loadFile(const std::string & filename)
{
   std::fstream file(filename, std::ios_base::in);
   std::string content;
   std::istream_iterator<char> it(file), itEnd;
   std::copy(it, itEnd, std::insert_iterator<std::string>(content, content.end()));
   return content;
}


} // namespace paercebal::KizukoLib::utilities


#endif // PAERCEBAL_x_KIZUKOLIB_x_UTILITIES_x_HPP
