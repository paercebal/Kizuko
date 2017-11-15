#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_WIDGET_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_WIDGET_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <functional>


namespace paercebal::KizukoLib::gui
{

enum class RelativePositionStyle
{
   Center
   , CenterLeft
   , CenterRight
   , TopCenter
   , BottomCenter
   , TopLeft
   , TopRight
   , BottomLeft
   , BottomRight
};

struct WidgetStyle
{
   struct Area
   {
      sf::Color background = {};
      sf::Color outline = {};
      float outlineThickness = {};
   };

   struct Font
   {
      sf::Color foreground = {};
      sf::Color outline = {};
      float outlineThickness = {};
      sf::Uint32 style = sf::Text::Regular;
   };

   Area area;
   Font font;
};

struct WidgetStyles
{
   WidgetStyle normal;
   WidgetStyle hover;
};

class PAERCEBAL_x_KIZUKOLIB_x_API Widget
{
public:

   using CommandCallback = std::function<void(void)>;

protected:
   Widget(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_);
   Widget(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, const WidgetStyles & widgetStyles_);
   Widget(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, const WidgetStyles & widgetStyles_, CommandCallback commandCallback_);

public:
   void                          createShapes2D();
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const = 0;
   std::unique_ptr<Widget>       clone()                                         const;

   const GlobalResources &       getGlobalResources()                            const;

   Widget &                      setCommand(CommandCallback commandCallback);
   Widget &                      setPosition(RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition);
   Widget &                      setStyle(const WidgetStyles & widgetStyles);

   Widget &                      setChanged(bool isChanged);
   bool                          isChanged()                                     const;

   Widget &                      setView(const sf::View & view);

   sf::FloatRect                 getWidgetBounds()                               const;
   bool                          isMouseHovering()                               const;

   void                          warnMouseHovering(int x, int y);
   void                          warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released);
   void                          warnLoseFocus();

protected:
   Widget &                      setSize(const sf::Vector2f & size);

private:
   virtual Widget *              cloneImpl()                                     const = 0;

   virtual void                  createShapes2DFirstWhenChanged()                      = 0;
   virtual void                  createShapes2DSecondAlways()                          = 0;

protected:

   void                          calculateAbsolutePosition();

   const GlobalResources &       globalResources;
   RelativePositionStyle         relativePositionStyle = RelativePositionStyle::Center;
   sf::Vector2f                  relativePosition = {};
   sf::Vector2f                  absolutePosition = {};
   sf::Vector2f                  size = {};
   bool                          changed = true;
   WidgetStyles                  styles;
   CommandCallback               commandCallback;

   sf::Vector2f                  viewSize;
   sf::Vector2f                  viewCenter;
   sf::Vector2i                  viewMousePosition;
};


} // namespace paercebal::KizukoLib::gui

#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_WIDGET_x_HPP

