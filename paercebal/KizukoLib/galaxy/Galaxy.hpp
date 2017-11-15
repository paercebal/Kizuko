#ifndef PAERCEBAL_x_KIZUKOLIB_x_GALAXY_GALAXY_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GALAXY_GALAXY_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/galaxy/GalaxyLine.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::galaxy
{


class PAERCEBAL_x_KIZUKOLIB_x_API Galaxy : public objects::Object
{
   using super = objects::Object;
public:

   Galaxy(const GlobalResources & globalResources);
   Galaxy(const GlobalResources & globalResources, float gridIncrement_, int gridMajorIncrement_, float scaling_, sf::Vector3f size3D_);

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<Galaxy>       clone()                                         const;

   //Galaxy &                      addStar(const Star & star);
   //Galaxy &                      addDistance(const DistanceShape & distance);

private:
   virtual Galaxy *              cloneImpl()                                     const override;

   sf::Vector3f                  size3D                  = { 100.f, 100.f, 100.f };
   float                         gridIncrement           = 2.f;
   int                           gridMajorIncrement      = 5;
   float                         scaling                 = 1.f;

   std::vector<GalaxyLine *>     galaxyLines;
   //std::vector<DistanceShape *>  distanceShapes;
   //std::vector<AltitudeLine *>   altitudeLine;
   //std::vector<Star *>           stars;
};



} // namespace paercebal::KizukoLib::galaxy





#endif // PAERCEBAL_x_KIZUKOLIB_x_GALAXY_GALAXY_x_HPP

