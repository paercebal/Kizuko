#include <paercebal/KizukoLib/clusters/View.hpp>

#include <paercebal/KizukoLib/clusters/Cluster.hpp>
#include <paercebal/Graphics/maths/Matrix3D.hpp>
#include <paercebal/Graphics/maths/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <memory>
#include <string>
#include <sstream>
#include <cmath>

namespace paercebal::KizukoLib::clusters
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
   auto cluster = std::make_unique<Cluster>(globalResources);
   this->cluster = cluster.get();
   this->getChildren().push_back(std::move(cluster));
   this->updateTranslation();
   this->updateZoom();
}

void View::createShapes2D()
{
   this->debugLabel.setString(this->debugText);
   this->debugLabel.setFont(this->getGlobalResources().getFontNormal().font);
   this->debugLabel.setCharacterSize(this->getGlobalResources().getFontNormal().size);
   this->debugLabel.setStyle(sf::Text::Regular);
   this->debugLabel.setFillColor(sf::Color::White);
   this->debugLabel.setPosition({ 20, 20 });
}

void View::drawInto(sf::RenderTarget & renderTarget) const
{
   this->cluster->drawInto(renderTarget);
   renderTarget.draw(this->debugLabel);
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


} // namespace paercebal::KizukoLib::clusters
