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
}

View & View::setView(const sf::View & view)
{
   this->viewSize = view.getSize();
   this->viewCenter = view.getCenter();
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

   {
      // left-bottom Button position
      const float xPos = this->viewCenter.x - (this->viewSize.x / 2.f) + 20;
      const float yPos = this->viewCenter.y - (this->viewSize.y / 2.f) + (this->viewSize.y) - 60;

      // Button size
      const float xSize = 200;
      const float ySize = 40;

      this->button.setSize({ xSize, ySize });
      this->button.setPosition({ xPos, yPos });

      sf::FloatRect buttonBounds = this->button.getGlobalBounds();
      bool isHoveringOnButton = ((this->viewMousePosition.x >= buttonBounds.left) && (this->viewMousePosition.x <= buttonBounds.left + buttonBounds.width) && (this->viewMousePosition.y >= buttonBounds.top) && (this->viewMousePosition.y <= buttonBounds.top + buttonBounds.height));

      sf::Color fillColor = isHoveringOnButton ? sf::Color{ 0, 128, 255, 192 } : sf::Color{ 0, 128, 255, 128 };
      sf::Color outlineColor = isHoveringOnButton ? sf::Color{ 0, 128, 255, 255 } : sf::Color{ 0, 128, 255, 192 };

      this->button.setFillColor(fillColor);
      this->button.setOutlineColor(outlineColor);
      this->button.setOutlineThickness(2.f);

      this->buttonLabel.setString("Background");
      this->buttonLabel.setFont(this->getGlobalResources().getFontScifi().font);
      this->buttonLabel.setCharacterSize(this->getGlobalResources().getFontScifi().size);
      this->buttonLabel.setStyle(sf::Text::Regular);
      this->buttonLabel.setFillColor(sf::Color::White);

      const sf::FloatRect labelBounds = this->buttonLabel.getLocalBounds();
      this->buttonLabel.setPosition({ xPos + (xSize - labelBounds.width) / 2.f, yPos + (ySize - labelBounds.height) / 2.f }); /// @todo there's a bug, somewhere near. The label is too low.
      //this->buttonLabel.setPosition({ 0, 0 - labelBounds.height/1.3f });
   }
}

void View::warnMouseHovering(int x, int y)
{
   const float xPos = this->viewCenter.x - (this->viewSize.x / 2.f) + x;
   const float yPos = this->viewCenter.y - (this->viewSize.y / 2.f) + y;

   this->viewMousePosition = { static_cast<int>(xPos), static_cast<int>(yPos) };

   //sf::FloatRect buttonBounds = this->button.getGlobalBounds();
   //const bool isHoveringOnButton = ((this->viewMousePosition.x >= buttonBounds.left) && (this->viewMousePosition.x <= buttonBounds.left + buttonBounds.width) && (this->viewMousePosition.y >= buttonBounds.top) && (this->viewMousePosition.y <= buttonBounds.top + buttonBounds.height));

   //std::stringstream str;
   //str << "Hover: " << x << "x " << y << "y, " << this->viewMousePosition.x << "xPos " << this->viewMousePosition.y << "yPos" << "\n";
   //str << "buttonBounds: " << buttonBounds.left << "left " << buttonBounds.top << "top " << buttonBounds.width << "width " << buttonBounds.height << "height";
   //this->setDebugText(str.str());
}

void View::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
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

   const bool isHoveringOnButton = isWithinButtonBounds(realPressed) && isWithinButtonBounds(realReleased);

   if (isHoveringOnButton)
   {
      this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible;
      //static int clickCount = 0;
      //++clickCount;
      //std::stringstream str;
      //str << "Clicked on button: " << clickCount << " time(s)";
      //this->setDebugText(str.str());
   }
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
   renderTarget.draw(this->button);
   renderTarget.draw(this->buttonLabel);
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
