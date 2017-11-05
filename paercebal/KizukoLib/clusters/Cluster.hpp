#ifndef PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_CLUSTER_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_CLUSTER_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/clusters/AltitudeLine.hpp>
#include <paercebal/KizukoLib/clusters/ClusterLine.hpp>
#include <paercebal/KizukoLib/clusters/DistanceShape.hpp>
#include <paercebal/KizukoLib/clusters/Star.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::clusters
{


class PAERCEBAL_x_KIZUKOLIB_x_API Cluster : public objects::Object
{
   using super = objects::Object;
public:

   Cluster(const GlobalResources & globalResources);
   Cluster(const GlobalResources & globalResources, float gridIncrement_, int gridMajorIncrement_, float scaling_, sf::Vector3f size3D_);

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<Cluster>      clone()                                         const;

   Cluster &                     addStar(const Star & star);
   Cluster &                     addDistance(const DistanceShape & distance);

private:
   virtual Cluster *             cloneImpl()                                     const override;

   sf::Vector3f                  size3D                  = { 100.f, 100.f, 100.f };
   float                         gridIncrement           = 2.f;
   int                           gridMajorIncrement      = 5;
   float                         scaling                 = 1.f;

   std::vector<ClusterLine *>    clusterLines;
   std::vector<DistanceShape *>  distanceShapes;
   std::vector<AltitudeLine *>   altitudeLine;
   std::vector<Star *>           stars;
};



} // namespace paercebal::KizukoLib::clusters





#endif // PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_CLUSTER_x_HPP

