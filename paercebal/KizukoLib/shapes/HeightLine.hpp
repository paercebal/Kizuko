#ifndef PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_HEIGHT_LINE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_HEIGHT_LINE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/shapes/AbstractLine.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <array>

namespace paercebal::KizukoLib::shapes
{

class HeightLine : public AbstractLine
{
   using super = AbstractLine;
public:
   HeightLine(const GlobalResources & globalResources_, sf::Color starColor, sf::Vector3f starCenter);
};


inline HeightLine::HeightLine(const GlobalResources & globalResources_, sf::Color starColor, sf::Vector3f starCenter)
   : super(globalResources_, sf::Color{ starColor.r, starColor.g, starColor.b, 128 }, starCenter, sf::Vector3f{ starCenter.x, starCenter.y, 0 })
{
}


} // namespace paercebal::KizukoLib::shapes





#endif // PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_HEIGHT_LINE_x_HPP

