#ifndef PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_VIEW_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_VIEW_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/galaxy/Galaxy.hpp>
#include <paercebal/KizukoLib/gui/View.hpp>
#include <paercebal/KizukoLib/gui/Button.hpp>
#include <paercebal/KizukoLib/gui/Label.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <string>
#include <sstream>


namespace paercebal::KizukoLib::galaxy
{


struct GalaxyViewCommands
{
   using Command = std::function<void()>;

   Command onBack;
};


class PAERCEBAL_x_KIZUKOLIB_x_API GalaxyView : public objects::Object, public gui::View
{
   using super = objects::Object;
public:

   GalaxyView(const GlobalResources & globalResources, GalaxyViewCommands galaxyViewCommands);

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<GalaxyView>   clone()                                         const;

   GalaxyView &                  translateXPositive();
   GalaxyView &                  translateYPositive();
   GalaxyView &                  translateXNegative();
   GalaxyView &                  translateYNegative();
   GalaxyView &                  translateByPixels(int x, int y);
   GalaxyView &                  zoomIn();
   GalaxyView &                  zoomOut();
   GalaxyView &                  zoomInByWheel();
   GalaxyView &                  zoomOutByWheel();

   GalaxyView &                  setDebugText(const std::string & debugText_);
   GalaxyView &                  setDebugText(std::string && debugText_);

   GalaxyView &                  setChanged(bool isChanged);
   bool                          isChanged()                                     const;

   GalaxyView &                  setView(const sf::View & view);

   virtual void                  warnMouseHovering(int x, int y)                                      override;
   virtual void                  warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)       override;
   virtual void                  warnLoseFocus()                                                      override;

   virtual void                  calculateAbsolutePositionThenShapes2DRecursiveIfNeeded() override;

private:
   GalaxyView(const GlobalResources & globalResources, GalaxyViewCommands galaxyViewCommands, float translationIncrement_);

   virtual GalaxyView *          cloneImpl()                                     const override;

   GalaxyView &                  updateTranslation();
   GalaxyView &                  updateZoom();

   bool                          isChanged_              = true;
   galaxy::Galaxy *              galaxy                  = nullptr;
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

   GalaxyViewCommands            commands;
   gui::Button                   button;
   gui::Label                    label;

   sf::Texture                   spaceBackground;
   sf::Sprite                    spaceBackgroundSprite;
   bool                          isSpaceBackgroundVisible = false;
};

//PAERCEBAL_x_KIZUKOLIB_x_API void calculateAbsolutePositionThenShapes2DRecursiveIfNeeded(GalaxyView & view);


} // namespace paercebal::KizukoLib::galaxy





#endif // PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_VIEW_x_HPP

