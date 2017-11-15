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
   : globalResources{ globalResources_ }
   , relativePositionStyle{ relativePositionStyle_ }
   , relativePosition{ relativePosition_ }
   , fontScale{ fontScale_ }
   , styles(widgetStyles_)
   , commandCallback(commandCallback_)
{
}

const GlobalResources & Label::getGlobalResources() const
{
   return this->globalResources;
}

Label & Label::setFontScale(float fontScale)
{
   this->fontScale = fontScale;
   this->setChanged(true);
   return *this;
}
Label & Label::setPosition(RelativePositionStyle relativePositionStyle, const sf::Vector2f & relativePosition)
{
   this->relativePositionStyle = relativePositionStyle;
   this->relativePosition = relativePosition;
   this->setChanged(true);
   return *this;
}

Label & Label::setView(const sf::View & view)
{
   this->viewSize = view.getSize();
   this->viewCenter = view.getCenter();
   this->setChanged(true);

   return *this;
}

Label & Label::setLabel(const std::string & label)
{
   this->label.setString(label);
   this->setChanged(true);
   return *this;
}

Label & Label::setCommand(CommandCallback commandCallback)
{
   this->commandCallback = commandCallback;
   this->setChanged(true);
   return *this;
}

void Label::createShapes2D()
{
   if (this->isChanged())
   {
      this->label.setFont(this->getGlobalResources().getFontScifi().font);
      this->label.setCharacterSize(static_cast<int>(this->getGlobalResources().getFontScifi().size * this->fontScale));

      const sf::FloatRect labelBounds = this->label.getLocalBounds();
      this->size.x = labelBounds.width + labelBounds.left;  // I've yet to understand what the LocalBounds is for sf::Text, because that addition makes no sense
      this->size.y = labelBounds.height + labelBounds.top;  // I've yet to understand what the LocalBounds is for sf::Text, because that addition makes no sense

      this->absolutePosition = calculateAbsolutePosition(this->viewCenter, this->viewSize, this->relativePositionStyle, this->relativePosition, this->size);

      this->label.setPosition(this->absolutePosition);

      this->setChanged(false);
   }

   sf::FloatRect labelBounds = { this->absolutePosition, this->size };
   const bool isHoveringOnButton = ((this->viewMousePosition.x >= labelBounds.left) && (this->viewMousePosition.x <= labelBounds.left + labelBounds.width) && (this->viewMousePosition.y >= labelBounds.top) && (this->viewMousePosition.y <= labelBounds.top + labelBounds.height));

   WidgetStyle style = isHoveringOnButton ? this->styles.hover : this->styles.normal;

   this->label.setFillColor(style.font.foreground);
   this->label.setStyle(style.font.style);
   this->label.setOutlineColor(style.font.outline);
   this->label.setOutlineThickness(style.font.outlineThickness);
}

void Label::warnMouseHovering(int x, int y)
{
   const float xPos = this->viewCenter.x - (this->viewSize.x / 2.f) + x;
   const float yPos = this->viewCenter.y - (this->viewSize.y / 2.f) + y;

   this->viewMousePosition = { static_cast<int>(xPos), static_cast<int>(yPos) };
}

void Label::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   auto convertToViewCoordinates = [this](sf::Vector2i pos) ->sf::Vector2i
   {
      return { static_cast<int>(this->viewCenter.x - (this->viewSize.x / 2.f) + pos.x), static_cast<int>(this->viewCenter.y - (this->viewSize.y / 2.f) + pos.y) };
   };

   auto realPressed = convertToViewCoordinates(pressed);
   auto realReleased = convertToViewCoordinates(released);

   auto isWithinLabelBounds = [this](sf::Vector2i mouse) ->bool
   {
      sf::FloatRect labelBounds = { this->absolutePosition, this->size };
      return ((mouse.x >= labelBounds.left) && (mouse.x <= labelBounds.left + labelBounds.width) && (mouse.y >= labelBounds.top) && (mouse.y <= labelBounds.top + labelBounds.height));
   };

   const bool isClickingOnLabel = isWithinLabelBounds(realPressed) && isWithinLabelBounds(realReleased);

   if (isClickingOnLabel)
   {
      this->commandCallback();
   }
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

Label & Label::setChanged(bool changed)
{
   this->changed = changed;
   return *this;
}

bool Label::isChanged() const
{
   return this->changed;
}

} // namespace paercebal::KizukoLib::gui
