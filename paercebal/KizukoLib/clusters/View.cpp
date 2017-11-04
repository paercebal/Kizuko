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
   this->debugLabel.setFont(this->getGlobalResources().getNeutralFont());
   this->debugLabel.setCharacterSize(20);
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

View & View::updateTranslation()
{
   auto v = Graphics::maths::utilities::createTranslationVector<float>(this->translationX * this->translationIncrement, translationY * this->translationIncrement, 0);
   this->cluster->setCenter(v);

   //std::stringstream str;
   //str << "Translation: " << this->translationX << "x, " << this->translationY << "y | ZoomPosition: " << this->zoomPosition << "| Zoom: " << this->zoom << "x";
   //this->debugText = str.str();

   return *this;
}

View & View::updateZoom()
{
   this->zoomPosition = std::clamp(this->zoomPosition, -50, +100);
   this->zoom = std::pow(10., (this->zoomPosition / 100.) + 1.);
   auto m = Graphics::maths::utilities::createScaleMatrix<float>(this->zoom);
   this->cluster->setRelativeScaling(m);

   //std::stringstream str;
   //str << "Translation: " << this->translationX << "x, " << this->translationY << "y | ZoomPosition: " << this->zoomPosition << "| Zoom: " << this->zoom << "x";
   //this->debugText = str.str();

   return *this;
}

View & View::translateXPositive()
{
   this->translationX += 1;
   this->updateTranslation();

   return *this;
}

View & View::translateYPositive()
{
   this->translationY += 1;
   this->updateTranslation();

   return *this;
}

View & View::translateXNegative()
{
   this->translationX -= 1;
   this->updateTranslation();

   return *this;
}

View & View::translateYNegative()
{
   this->translationY -= 1;
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




} // namespace paercebal::KizukoLib::clusters
