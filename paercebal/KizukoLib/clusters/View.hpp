#ifndef PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_VIEW_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_VIEW_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/clusters/Cluster.hpp>
#include <paercebal/KizukoLib/gui/Button.hpp>
#include <paercebal/KizukoLib/gui/Label.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <string>
#include <sstream>


namespace paercebal::KizukoLib::clusters
{


class PAERCEBAL_x_KIZUKOLIB_x_API View : public objects::Object
{
   using super = objects::Object;
public:

   View(const GlobalResources & globalResources);

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<View>         clone()                                         const;

   View &                        translateXPositive();
   View &                        translateYPositive();
   View &                        translateXNegative();
   View &                        translateYNegative();
   View &                        translateByPixels(int x, int y);
   View &                        zoomIn();
   View &                        zoomOut();
   View &                        zoomInByWheel();
   View &                        zoomOutByWheel();

   View &                        setDebugText(const std::string & debugText_);
   View &                        setDebugText(std::string && debugText_);

   View &                        setChanged(bool isChanged);
   bool                          isChanged()                                     const;

   View &                        setView(const sf::View & view);

   void                          warnMouseHovering(int x, int y);
   void                          warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released);

private:
   View(const GlobalResources & globalResources, float translationIncrement_);

   virtual View *                cloneImpl()                                     const override;

   View &                        updateTranslation();
   View &                        updateZoom();

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

   gui::Button                   button;
   gui::Label                    label;

   sf::Texture                   spaceBackground;
   sf::Sprite                    spaceBackgroundSprite;
   bool                          isSpaceBackgroundVisible = false;
};

PAERCEBAL_x_KIZUKOLIB_x_API void calculateAbsolutePositionThenShapes2DRecursiveIfNeeded(View & view);


} // namespace paercebal::KizukoLib::clusters





#endif // PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_VIEW_x_HPP

