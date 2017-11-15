#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_BUTTON_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_BUTTON_x_HPP

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


class PAERCEBAL_x_KIZUKOLIB_x_API Button
{
public:

   using CommandCallback = std::function<void(void)>;

   Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_);
   Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_, const WidgetStyles & widgetStyles_);
   Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_, const WidgetStyles & widgetStyles_, CommandCallback commandCallback_);

   virtual void                  createShapes2D();
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const;
   std::unique_ptr<Button>       clone()                                         const;

   const GlobalResources &       getGlobalResources()                            const;

   Button &                      setCommand(CommandCallback commandCallback);
   Button &                      setPosition(RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition);
   Button &                      setSize(const sf::Vector2f & size);
   Button &                      setColor(const WidgetStyles & widgetColors);
   Button &                      setLabel(const std::string & label);

   Button &                      setChanged(bool isChanged);
   bool                          isChanged()                                     const;

   Button &                      setView(const sf::View & view);

   void                          warnMouseHovering(int x, int y);
   void                          warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released);

private:
   virtual Button *              cloneImpl()                                     const;

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

   sf::RectangleShape            button;
   sf::Text                      buttonLabel;
};


} // namespace paercebal::KizukoLib::gui

#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_BUTTON_x_HPP

