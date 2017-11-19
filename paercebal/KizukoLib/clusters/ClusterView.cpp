#include <paercebal/KizukoLib/clusters/ClusterView.hpp>

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

ClusterView::ClusterView(const GlobalResources & globalResources, ClusterViewCommands clusterViewCommands)
   : ClusterView(globalResources, clusterViewCommands, 10.0f)
{
}

ClusterView::ClusterView(const GlobalResources & globalResources, ClusterViewCommands clusterViewCommands, float translationIncrement_)
   : super(globalResources)
   , translationIncrement(translationIncrement_)
   , commands(clusterViewCommands)
   , button(globalResources, gui::RelativePositionStyle::BottomLeft, { 20.f, -20.f }, { 200.f, 40.f })
   , label(globalResources, gui::RelativePositionStyle::BottomRight, { -20.f, -20.f }, 2.f)
   , milkyWay(globalResources, gui::RelativePositionStyle::TopLeft, { 20.f, 20.f }, 2.f)
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

   this->button.setLabel("Background");
   this->button.setCommand([this]() { this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible; this->setChanged(true); });

   this->label.setLabel("Caleston Rift");
   this->label.setCommand([this]() { this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible; this->setChanged(true); });

   this->milkyWay.setLabel("Milky Way");
   this->milkyWay.setCommand(this->commands.onBack);
}

ClusterView & ClusterView::setView(const sf::View & view)
{
   this->viewSize = view.getSize();
   this->viewCenter = view.getCenter();
   this->button.setView(view);
   this->label.setView(view);
   this->milkyWay.setView(view);
   this->setChanged(true);

   return *this;
}

void ClusterView::createShapes2D()
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
   this->milkyWay.createShapes2D();
}

void ClusterView::warnMouseHovering(int x, int y)
{
   this->button.warnMouseHovering(x, y);
   this->label.warnMouseHovering(x, y);
   this->milkyWay.warnMouseHovering(x, y);
   this->setChanged(true); // This is wrong. I should do better.
}

void ClusterView::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   this->button.warnMouseClicking(pressed, released);
   this->label.warnMouseClicking(pressed, released);
   this->milkyWay.warnMouseClicking(pressed, released);
   this->setChanged(true); // This is wrong. I should do better.
}

void ClusterView::warnLoseFocus()
{
   this->button.warnLoseFocus();
   this->label.warnLoseFocus();
   this->milkyWay.warnLoseFocus();
   this->setChanged(true); // This is wrong. I should do better.
}

void ClusterView::drawInto(sf::RenderTarget & renderTarget) const
{
   if (this->isSpaceBackgroundVisible)
   {
      renderTarget.draw(this->spaceBackgroundSprite);
   }

   this->cluster->drawInto(renderTarget);
   renderTarget.draw(this->debugLabel);
   this->button.drawInto(renderTarget);
   this->label.drawInto(renderTarget);
   this->milkyWay.drawInto(renderTarget);
}

std::unique_ptr<ClusterView> ClusterView::clone() const
{
   return std::unique_ptr<ClusterView>(this->cloneImpl());
}

ClusterView * ClusterView::cloneImpl() const
{
   return new ClusterView(*this);
}

ClusterView & ClusterView::setDebugText(const std::string & debugText_)
{
   this->debugText = debugText_;
   return *this;
}

ClusterView & ClusterView::setDebugText(std::string && debugText_)
{
   this->debugText = std::move(debugText_);
   return *this;
}

ClusterView & ClusterView::updateTranslation()
{
   auto v = Graphics::maths::utilities::createTranslationVector<float>(static_cast<float>(this->translationX), static_cast<float>(this->translationY), 0);
   this->cluster->setCenter(v);

   //std::stringstream str;
   //str << "Translation: " << this->translationIncrementX << "x, " << this->translationIncrementY << "y | ZoomPosition: " << this->zoomPosition << "| Zoom: " << this->zoom << "x";
   //this->debugText = str.str();

   this->setChanged(true);

   return *this;
}

ClusterView & ClusterView::updateZoom()
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

ClusterView & ClusterView::translateByPixels(int x, int y)
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


ClusterView & ClusterView::translateXPositive()
{
   this->translationIncrementX += 1;
   this->translationX = static_cast<int>(this->translationIncrementX * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

ClusterView & ClusterView::translateYPositive()
{
   this->translationIncrementY += 1;
   this->translationY = static_cast<int>(this->translationIncrementY * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

ClusterView & ClusterView::translateXNegative()
{
   this->translationIncrementX -= 1;
   this->translationX = static_cast<int>(this->translationIncrementX * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

ClusterView & ClusterView::translateYNegative()
{
   this->translationIncrementY -= 1;
   this->translationY = static_cast<int>(this->translationIncrementY * this->translationIncrement);
   this->updateTranslation();

   return *this;
}

ClusterView & ClusterView::zoomIn()
{
   this->zoomPosition += 1;
   this->updateZoom();

   return *this;
}

ClusterView & ClusterView::zoomOut()
{
   this->zoomPosition -= 1;
   this->updateZoom();

   return *this;
}

ClusterView & ClusterView::zoomInByWheel()
{
   this->zoomPosition += 5;
   this->updateZoom();

   return *this;
}

ClusterView & ClusterView::zoomOutByWheel()
{
   this->zoomPosition -= 5;
   this->updateZoom();

   return *this;
}

ClusterView & ClusterView::setChanged(bool isChanged_)
{
   this->isChanged_ = isChanged_;
   return *this;
}

bool ClusterView::isChanged() const
{
   return this->isChanged_;
}

void ClusterView::calculateAbsolutePositionThenShapes2DRecursiveIfNeeded()
{
   if (this->isChanged())
   {
      calculateAbsolutePositionThenShapes2DRecursive(*this);
      this->setChanged(false);
   }
}

//PAERCEBAL_x_KIZUKOLIB_x_API void calculateAbsolutePositionThenShapes2DRecursiveIfNeeded(ClusterView & view)
//{
//   if (view.isChanged())
//   {
//      calculateAbsolutePositionThenShapes2DRecursive(view);
//      view.setChanged(false);
//   }
//}

} // namespace paercebal::KizukoLib::clusters
