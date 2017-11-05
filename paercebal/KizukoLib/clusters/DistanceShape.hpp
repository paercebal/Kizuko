#ifndef PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_DISTANCE_SHAPE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_DISTANCE_SHAPE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::clusters
{

class PAERCEBAL_x_KIZUKOLIB_x_API DistanceShape : public objects::Object
{
   using super = objects::Object;
public:

   DistanceShape(const GlobalResources & globalResources_, const std::string & beginName_, const std::string & endName_);
   DistanceShape(const GlobalResources & globalResources_, sf::Color colorLine_, sf::Color colorBaseLine_, sf::Color colorShape_, const std::string & beginName_, const std::string & endName_);

   //sf::Vector3f                     getBegin3D()                                    const noexcept;
   //sf::Vector3f                     getEnd3D()                                      const noexcept;
   //sf::Color                        getColor()                                      const noexcept;

   const std::string &              getBeginName() const;
   const std::string &              getEndName() const;

   DistanceShape &                  setBeginAndEnd(sf::Vector3f begin3D_, sf::Vector3f end3D_);

   virtual void                     createShapes2D()                                      override;
   virtual void                     drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<DistanceShape>   clone()                                         const;

private:
   virtual DistanceShape *          cloneImpl()                                     const override;

   sf::ConvexShape                  polygonShape;
   std::array<sf::Vertex, 4>        polygon2D;
   sf::Vector2f                     center2D;
   sf::Color                        colorShape;
   sf::Color                        colorLine;
   sf::Color                        colorBaseLine;
   float                            lightYearsLength = 0;
   std::string                      distanceText;
   sf::Text                         distanceLabel;

   std::string                      beginName;
   std::string                      endName;
};


} // namespace paercebal::KizukoLib::clusters


#endif // PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_DISTANCE_SHAPE_x_HPP

