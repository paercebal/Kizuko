#ifndef PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_VIEW_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_VIEW_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/clusters/Object.hpp>
#include <paercebal/KizukoLib/clusters/Cluster.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::clusters
{


class PAERCEBAL_x_KIZUKOLIB_x_API View : public Object
{
   using super = Object;
public:

   View(const GlobalResources & globalResources);

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<View>         clone()                                         const;

   View &                        translateXPositive();
   View &                        translateYPositive();
   View &                        translateXNegative();
   View &                        translateYNegative();
   View &                        zoomIn();
   View &                        zoomOut();

private:
   View(const GlobalResources & globalResources, float translationIncrement_);

   virtual View *                cloneImpl()                                     const override;

   View &                        updateTranslation();
   View &                        updateZoom();

   Cluster *                     cluster              = nullptr;
   float                         translationIncrement = 10.f;
   int                           translationX         = 0;
   int                           translationY         = 0;
   int                           zoomPosition         = 0;
   float                         zoom                 = 100.f;

   sf::Text                      debugLabel;
   std::string                   debugText;
};



} // namespace paercebal::KizukoLib::clusters





#endif // PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_VIEW_x_HPP

