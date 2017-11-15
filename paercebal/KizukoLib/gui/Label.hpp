#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_LABEL_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_LABEL_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/gui/Button.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <functional>


namespace paercebal::KizukoLib::gui
{

class PAERCEBAL_x_KIZUKOLIB_x_API Label
{
public:

   using CommandCallback = std::function<void(void)>;

   Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_);
   Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, float fontScale_);
   Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, float fontScale_, const WidgetStyles & widgetStyles_);
   Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, float fontScale_, const WidgetStyles & widgetStyles_, CommandCallback commandCallback_);

   virtual void                  createShapes2D();
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const;
   std::unique_ptr<Label>        clone()                                         const;

   const GlobalResources &       getGlobalResources()                            const;

   Label &                       setCommand(CommandCallback commandCallback);
   Label &                       setPosition(RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition);
   Label &                       setFontScale(float fontScale);
   Label &                       setColor(const WidgetStyles & widgetColors);
   Label &                       setLabel(const std::string & label);

   Label &                       setChanged(bool isChanged);
   bool                          isChanged()                                     const;

   Label &                       setView(const sf::View & view);

   void                          warnMouseHovering(int x, int y);
   void                          warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released);

private:
   virtual Label *               cloneImpl()                                     const;

   const GlobalResources &       globalResources;
   RelativePositionStyle         relativePositionStyle = RelativePositionStyle::Center;
   sf::Vector2f                  relativePosition = {};
   sf::Vector2f                  absolutePosition = {};
   sf::Vector2f                  size = {};
   bool                          changed = true;
   WidgetStyles                  styles;
   CommandCallback               commandCallback;
   float                         fontScale = 1.f;

   sf::Vector2f                  viewSize;
   sf::Vector2f                  viewCenter;
   sf::Vector2i                  viewMousePosition;

   sf::Text                      label;
};


} // namespace paercebal::KizukoLib::gui

#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_LABEL_x_HPP

