#ifndef PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_CIRCLE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_CIRCLE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::galaxy
{

enum class GalaxyCircleStyle
{
     Minor
   , Major
   , AxisX
   , AxisY
};


class PAERCEBAL_x_KIZUKOLIB_x_API GalaxyCircle : public objects::Object
{
   using super = objects::Object;
public:

   GalaxyCircle(const GlobalResources & globalResources, GalaxyCircleStyle style_, float radius);
   GalaxyCircle(const GlobalResources & globalResources, sf::Color color_, float radius);

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<GalaxyCircle> clone()                                         const;

private:
   virtual GalaxyCircle *        cloneImpl()                                     const override;

   float                         radius;
   sf::CircleShape               circle;
   sf::Color                     color;
};


} // namespace paercebal::KizukoLib::galaxy


#endif // PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_CIRCLE_x_HPP

