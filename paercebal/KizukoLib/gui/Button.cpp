#include <paercebal/KizukoLib/gui/Button.hpp>

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
sf::Vector2f calculateAbsolutePosition(const sf::Vector2f & viewCenter, const sf::Vector2f & viewSize, RelativePositionStyle widgetRelativePositionStyle, const sf::Vector2f & widgetPosition, const sf::Vector2f & widgetSize)
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


}

Button::Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_)
   : Button(globalResources_, relativePositionStyle_, relativePosition_, size_, { { { 255, 255, 255, 255 },{ 0, 128, 255, 128 },{ 0, 128, 255, 192 } },{ { 255, 255, 255, 255 },{ 0, 128, 255, 192 },{ 0, 128, 255, 255 } } })
{
}

Button::Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_, const WidgetColors & widgetColors_)
   : Button(globalResources_, relativePositionStyle_, relativePosition_, size_, widgetColors_, []() {})
{
}

Button::Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_, const WidgetColors & widgetColors_, CommandCallback commandCallback_)
   : globalResources{ globalResources_ }
   , relativePositionStyle{ relativePositionStyle_ }
   , relativePosition{ relativePosition_ }
   , size{ size_ }
   , colors(widgetColors_)
   , commandCallback(commandCallback_)
{
}

const GlobalResources & Button::getGlobalResources() const
{
   return this->globalResources;
}

Button & Button::setSize(const sf::Vector2f & size)
{
   this->size = size;
   this->setChanged(true);
   return *this;
}

Button & Button::setPosition(RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition)
{
   this->relativePositionStyle = relativePositionStyle;
   this->relativePosition = relativePosition;
   this->setChanged(true);
   return *this;
}

Button & Button::setView(const sf::View & view)
{
   this->viewSize = view.getSize();
   this->viewCenter = view.getCenter();
   this->setChanged(true);

   return *this;
}

Button & Button::setLabel(const std::string & label)
{
   this->buttonLabel.setString(label);
   this->setChanged(true);
   return *this;
}

Button & Button::setCommand(CommandCallback commandCallback)
{
   this->commandCallback = commandCallback;
   this->setChanged(true);
   return *this;
}

void Button::createShapes2D()
{
   if (this->isChanged())
   {
      this->absolutePosition = calculateAbsolutePosition(this->viewCenter, this->viewSize, this->relativePositionStyle, this->relativePosition, this->size);

      this->button.setSize(this->size);
      this->button.setPosition(this->absolutePosition);

      this->button.setOutlineThickness(2.f);

      this->buttonLabel.setString("Background");
      this->buttonLabel.setFont(this->getGlobalResources().getFontScifi().font);
      this->buttonLabel.setCharacterSize(this->getGlobalResources().getFontScifi().size * 1.2);
      this->buttonLabel.setStyle(sf::Text::Regular);

      const sf::FloatRect labelBounds = this->buttonLabel.getLocalBounds();
      this->buttonLabel.setPosition({ this->absolutePosition.x + (this->size.x - (labelBounds.width - labelBounds.left)) / 2.f, this->absolutePosition.y + (this->size.y - (labelBounds.height + labelBounds.top)) / 2.f }); /// @todo there's a bug, somewhere near. The label is too low.
      //this->buttonLabel.setPosition({ 0, 0 - labelBounds.height/1.3f });

      this->setChanged(false);
   }

   sf::FloatRect buttonBounds = this->button.getGlobalBounds();
   const bool isHoveringOnButton = ((this->viewMousePosition.x >= buttonBounds.left) && (this->viewMousePosition.x <= buttonBounds.left + buttonBounds.width) && (this->viewMousePosition.y >= buttonBounds.top) && (this->viewMousePosition.y <= buttonBounds.top + buttonBounds.height));

   WidgetColorStates colorState = isHoveringOnButton ? this->colors.hover : this->colors.normal;

   this->button.setFillColor(colorState.background);
   this->button.setOutlineColor(colorState.outline);

   this->buttonLabel.setFillColor(colorState.foreground);
}

void Button::warnMouseHovering(int x, int y)
{
   const float xPos = this->viewCenter.x - (this->viewSize.x / 2.f) + x;
   const float yPos = this->viewCenter.y - (this->viewSize.y / 2.f) + y;

   this->viewMousePosition = { static_cast<int>(xPos), static_cast<int>(yPos) };
}

void Button::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   auto convertToViewCoordinates = [this](sf::Vector2i pos) ->sf::Vector2i
   {
      return { static_cast<int>(this->viewCenter.x - (this->viewSize.x / 2.f) + pos.x), static_cast<int>(this->viewCenter.y - (this->viewSize.y / 2.f) + pos.y) };
   };

   auto realPressed = convertToViewCoordinates(pressed);
   auto realReleased = convertToViewCoordinates(released);

   auto isWithinButtonBounds = [this](sf::Vector2i mouse) ->bool
   {
      sf::FloatRect buttonBounds = this->button.getGlobalBounds();
      return ((mouse.x >= buttonBounds.left) && (mouse.x <= buttonBounds.left + buttonBounds.width) && (mouse.y >= buttonBounds.top) && (mouse.y <= buttonBounds.top + buttonBounds.height));
   };

   const bool isClickingOnButton = isWithinButtonBounds(realPressed) && isWithinButtonBounds(realReleased);

   if (isClickingOnButton)
   {
      this->commandCallback();
   }
}

void Button::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->button);
   renderTarget.draw(this->buttonLabel);
}

std::unique_ptr<Button> Button::clone() const
{
   return std::unique_ptr<Button>(this->cloneImpl());
}

Button * Button::cloneImpl() const
{
   return new Button(*this);
}

Button & Button::setChanged(bool changed)
{
   this->changed = changed;
   return *this;
}

bool Button::isChanged() const
{
   return this->changed;
}

} // namespace paercebal::KizukoLib::gui
