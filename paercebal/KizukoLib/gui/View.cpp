#include <paercebal/KizukoLib/gui/View.hpp>

#include <paercebal/KizukoLib/clusters/Cluster.hpp>
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

}

View::View(const GlobalResources & globalResources)
   : View(globalResources, 10.0f)
{
}

View::View(const GlobalResources & globalResources, float translationIncrement_)
   : super(globalResources)
   , translationIncrement(translationIncrement_)
   , button(globalResources, RelativePositionStyle::BottomLeft, { 20.f, -20.f }, { 200.f, 40.f })
{
   auto cluster = std::make_unique<clusters::Cluster>(globalResources);
   this->cluster = cluster.get();
   this->getChildren().push_back(std::move(cluster));
   this->updateTranslation();
   this->updateZoom();

   this->spaceBackground.loadFromFile("./copyrighted/caleston-rift.png");
   this->spaceBackground.setSmooth(true);
   this->spaceBackgroundSprite.setTexture(this->spaceBackground);
   this->spaceBackgroundSprite.setScale(sf::Vector2f(1.0f, 1.0f));
   this->spaceBackgroundSprite.setColor(sf::Color(255, 255, 255, 96));

   this->button.setCommand([this]() { this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible; this->setChanged(true); });
}

View & View::setView(const sf::View & view)
{
   this->viewSize = view.getSize();
   this->viewCenter = view.getCenter();
   this->button.setView(view);
   this->setChanged(true);

   return *this;
}

void View::createShapes2D()
{
   this->debugLabel.setString(this->debugText);
   this->debugLabel.setFont(this->getGlobalResources().getFontNormal().font);
   this->debugLabel.setCharacterSize(this->getGlobalResources().getFontNormal().size);
   this->debugLabel.setStyle(sf::Text::Regular);
   this->debugLabel.setFillColor(sf::Color::White);
   this->debugLabel.setPosition({ 0, 0 });

   {
      this->nameLabel.setString("Caleston Rift");
      this->nameLabel.setFont(this->getGlobalResources().getFontScifi().font);
      this->nameLabel.setCharacterSize(this->getGlobalResources().getFontScifi().size * 2);
      this->nameLabel.setStyle(sf::Text::Regular);
      this->nameLabel.setFillColor(sf::Color::White);

      // right-bottom Cluster Name position
      const float xPos = this->viewCenter.x + (this->viewSize.x / 2.f) - (20 + 40);
      const float yPos = this->viewCenter.y + (this->viewSize.y / 2.f) - (40 + 40);

      const sf::FloatRect labelBounds = this->nameLabel.getLocalBounds();
      this->nameLabel.setPosition({ xPos - labelBounds.width, yPos });
   }

   {
      const float xPos = this->viewCenter.x - (this->viewSize.x / 2.f);
      const float yPos = this->viewCenter.y - (this->viewSize.y / 2.f);
      this->spaceBackgroundSprite.setPosition(sf::Vector2f(xPos, yPos));
   }

   this->button.createShapes2D();
}

void View::warnMouseHovering(int x, int y)
{
   this->button.warnMouseHovering(x, y);
}

void View::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   this->button.warnMouseClicking(pressed, released);
}

void View::drawInto(sf::RenderTarget & renderTarget) const
{
   if (this->isSpaceBackgroundVisible)
   {
      renderTarget.draw(this->spaceBackgroundSprite);
   }

   this->cluster->drawInto(renderTarget);
   renderTarget.draw(this->debugLabel);
   renderTarget.draw(this->nameLabel);
   this->button.drawInto(renderTarget);
}

std::unique_ptr<View> View::clone() const
{
   return std::unique_ptr<View>(this->cloneImpl());
}

View * View::cloneImpl() const
{
   return new View(*this);
}

View & View::setDebugText(const std::string & debugText_)
{
   this->debugText = debugText_;
   return *this;
}

View & View::setDebugText(std::string && debugText_)
{
   this->debugText = std::move(debugText_);
   return *this;
}

View & View::updateTranslation()
{
   auto v = Graphics::maths::utilities::createTranslationVector<float>(static_cast<float>(this->translationX), static_cast<float>(this->translationY), 0);
   this->cluster->setCenter(v);

   //std::stringstream str;
   //str << "Translation: " << this->translationIncrementX << "x, " << this->translationIncrementY << "y | ZoomPosition: " << this->zoomPosition << "| Zoom: " << this->zoom << "x";
   //this->debugText = str.str();

   this->setChanged(true);

   return *this;
}

View & View::updateZoom()
{
   this->zoomPosition = std::clamp(this->zoomPosition, -100, +100);
   this->zoom = static_cast<float>(std::pow(10., (this->zoomPosition / 100.) + 1.));
   auto m = Graphics::maths::utilities::createScaleMatrix<float>(this->zoom);
   this->cluster->setRelativeScaling(m);

   //std::stringstream str;
   //str << "Translation: " << this->translationIncrementX << "x, " << this->translationIncrementY << "y | ZoomPosition: " << this->zoomPosition << "| Zoom: " << this->zoom << "x";
   //this->debugText = str.str();

   this->setChanged(true);

   return *this;
}

View & View::translateByPixels(int x, int y)
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


View & View::translateXPositive()
{
   this->translationIncrementX += 1;
   this->translationX = static_cast<int>(this->translationIncrementX * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

View & View::translateYPositive()
{
   this->translationIncrementY += 1;
   this->translationY = static_cast<int>(this->translationIncrementY * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

View & View::translateXNegative()
{
   this->translationIncrementX -= 1;
   this->translationX = static_cast<int>(this->translationIncrementX * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

View & View::translateYNegative()
{
   this->translationIncrementY -= 1;
   this->translationY = static_cast<int>(this->translationIncrementY * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

View & View::zoomIn()
{
   this->zoomPosition += 1;
   this->updateZoom();

   return *this;
}

View & View::zoomOut()
{
   this->zoomPosition -= 1;
   this->updateZoom();

   return *this;
}

View & View::zoomInByWheel()
{
   this->zoomPosition += 5;
   this->updateZoom();

   return *this;
}

View & View::zoomOutByWheel()
{
   this->zoomPosition -= 5;
   this->updateZoom();

   return *this;
}

View & View::setChanged(bool isChanged_)
{
   this->isChanged_ = isChanged_;
   return *this;
}

bool View::isChanged() const
{
   return this->isChanged_;
}

PAERCEBAL_x_KIZUKOLIB_x_API void calculateAbsolutePositionThenShapes2DRecursiveIfNeeded(View & view)
{
   if (view.isChanged())
   {
      calculateAbsolutePositionThenShapes2DRecursive(view);
      view.setChanged(false);
   }
}


} // namespace paercebal::KizukoLib::gui
