#ifndef PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_CLUSTER_VIEW_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_CLUSTER_VIEW_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/clusters/Cluster.hpp>
#include <paercebal/KizukoLib/gui/Button.hpp>
#include <paercebal/KizukoLib/gui/Label.hpp>
#include <paercebal/KizukoLib/gui/View.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <functional>


namespace paercebal::KizukoLib::clusters
{

struct ClusterViewCommands
{
   using Command = std::function<void()>;

   Command onBack;
};


class PAERCEBAL_x_KIZUKOLIB_x_API ClusterView : public objects::Object, public gui::View
{
   using super = objects::Object;
public:

   ClusterView(const GlobalResources & globalResources, ClusterViewCommands clusterViewCommands);

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<ClusterView>  clone()                                         const;

   ClusterView &                 translateXPositive();
   ClusterView &                 translateYPositive();
   ClusterView &                 translateXNegative();
   ClusterView &                 translateYNegative();
   ClusterView &                 translateByPixels(int x, int y);
   ClusterView &                 zoomIn();
   ClusterView &                 zoomOut();
   ClusterView &                 zoomInByWheel();
   ClusterView &                 zoomOutByWheel();

   ClusterView &                 setDebugText(const std::string & debugText_);
   ClusterView &                 setDebugText(std::string && debugText_);

   ClusterView &                 setChanged(bool isChanged);
   bool                          isChanged()                                     const;

   ClusterView &                 setView(const sf::View & view);

   virtual void                  warnMouseHovering(int x, int y)                                      override;
   virtual void                  warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)       override;
   virtual void                  warnLoseFocus()                                                      override;

   virtual void                  calculateAbsolutePositionThenShapes2DRecursiveIfNeeded() override;

private:
   ClusterView(const GlobalResources & globalResources, ClusterViewCommands clusterViewCommands, float translationIncrement_);

   virtual ClusterView *         cloneImpl()                                     const override;

   ClusterView &                 updateTranslation();
   ClusterView &                 updateZoom();

   bool                          isChanged_              = true;
   clusters::Cluster *           cluster                 = nullptr;
   float                         translationIncrement    = 10.f;
   int                           translationIncrementX   = 0;
   int                           translationIncrementY   = 0;
   int                           translationX            = 0;
   int                           translationY            = 0;
   int                           zoomPosition            = 0;
   float                         zoom                    = 100.f;

   sf::Vector2f                  viewSize;
   sf::Vector2f                  viewCenter;

   sf::Text                      debugLabel;
   std::string                   debugText;

   ClusterViewCommands           commands;
   gui::Button                   button;
   gui::Label                    label;
   gui::Label                    milkyWay;

   sf::Texture                   spaceBackground;
   sf::Sprite                    spaceBackgroundSprite;
   bool                          isSpaceBackgroundVisible = false;
};

//PAERCEBAL_x_KIZUKOLIB_x_API void calculateAbsolutePositionThenShapes2DRecursiveIfNeeded(ClusterView & view);


} // namespace paercebal::KizukoLib::clusters





#endif // PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_CLUSTER_VIEW_x_HPP

