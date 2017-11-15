#include <paercebal/KizukoLib/gui/Widget.hpp>

#include <paercebal/Graphics/maths/Matrix3D.hpp>
#include <paercebal/Graphics/maths/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <memory>
#include <string>
#include <sstream>
#include <cmath>

namespace paercebal::KizukoLib::gui
{

namespace {

/// @todo There's a way to write it in a more concise, less copy-n-paste manner, using a flag enum
sf::Vector2f doCalculateAbsolutePosition(const sf::Vector2f & viewCenter, const sf::Vector2f & viewSize, RelativePositionStyle widgetRelativePositionStyle, const sf::Vector2f & widgetPosition, const sf::Vector2f & widgetSize)
{
   switch (widgetRelativePositionStyle)
   {
      case RelativePositionStyle::CenterLeft:
         {
            const float xPos = viewCenter.x - (viewSize.x / 2.f) + widgetPosition.x;
            const float yPos = viewCenter.y + widgetPosition.y - (widgetSize.y / 2.f);
            return { xPos, yPos };
         }
         break;
      case RelativePositionStyle::CenterRight:
         {
            const float xPos = viewCenter.x + (viewSize.x / 2.f) + widgetPosition.x - widgetSize.x;
            const float yPos = viewCenter.y + widgetPosition.y - (widgetSize.y / 2.f);
            return { xPos, yPos };
         }
         break;
      case RelativePositionStyle::TopCenter:
         {
            const float xPos = viewCenter.x + widgetPosition.x - (widgetSize.x / 2.f);
            const float yPos = viewCenter.y - (viewSize.y / 2.f) + widgetPosition.y;
            return { xPos, yPos };
         }
         break;
      case RelativePositionStyle::BottomCenter:
         {
            const float xPos = viewCenter.x + widgetPosition.x - (widgetSize.x / 2.f);
            const float yPos = viewCenter.y + (viewSize.y / 2.f) + widgetPosition.y - widgetSize.y;
            return { xPos, yPos };
         }
         break;
      case RelativePositionStyle::TopLeft:
         {
            const float xPos = viewCenter.x - (viewSize.x / 2.f) + widgetPosition.x;
            const float yPos = viewCenter.y - (viewSize.y / 2.f) + widgetPosition.y;
            return { xPos, yPos };
         }
         break;
      case RelativePositionStyle::TopRight:
         {
            const float xPos = viewCenter.x + (viewSize.x / 2.f) + widgetPosition.x - widgetSize.x;
            const float yPos = viewCenter.y - (viewSize.y / 2.f) + widgetPosition.y;
            return { xPos, yPos };
         }
         break;
      case RelativePositionStyle::BottomLeft:
         {
            const float xPos = viewCenter.x - (viewSize.x / 2.f) + widgetPosition.x;
            const float yPos = viewCenter.y + (viewSize.y / 2.f) + widgetPosition.y - widgetSize.y;
            return { xPos, yPos };
         }
         break;
      case RelativePositionStyle::BottomRight:
         {
            const float xPos = viewCenter.x + (viewSize.x / 2.f) + widgetPosition.x - widgetSize.x;
            const float yPos = viewCenter.y + (viewSize.y / 2.f) + widgetPosition.y - widgetSize.y;
            return { xPos, yPos };
         }
         break;
      case RelativePositionStyle::Center:
      default:
         {
            const float xPos = viewCenter.x + widgetPosition.x - (widgetSize.x / 2.f);
            const float yPos = viewCenter.y + widgetPosition.y - (widgetSize.y / 2.f);
            return { xPos, yPos };
         }
         break;
   };
}

const WidgetStyles GlobalWidgetStyles =
{
   {
      { { 0, 0, 0, 0 },{ 0, 0, 0, 0 }, 0 }
      ,{ { 255, 255, 255, 255 },{ 0, 0, 0, 128 }, 2.f, sf::Text::Regular }
   }
   ,{
      { { 0, 0, 0, 0 },{ 0, 0, 0, 0 }, 0 }
      ,{ { 255, 255, 255, 255 },{ 0, 128, 255, 192 }, 3.f, sf::Text::Regular }
   }
};

} // anonymous namespace

Widget::Widget(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_)
   : Widget(globalResources_, relativePositionStyle_, relativePosition_, GlobalWidgetStyles)
{
}

Widget::Widget(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, const WidgetStyles & widgetStyles_)
   : Widget(globalResources_, relativePositionStyle_, relativePosition_, widgetStyles_, []() {})
{
}

Widget::Widget(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, const WidgetStyles & widgetStyles_, CommandCallback commandCallback_)
   : globalResources{ globalResources_ }
   , relativePositionStyle{ relativePositionStyle_ }
   , relativePosition{ relativePosition_ }
   , styles(widgetStyles_)
   , commandCallback(commandCallback_)
{
}

const GlobalResources & Widget::getGlobalResources() const
{
   return this->globalResources;
}

Widget & Widget::setSize(const sf::Vector2f & size)
{
   this->size = size;
   return *this;
}

Widget & Widget::setStyle(const WidgetStyles & widgetStyles)
{
   this->styles = widgetStyles;
   return *this;
}

Widget & Widget::setPosition(RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition)
{
   this->relativePositionStyle = relativePositionStyle;
   this->relativePosition = relativePosition;
   this->setChanged(true);
   return *this;
}

Widget & Widget::setView(const sf::View & view)
{
   this->viewSize = view.getSize();
   this->viewCenter = view.getCenter();
   this->setChanged(true);

   return *this;
}

Widget & Widget::setCommand(CommandCallback commandCallback)
{
   this->commandCallback = commandCallback;
   this->setChanged(true);
   return *this;
}

void Widget::calculateAbsolutePosition()
{
   this->absolutePosition = doCalculateAbsolutePosition(this->viewCenter, this->viewSize, this->relativePositionStyle, this->relativePosition, this->size);
}

sf::FloatRect Widget::getWidgetBounds() const
{
   return { this->absolutePosition, this->size };
}

bool Widget::isMouseHovering() const
{
   sf::FloatRect widgetBounds = this->getWidgetBounds();
   const bool isHoveringOnWidget = ((this->viewMousePosition.x >= widgetBounds.left) && (this->viewMousePosition.x <= widgetBounds.left + widgetBounds.width) && (this->viewMousePosition.y >= widgetBounds.top) && (this->viewMousePosition.y <= widgetBounds.top + widgetBounds.height));
   return isHoveringOnWidget;
}

void Widget::createShapes2D()
{
   if (this->isChanged())
   {
      this->createShapes2DFirstWhenChanged();
      this->setChanged(false);
   }

   this->createShapes2DSecondAlways();
}

void Widget::warnMouseHovering(int x, int y)
{
   const float xPos = this->viewCenter.x - (this->viewSize.x / 2.f) + x;
   const float yPos = this->viewCenter.y - (this->viewSize.y / 2.f) + y;

   this->viewMousePosition = { static_cast<int>(xPos), static_cast<int>(yPos) };
}

void Widget::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   auto convertToViewCoordinates = [this](sf::Vector2i pos) ->sf::Vector2i
   {
      return { static_cast<int>(this->viewCenter.x - (this->viewSize.x / 2.f) + pos.x), static_cast<int>(this->viewCenter.y - (this->viewSize.y / 2.f) + pos.y) };
   };

   auto realPressed = convertToViewCoordinates(pressed);
   auto realReleased = convertToViewCoordinates(released);

   auto isWithinWidgetBounds = [this](sf::Vector2i mouse) ->bool
   {
      sf::FloatRect widgetBounds = this->getWidgetBounds();
      return ((mouse.x >= widgetBounds.left) && (mouse.x <= widgetBounds.left + widgetBounds.width) && (mouse.y >= widgetBounds.top) && (mouse.y <= widgetBounds.top + widgetBounds.height));
   };

   const bool isClickingOnWidget = isWithinWidgetBounds(realPressed) && isWithinWidgetBounds(realReleased);

   if (isClickingOnWidget)
   {
      this->commandCallback();
   }
}

std::unique_ptr<Widget> Widget::clone() const
{
   return std::unique_ptr<Widget>(this->cloneImpl());
}

Widget & Widget::setChanged(bool changed)
{
   this->changed = changed;
   return *this;
}

bool Widget::isChanged() const
{
   return this->changed;
}

} // namespace paercebal::KizukoLib::gui
