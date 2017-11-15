#include <paercebal/KizukoLib/gui/Label.hpp>

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

const WidgetStyles LabelStyles =
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

Label::Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_)
   : Label(globalResources_, relativePositionStyle_, relativePosition_, 1.f)
{
}

Label::Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, float fontScale_)
   : Label(globalResources_, relativePositionStyle_, relativePosition_, fontScale_, LabelStyles)
{
}

Label::Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, float fontScale_, const WidgetStyles & widgetStyles_)
   : Label(globalResources_, relativePositionStyle_, relativePosition_, fontScale_, widgetStyles_, []() {})
{
}

Label::Label(const GlobalResources & globalResources_, RelativePositionStyle relativePositionStyle_, const sf::Vector2f & relativePosition_, float fontScale_, const WidgetStyles & widgetStyles_, CommandCallback commandCallback_)
   : super(globalResources_, relativePositionStyle_, relativePosition_, widgetStyles_, commandCallback_)
   , fontScale{ fontScale_ }
{
}

Label & Label::setFontScale(float fontScale)
{
   this->fontScale = fontScale;
   this->setChanged(true);
   return *this;
}

Label & Label::setLabel(const std::string & label)
{
   this->label.setString(label);
   this->setChanged(true);
   return *this;
}

void Label::createShapes2DFirstWhenChanged()
{
   this->label.setFont(this->getGlobalResources().getFontScifi().font);
   this->label.setCharacterSize(static_cast<int>(this->getGlobalResources().getFontScifi().size * this->fontScale));

   const sf::FloatRect labelBounds = this->label.getLocalBounds();
   this->size.x = labelBounds.width + labelBounds.left;  // I've yet to understand what the LocalBounds is for sf::Text, because that addition makes no sense
   this->size.y = labelBounds.height + labelBounds.top;  // I've yet to understand what the LocalBounds is for sf::Text, because that addition makes no sense

   this->calculateAbsolutePosition();

   this->label.setPosition(this->absolutePosition);
}

void Label::createShapes2DSecondAlways()
{
   WidgetStyle style = this->isMouseHovering() ? this->styles.hover : this->styles.normal;

   this->label.setFillColor(style.font.foreground);
   this->label.setStyle(style.font.style);
   this->label.setOutlineColor(style.font.outline);
   this->label.setOutlineThickness(style.font.outlineThickness);
}

void Label::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->label);
}

std::unique_ptr<Label> Label::clone() const
{
   return std::unique_ptr<Label>(this->cloneImpl());
}

Label * Label::cloneImpl() const
{
   return new Label(*this);
}

} // namespace paercebal::KizukoLib::gui
