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


class PAERCEBAL_x_KIZUKOLIB_x_API ClusterView : public gui::View
{
   using super = gui::View;
public:

   ClusterView(const GlobalResources & globalResources, ClusterViewCommands clusterViewCommands);

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<ClusterView>  clone()                                         const;

   virtual ClusterView &                 setView(const sf::View & view);

   virtual void                          warnMouseHovering(int x, int y);
   virtual void                          warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released);
   virtual void                          warnLoseFocus();

private:
   ClusterView(const GlobalResources & globalResources, ClusterViewCommands clusterViewCommands, float translationIncrement_);

   virtual ClusterView *         cloneImpl()                                     const override;

   ClusterViewCommands           commands;
   gui::Button                   button;
   gui::Label                    label;
   gui::Label                    milkyWay;
};

//PAERCEBAL_x_KIZUKOLIB_x_API void calculateAbsolutePositionThenShapes2DRecursiveIfNeeded(ClusterView & view);


} // namespace paercebal::KizukoLib::clusters





#endif // PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_CLUSTER_VIEW_x_HPP

