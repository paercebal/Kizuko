#include <paercebal/KizukoLib/galaxy/GalaxyView.hpp>

#include <paercebal/KizukoLib/galaxy/Galaxy.hpp>
#include <paercebal/Graphics/maths/Matrix3D.hpp>
#include <paercebal/Graphics/maths/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <memory>
#include <string>
#include <sstream>
#include <cmath>

namespace paercebal::KizukoLib::galaxy
{

namespace {

}

GalaxyView::GalaxyView(const GlobalResources & globalResources, GalaxyViewCommands galaxyViewCommands)
   : GalaxyView(globalResources, galaxyViewCommands, 10.0f)
{
}

GalaxyView::GalaxyView(const GlobalResources & globalResources, GalaxyViewCommands galaxyViewCommands, float translationIncrement_)
   : super(globalResources)
   , translationIncrement(translationIncrement_)
   , commands(galaxyViewCommands)
   , button(globalResources, gui::RelativePositionStyle::BottomLeft, { 20.f, -20.f }, { 200.f, 40.f })
   , label(globalResources, gui::RelativePositionStyle::BottomRight, { -20.f, -20.f }, 2.f)
{
   auto galaxy = std::make_unique<galaxy::Galaxy>(globalResources);
   this->galaxy = galaxy.get();
   this->getChildren().push_back(std::move(galaxy));
   this->updateTranslation();
   this->updateZoom();

   this->spaceBackground.loadFromFile("./copyrighted/caleston-rift.png");
   this->spaceBackground.setSmooth(true);
   this->spaceBackgroundSprite.setTexture(this->spaceBackground);
   this->spaceBackgroundSprite.setScale(sf::Vector2f(1.0f, 1.0f));
   this->spaceBackgroundSprite.setColor(sf::Color(255, 255, 255, 96));

   this->button.setLabel("Go to Caleston Rift");
   this->button.setCommand(commands.onBack);

   this->label.setLabel("Milky Way");
   this->label.setCommand([this]() { this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible; this->setChanged(true); });
}

GalaxyView & GalaxyView::setView(const sf::View & view)
{
   this->viewSize = view.getSize();
   this->viewCenter = view.getCenter();
   this->button.setView(view);
   this->label.setView(view);
   this->setChanged(true);

   return *this;
}

void GalaxyView::createShapes2D()
{
   this->debugLabel.setString(this->debugText);
   this->debugLabel.setFont(this->getGlobalResources().getFontNormal().font);
   this->debugLabel.setCharacterSize(this->getGlobalResources().getFontNormal().size);
   this->debugLabel.setStyle(sf::Text::Regular);
   this->debugLabel.setFillColor(sf::Color::White);
   this->debugLabel.setPosition({ 0, 0 });

   {
      const float xPos = this->viewCenter.x - (this->viewSize.x / 2.f);
      const float yPos = this->viewCenter.y - (this->viewSize.y / 2.f);
      this->spaceBackgroundSprite.setPosition(sf::Vector2f(xPos, yPos));
   }

   this->button.createShapes2D();
   this->label.createShapes2D();
}

void GalaxyView::warnMouseHovering(int x, int y)
{
   this->button.warnMouseHovering(x, y);
   this->label.warnMouseHovering(x, y);
   this->setChanged(true); // This is wrong. I should do better.
}

void GalaxyView::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   this->button.warnMouseClicking(pressed, released);
   this->label.warnMouseClicking(pressed, released);
   this->setChanged(true); // This is wrong. I should do better.
}

void GalaxyView::warnLoseFocus()
{
   this->button.warnLoseFocus();
   this->label.warnLoseFocus();
   this->setChanged(true); // This is wrong. I should do better.
}

void GalaxyView::drawInto(sf::RenderTarget & renderTarget) const
{
   if (this->isSpaceBackgroundVisible)
   {
      renderTarget.draw(this->spaceBackgroundSprite);
   }

   this->galaxy->drawInto(renderTarget);
   renderTarget.draw(this->debugLabel);
   this->button.drawInto(renderTarget);
   this->label.drawInto(renderTarget);
}

std::unique_ptr<GalaxyView> GalaxyView::clone() const
{
   return std::unique_ptr<GalaxyView>(this->cloneImpl());
}

GalaxyView * GalaxyView::cloneImpl() const
{
   return new GalaxyView(*this);
}

GalaxyView & GalaxyView::setDebugText(const std::string & debugText_)
{
   this->debugText = debugText_;
   return *this;
}

GalaxyView & GalaxyView::setDebugText(std::string && debugText_)
{
   this->debugText = std::move(debugText_);
   return *this;
}

GalaxyView & GalaxyView::updateTranslation()
{
   auto v = Graphics::maths::utilities::createTranslationVector<float>(static_cast<float>(this->translationX), static_cast<float>(this->translationY), 0);
   this->galaxy->setCenter(v);

   //std::stringstream str;
   //str << "Translation: " << this->translationIncrementX << "x, " << this->translationIncrementY << "y | ZoomPosition: " << this->zoomPosition << "| Zoom: " << this->zoom << "x";
   //this->debugText = str.str();

   this->setChanged(true);

   return *this;
}

GalaxyView & GalaxyView::updateZoom()
{
   this->zoomPosition = std::clamp(this->zoomPosition, -100, +100);
   this->zoom = static_cast<float>(std::pow(10., (this->zoomPosition / 100.) + 1.));
   auto m = Graphics::maths::utilities::createScaleMatrix<float>(this->zoom);
   this->galaxy->setRelativeScaling(m);

   //std::stringstream str;
   //str << "Translation: " << this->translationIncrementX << "x, " << this->translationIncrementY << "y | ZoomPosition: " << this->zoomPosition << "| Zoom: " << this->zoom << "x";
   //this->debugText = str.str();

   this->setChanged(true);

   return *this;
}

GalaxyView & GalaxyView::translateByPixels(int x, int y)
{
   if ((x != 0) || (y != 0))
   {
      this->translationX += x;
      this->translationY += y;
      this->translationIncrementX = static_cast<int>(this->translationX / this->translationIncrement);
      this->translationIncrementY = static_cast<int>(this->translationY / this->translationIncrement);
      this->updateTranslation();
   }

   return *this;
}


GalaxyView & GalaxyView::translateXPositive()
{
   this->translationIncrementX += 1;
   this->translationX = static_cast<int>(this->translationIncrementX * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

GalaxyView & GalaxyView::translateYPositive()
{
   this->translationIncrementY += 1;
   this->translationY = static_cast<int>(this->translationIncrementY * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

GalaxyView & GalaxyView::translateXNegative()
{
   this->translationIncrementX -= 1;
   this->translationX = static_cast<int>(this->translationIncrementX * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

GalaxyView & GalaxyView::translateYNegative()
{
   this->translationIncrementY -= 1;
   this->translationY = static_cast<int>(this->translationIncrementY * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

GalaxyView & GalaxyView::zoomIn()
{
   this->zoomPosition += 1;
   this->updateZoom();

   return *this;
}

GalaxyView & GalaxyView::zoomOut()
{
   this->zoomPosition -= 1;
   this->updateZoom();

   return *this;
}

GalaxyView & GalaxyView::zoomInByWheel()
{
   this->zoomPosition += 5;
   this->updateZoom();

   return *this;
}

GalaxyView & GalaxyView::zoomOutByWheel()
{
   this->zoomPosition -= 5;
   this->updateZoom();

   return *this;
}

GalaxyView & GalaxyView::setChanged(bool isChanged_)
{
   this->isChanged_ = isChanged_;
   return *this;
}

bool GalaxyView::isChanged() const
{
   return this->isChanged_;
}

void GalaxyView::calculateAbsolutePositionThenShapes2DRecursiveIfNeeded()
{
   if (this->isChanged())
   {
      calculateAbsolutePositionThenShapes2DRecursive(*this);
      this->setChanged(false);
   }
}

//PAERCEBAL_x_KIZUKOLIB_x_API void calculateAbsolutePositionThenShapes2DRecursiveIfNeeded(GalaxyView & view)
//{
//   if (view.isChanged())
//   {
//      calculateAbsolutePositionThenShapes2DRecursive(view);
//      view.setChanged(false);
//   }
//}

} // namespace paercebal::KizukoLib::clusters
