#ifndef PAERCEBAL_x_KIZUKOLIB_x_GALAXY_GALAXY_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GALAXY_GALAXY_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/galaxy/GalaxyCircle.hpp>
#include <paercebal/KizukoLib/galaxy/GalaxyLine.hpp>
#include <paercebal/KizukoLib/galaxy/GalaxyCluster.hpp>
#include <paercebal/KizukoLib/gui/ObserverWidget3D.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/objects/FlatImage.hpp>


#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::galaxy
{

struct GalaxyCommands
{
   std::function<void(const std::string &)> onSelectCluster;
};


class PAERCEBAL_x_KIZUKOLIB_x_API Galaxy : public objects::Object, public gui::Control
{
   using super = objects::Object;
public:

   Galaxy(const GlobalResources & globalResources, GalaxyCommands galaxyCommands_, gui::ObserverWidget3D & observerWidget3D_);
   Galaxy(const GlobalResources & globalResources, GalaxyCommands galaxyCommands_, gui::ObserverWidget3D & observerWidget3D_, float gridIncrement_, int gridMajorIncrement_, float scaling_, float radius_);
   virtual ~Galaxy();

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<Galaxy>       clone()                                         const;

   //Galaxy &                      addStar(const Star & star);
   //Galaxy &                      addDistance(const DistanceShape & distance);
   Galaxy &                      addCluster(const GalaxyCluster & cluster);

   bool                          isBackgroundImageVisible()                      const;
   Galaxy &                      setBackgroundImageVisible(bool visible);

   void                          registerIntoObserver(gui::ObserverWidget3D & observerWidget3D_);
   void                          unregisterFromObserver();

   void                          onSelectCluster(const std::string & clusterName);

private:
   virtual Galaxy *              cloneImpl()                                     const override;

   GalaxyCommands                galaxyCommands;
   float                         radius                  = 100.f;
   float                         gridIncrement           = 2.f;
   int                           gridMajorIncrement      = 5;
   float                         scaling                 = 1.f;

   gui::ObserverWidget3D *       observerWidget3D = nullptr;
   objects::FlatImage *          milkyWayImage = nullptr;
   std::vector<GalaxyLine *>     galaxyLines;
   std::vector<GalaxyCircle *>   galaxyCircles;
   //std::vector<DistanceShape *>  distanceShapes;
   //std::vector<AltitudeLine *>   altitudeLine;
   std::vector<GalaxyCluster *>  clusters;
};



} // namespace paercebal::KizukoLib::galaxy





#endif // PAERCEBAL_x_KIZUKOLIB_x_GALAXY_GALAXY_x_HPP

