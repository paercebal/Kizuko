#ifndef PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_LINE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_LINE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::galaxy
{

enum class GalaxyLineStyle
{
     Minor
   , Major
   , AxisX
   , AxisY
};


class PAERCEBAL_x_KIZUKOLIB_x_API GalaxyLine : public objects::Object
{
   using super = objects::Object;
public:

   GalaxyLine(const GlobalResources & globalResources, GalaxyLineStyle style_, sf::Vector3f begin_, sf::Vector3f end_);
   GalaxyLine(const GlobalResources & globalResources, sf::Color color_, sf::Vector3f begin_, sf::Vector3f end_);

   sf::Vector3f                  getBegin3D()                                    const noexcept;
   sf::Vector3f                  getEnd3D()                                      const noexcept;
   sf::Color                     getColor()                                      const noexcept;

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<GalaxyLine>   clone()                                         const;

private:
   virtual GalaxyLine *          cloneImpl()                                     const override;

   std::array<sf::Vertex, 2>     line2D;
   sf::Color                     color;
};


} // namespace paercebal::KizukoLib::galaxy


#endif // PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_LINE_x_HPP

