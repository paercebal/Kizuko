#ifndef PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_DISTANCE_LINE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_DISTANCE_LINE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/shapes/AbstractLine.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <array>

namespace paercebal::KizukoLib::shapes
{

class DistanceLine : public AbstractLine
{
   using super = AbstractLine;
public:
   DistanceLine(const GlobalResources & globalResources_, const std::string & beginName_, const std::string & endName_);

   const std::string &        getBeginName() const;
   const std::string &        getEndName() const;

private:
   std::string beginName;
   std::string endName;
};


inline DistanceLine::DistanceLine(const GlobalResources & globalResources_, const std::string & beginName_, const std::string & endName_)
   : super(globalResources_, sf::Color{ 128, 128, 128, 128 })
   , beginName(beginName_)
   , endName(endName_)
{
}


inline const std::string & DistanceLine::getBeginName() const
{
   return this->beginName;
}

inline const std::string & DistanceLine::getEndName() const
{
   return this->endName;
}



} // namespace paercebal::KizukoLib::shapes





#endif // PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_DISTANCE_LINE_x_HPP

