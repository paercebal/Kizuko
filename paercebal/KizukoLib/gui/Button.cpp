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

const WidgetStyles ButtonStyles =
{
   {
      { { 0, 128, 255, 128 },{ 0, 128, 255, 192 }, 2.f }
      ,{ { 255, 255, 255, 255 },{ 0, 0, 0, 0 }, 0, sf::Text::Regular }
   }
   ,{
      { { 0, 128, 255, 192 },{ 0, 128, 255, 255 }, 2.f }
      ,{ { 255, 255, 255, 255 },{ 0, 0, 0, 0 }, 0, sf::Text::Regular }
   }
};

} // anonymous namespace

Button::Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_)
   : Button(globalResources_, relativePositionStyle_, relativePosition_, size_, ButtonStyles)
{
}

Button::Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_, const WidgetStyles & widgetStyles_)
   : Button(globalResources_, relativePositionStyle_, relativePosition_, size_, widgetStyles_, []() {})
{
}

Button::Button(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, const sf::Vector2f & size_, const WidgetStyles & widgetStyles_, CommandCallback commandCallback_)
   : super(globalResources_, relativePositionStyle_, relativePosition_, widgetStyles_, commandCallback_)
{
   this->setSize(size_);
}

Button & Button::setLabel(const std::string & label)
{
   this->buttonLabel.setString(label);
   this->setChanged(true);
   return *this;
}

void Button::createShapes2DFirstWhenChanged()
{
   this->calculateAbsolutePosition();

   this->button.setSize(this->size);
   this->button.setPosition(this->absolutePosition);

   this->buttonLabel.setFont(this->getGlobalResources().getFontScifi().font);
   this->buttonLabel.setCharacterSize(static_cast<int>(this->getGlobalResources().getFontScifi().size * 1.2));

   const sf::FloatRect labelBounds = this->buttonLabel.getLocalBounds();
   const sf::Vector2f labelSize = { labelBounds.width + labelBounds.left, labelBounds.height + labelBounds.top }; // for some reason, the size and the local bounds are different. facepalm.
   this->buttonLabel.setPosition({ this->absolutePosition.x + (this->size.x - labelSize.x) / 2.f, this->absolutePosition.y + (this->size.y - labelSize.y) / 2.f });
}

void Button::createShapes2DSecondAlways()
{
   WidgetStyle style = this->isMouseHovering() ? this->styles.hover : this->styles.normal;

   this->button.setFillColor(style.area.background);
   this->button.setOutlineColor(style.area.outline);
   this->button.setOutlineThickness(style.area.outlineThickness);
   this->buttonLabel.setFillColor(style.font.foreground);
   this->buttonLabel.setStyle(style.font.style);
   this->buttonLabel.setOutlineColor(style.font.outline);
   this->buttonLabel.setOutlineThickness(style.font.outlineThickness);
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

} // namespace paercebal::KizukoLib::gui
