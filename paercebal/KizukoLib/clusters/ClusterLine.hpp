#ifndef PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_CLUSTER_LINE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_CLUSTER_LINE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/clusters/Object.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::clusters
{

enum class ClusterLineStyle
{
     Minor
   , Major
   , AxisX
   , AxisY
};


class PAERCEBAL_x_KIZUKOLIB_x_API ClusterLine : public Object
{
   using super = Object;
public:

   ClusterLine(const GlobalResources & globalResources, ClusterLineStyle style_, sf::Vector3f begin_, sf::Vector3f end_);
   ClusterLine(const GlobalResources & globalResources, sf::Color color_, sf::Vector3f begin_, sf::Vector3f end_);

   sf::Vector3f                  getBegin3D()                                    const noexcept;
   sf::Vector3f                  getEnd3D()                                      const noexcept;
   sf::Color                     getColor()                                      const noexcept;

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<ClusterLine>  clone()                                         const;

private:
   virtual ClusterLine *         cloneImpl()                                     const override;

   std::array<sf::Vertex, 2>     line2D;
   sf::Color                     color;
};


} // namespace paercebal::KizukoLib::clusters


#endif // PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_CLUSTER_LINE_x_HPP

