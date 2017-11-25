#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_CONTROL_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_CONTROL_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>

#include <SFML/Graphics.hpp>

#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <vector>


namespace paercebal::KizukoLib::gui
{


class PAERCEBAL_x_KIZUKOLIB_x_API Control
{
public:

   using CommandCallback = std::function<void(void)>;

   Control &                     setCommand(CommandCallback commandCallback);

   Control &                     setChanged(bool isChanged);
   bool                          isChanged()                                     const;

   Control &                     setView(const sf::View & view);

   sf::FloatRect                 getControlBounds()                              const;
   bool                          isMouseHovering()                               const;

   void                          warnMouseHovering(int x, int y);
   void                          warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released);
   void                          warnLoseFocus();

protected:
   void                          setControlBounds(const sf::FloatRect & controlBounds_);

   CommandCallback               commandCallback;

   bool                          changed = true;
   sf::Vector2f                  viewSize;
   sf::Vector2f                  viewCenter;
   sf::Vector2i                  viewMousePosition;
   sf::FloatRect                 controlBounds;

protected:
   Control() = default;
   virtual ~Control() = default;
   Control(const Control &) = default;
   Control & operator = (const Control &) = default;
   Control(Control &&) = default;
   Control & operator = (Control &&) = default;
};

} // namespace paercebal::KizukoLib::gui





#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_CONTROL_x_HPP

