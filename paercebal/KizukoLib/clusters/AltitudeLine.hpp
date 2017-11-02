#ifndef PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_ALTITUDE_LINE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_ALTITUDE_LINE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/clusters/Object.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::clusters
{

class PAERCEBAL_x_KIZUKOLIB_x_API AltitudeLine : public Object
{
   using super = Object;
public:

   AltitudeLine(const GlobalResources & globalResources, sf::Vector3f starCenter);

   sf::Vector3f                     getBegin3D()                                    const noexcept;
   sf::Vector3f                     getEnd3D()                                      const noexcept;
   sf::Color                        getColor()                                      const noexcept;

   virtual void                     createShapes2D()                                      override;
   virtual void                     drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<AltitudeLine>    clone()                                         const;

private:
   virtual AltitudeLine *           cloneImpl()                                     const override;

   std::array<sf::Vertex, 2>        line2D;
   sf::Color                        color;
};


} // namespace paercebal::KizukoLib::clusters


#endif // PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_ALTITUDE_LINE_x_HPP

