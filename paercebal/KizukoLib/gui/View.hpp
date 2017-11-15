#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_VIEW_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_VIEW_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/galaxy/Galaxy.hpp>
#include <paercebal/KizukoLib/gui/Button.hpp>
#include <paercebal/KizukoLib/gui/Label.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <string>
#include <sstream>


namespace paercebal::KizukoLib::gui
{


class PAERCEBAL_x_KIZUKOLIB_x_API View
{
public:

   virtual void                  createShapes2D()                                      = 0;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const = 0;
   std::unique_ptr<View>         clone()                                         const;

   virtual View &                translateXPositive()                                  = 0;
   virtual View &                translateYPositive()                                  = 0;
   virtual View &                translateXNegative()                                  = 0;
   virtual View &                translateYNegative()                                  = 0;
   virtual View &                translateByPixels(int x, int y)                       = 0;
   virtual View &                zoomIn()                                              = 0;
   virtual View &                zoomOut()                                             = 0;
   virtual View &                zoomInByWheel()                                       = 0;
   virtual View &                zoomOutByWheel()                                      = 0;

   virtual View &                setDebugText(const std::string & debugText_)          = 0;
   virtual View &                setDebugText(std::string && debugText_)               = 0;

   virtual View &                setChanged(bool isChanged)                            = 0;
   virtual bool                  isChanged()                                     const = 0;

   virtual View &                setView(const sf::View & view)                        = 0;

   virtual void                  warnMouseHovering(int x, int y)                       = 0;
   virtual void                  warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released) = 0;
   virtual void                  warnLoseFocus()                                       = 0;

   virtual void                  calculateAbsolutePositionThenShapes2DRecursiveIfNeeded() = 0;

private:

   virtual View *                cloneImpl()                                     const = 0;

protected:
   View() = default;
   View(const View &) = default;
   View & operator = (const View &) = default;
   View(View &&) = default;
   View & operator = (View &&) = default;
};

} // namespace paercebal::KizukoLib::gui





#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_VIEW_x_HPP

