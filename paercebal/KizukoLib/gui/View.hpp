#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_VIEW_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_VIEW_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/galaxy/Galaxy.hpp>
#include <paercebal/KizukoLib/gui/Control.hpp>
#include <paercebal/KizukoLib/gui/ObserverWidgetGui.hpp>
#include <paercebal/KizukoLib/gui/ObserverWidget3D.hpp>
#include <paercebal/KizukoLib/gui/Button.hpp>
#include <paercebal/KizukoLib/gui/Label.hpp>


#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <string>
#include <sstream>


namespace paercebal::KizukoLib::gui
{


class PAERCEBAL_x_KIZUKOLIB_x_API View : public objects::Object, public ObserverWidgetGui, public ObserverWidget3D
{
   using super = objects::Object;
public:
   View(const GlobalResources & globalResources_, float translationIncrement_);
   virtual ~View();

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

   virtual void                  registerWidget3D(Control & control)                   override;
   virtual void                  unregisterWidget3D(Control & control)                 override;
   virtual void                  registerWidgetGui(Control & control)                  override;
   virtual void                  unregisterWidgetGui(Control & control)                override;

   View &                                 setChanged(bool isChanged);
   bool                                   isChanged()                                     const;

   virtual View &                        setView(const sf::View & view);

   virtual void                          warnViewAboutMouseHovering(int x, int y);
   virtual void                          warnViewAboutMouseClicking(sf::Vector2i pressed, sf::Vector2i released);
   virtual void                          warnViewAboutLoseFocus();

   void                          calculateAbsolutePositionThenShapes2DRecursiveIfNeeded();

protected:

   View &                        setViewedObject(std::unique_ptr<objects::Object> viewedObject_);
   View &                        updateTranslation();
   View &                        updateZoom();

   bool                          isChanged_ = true;
   objects::Object *             viewedObject = nullptr;
   float                         translationIncrement = 10.f;
   int                           translationIncrementX = 0;
   int                           translationIncrementY = 0;
   int                           translationX = 0;
   int                           translationY = 0;
   int                           zoomPosition = 0;
   float                         zoom = 100.f;

   sf::Vector2f                  viewSize;
   sf::Vector2f                  viewCenter;

   sf::Text                      debugLabel;
   std::string                   debugText;

   sf::Texture                   spaceBackground;
   sf::Sprite                    spaceBackgroundSprite;
   bool                          isSpaceBackgroundVisible = false;

private:

   virtual View *                cloneImpl()                                     const = 0;

   std::set<Control *>           widget3D;
   std::set<Control *>           widgetGui;

protected:
   View(const View &) = default;
   View & operator = (const View &) = default;
   View(View &&) = default;
   View & operator = (View &&) = default;
};

} // namespace paercebal::KizukoLib::gui





#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_VIEW_x_HPP

