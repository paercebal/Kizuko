#ifndef PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_SPACE_TIME_LINE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_SPACE_TIME_LINE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/shapes/AbstractLine.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <array>

namespace paercebal::KizukoLib::shapes
{

enum class SpaceTimeStyle
{
   Minor
   , Major
};

inline sf::Color SpaceTimeStyleToColor(SpaceTimeStyle style)
{
   switch (style)
   {
      case SpaceTimeStyle::Major: return sf::Color{ 255, 255, 255, 64 };
      case SpaceTimeStyle::Minor: return sf::Color{ 255, 255, 255, 32 };
   }

   return sf::Color::White;
}

class SpaceTimeLine : public AbstractLine
{
   using super = AbstractLine;
public:
   SpaceTimeLine(const GlobalResources & globalResources_, SpaceTimeStyle style, sf::Vector3f begin3D_, sf::Vector3f end3D_);
};


inline SpaceTimeLine::SpaceTimeLine(const GlobalResources & globalResources_, SpaceTimeStyle style, sf::Vector3f begin3D_, sf::Vector3f end3D_)
   : super(globalResources_, SpaceTimeStyleToColor(style), begin3D_, end3D_)
{
}


} // namespace paercebal::KizukoLib::shapes





#endif // PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_SPACE_TIME_LINE_x_HPP

