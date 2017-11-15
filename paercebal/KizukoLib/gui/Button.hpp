#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_BUTTON_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_BUTTON_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/gui/Widget.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <functional>


namespace paercebal::KizukoLib::gui
{

class PAERCEBAL_x_KIZUKOLIB_x_API Button : public Widget
{
   using super = Widget;
public:

   using CommandCallback = std::function<void(void)>;

   Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_);
   Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_, const WidgetStyles & widgetStyles_);
   Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_, const WidgetStyles & widgetStyles_, CommandCallback commandCallback_);

   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<Button>       clone()                                         const;

   using super::setSize;

   Button &                      setLabel(const std::string & label);

private:

   virtual void                  createShapes2DFirstWhenChanged()                      override;
   virtual void                  createShapes2DSecondAlways()                          override;

   virtual Button *              cloneImpl()                                     const;

   sf::RectangleShape            button;
   sf::Text                      buttonLabel;
};


} // namespace paercebal::KizukoLib::gui

#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_BUTTON_x_HPP

