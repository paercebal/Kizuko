#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_LABEL_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_LABEL_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/gui/Widget.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <functional>


namespace paercebal::KizukoLib::gui
{

class PAERCEBAL_x_KIZUKOLIB_x_API Label : public Widget
{
   using super = Widget;
public:

   using CommandCallback = std::function<void(void)>;

   Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_);
   Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, float fontScale_);
   Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, float fontScale_, const WidgetStyles & widgetStyles_);
   Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition_, float fontScale_, const WidgetStyles & widgetStyles_, CommandCallback commandCallback_);

   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<Label>        clone()                                         const;

   Label &                       setFontScale(float fontScale);
   Label &                       setLabel(const std::string & label);

private:
   virtual void                  createShapes2DFirstWhenChanged()                      override;
   virtual void                  createShapes2DSecondAlways()                          override;

   virtual Label *               cloneImpl()                                     const;

   float                         fontScale = 1.f;

   sf::Text                      label;
};


} // namespace paercebal::KizukoLib::gui

#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_LABEL_x_HPP

