#include <paercebal/KizukoLib/gui/Control.hpp>

//#include <paercebal/KizukoLib/Exception.hpp>
//#include <paercebal/KizukoLib/utilities.hpp>
//
//#include <paercebal/Graphics/maths/Matrix3D.hpp>
//#include <paercebal/Graphics/maths/utilities.hpp>
//
//#include <SFML/Graphics.hpp>
//
//#include <algorithm>
//#include <memory>
//#include <string>
//#include <sstream>
//#include <cmath>

namespace paercebal::KizukoLib::gui
{

Control & Control::setCommand(CommandCallback commandCallback)
{
   this->commandCallback = commandCallback;
   this->setChanged(true);
   return *this;
}

Control & Control::setChanged(bool changed)
{
   this->changed = changed;
   return *this;
}

bool Control::isChanged() const
{
   return this->changed;
}

Control & Control::setView(const sf::View & view)
{
   this->viewSize = view.getSize();
   this->viewCenter = view.getCenter();
   this->setChanged(true);

   return *this;
}

bool Control::isMouseHovering() const
{
   sf::FloatRect widgetBounds = this->getControlBounds();
   const bool isHoveringOnWidget = ((this->viewMousePosition.x >= widgetBounds.left) && (this->viewMousePosition.x <= widgetBounds.left + widgetBounds.width) && (this->viewMousePosition.y >= widgetBounds.top) && (this->viewMousePosition.y <= widgetBounds.top + widgetBounds.height));
   return isHoveringOnWidget;
}

void Control::warnMouseHovering(int x, int y)
{
   const float xPos = this->viewCenter.x - (this->viewSize.x / 2.f) + x;
   const float yPos = this->viewCenter.y - (this->viewSize.y / 2.f) + y;

   this->viewMousePosition = { static_cast<int>(xPos), static_cast<int>(yPos) };
}

void Control::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   auto convertToViewCoordinates = [this](sf::Vector2i pos) ->sf::Vector2i
   {
      return { static_cast<int>(this->viewCenter.x - (this->viewSize.x / 2.f) + pos.x), static_cast<int>(this->viewCenter.y - (this->viewSize.y / 2.f) + pos.y) };
   };

   auto realPressed = convertToViewCoordinates(pressed);
   auto realReleased = convertToViewCoordinates(released);

   auto isWithinWidgetBounds = [this](sf::Vector2i mouse) ->bool
   {
      sf::FloatRect widgetBounds = this->getControlBounds();
      return ((mouse.x >= widgetBounds.left) && (mouse.x <= widgetBounds.left + widgetBounds.width) && (mouse.y >= widgetBounds.top) && (mouse.y <= widgetBounds.top + widgetBounds.height));
   };

   const bool isClickingOnWidget = isWithinWidgetBounds(realPressed) && isWithinWidgetBounds(realReleased);

   if (isClickingOnWidget && this->commandCallback)
   {
      this->commandCallback();
   }
}

void Control::warnLoseFocus()
{
   this->viewMousePosition = { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() };
}

sf::FloatRect Control::getControlBounds() const
{
   return this->controlBounds;
}

void Control::setControlBounds(const sf::FloatRect & controlBounds_)
{
   this->controlBounds = controlBounds_;
   this->setChanged(true);
}

} // namespace paercebal::KizukoLib::gui

