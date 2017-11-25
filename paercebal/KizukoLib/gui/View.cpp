#include <paercebal/KizukoLib/gui/View.hpp>

#include <paercebal/KizukoLib/Exception.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

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

View::View(const GlobalResources & globalResources_, float translationIncrement_)
   : super(globalResources_)
   , translationIncrement(translationIncrement_)
{
   PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(this->spaceBackground, "./copyrighted/caleston-rift.png", "./resources/cluster-empty.png");
   this->spaceBackground.setSmooth(true);
   this->spaceBackgroundSprite.setTexture(this->spaceBackground);
   this->spaceBackgroundSprite.setScale(sf::Vector2f(1.0f, 1.0f));
   this->spaceBackgroundSprite.setColor(sf::Color(255, 255, 255, 96));

}

View::~View()
{
}

View & View::setViewedObject(std::unique_ptr<objects::Object> viewedObject_)
{
   if (this->viewedObject != nullptr)
   {
      throw Exception() << "Trying to set the viewed object again.";
   }

   this->viewedObject = viewedObject_.get();
   this->getChildren().push_back(std::move(viewedObject_));
   this->updateTranslation();
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

View & View::setView(const sf::View & view)
{
   this->viewSize = view.getSize();
   this->viewCenter = view.getCenter();

   for (auto p : this->widgetGui)
   {
      p->setView(view);
   }

   for (auto p : this->widget3D)
   {
      p->setView(view);
   }

   this->setChanged(true);

   return *this;
}

void View::warnViewAboutMouseHovering(int x, int y)
{
   for (auto p : this->widgetGui)
   {
      p->warnMouseHovering(x, y);
   }

   for (auto p : this->widget3D)
   {
      p->warnMouseHovering(x, y);
   }

   this->setChanged(true); // This is wrong. I should do better.
}

void View::warnViewAboutMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   for (auto p : this->widgetGui)
   {
      p->warnMouseClicking(pressed, released);
   }

   for (auto p : this->widget3D)
   {
      p->warnMouseClicking(pressed, released);
   }

   this->setChanged(true); // This is wrong. I should do better.
}

void View::warnViewAboutLoseFocus()
{
   for (auto p : this->widgetGui)
   {
      p->warnLoseFocus();
   }

   for (auto p : this->widget3D)
   {
      p->warnLoseFocus();
   }

   this->setChanged(true); // This is wrong. I should do better.
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
      const float xPos = this->viewCenter.x - (this->viewSize.x / 2.f);
      const float yPos = this->viewCenter.y - (this->viewSize.y / 2.f);
      this->spaceBackgroundSprite.setPosition(sf::Vector2f(xPos, yPos));
   }
}

void View::drawInto(sf::RenderTarget & renderTarget) const
{
   if (this->isSpaceBackgroundVisible)
   {
      renderTarget.draw(this->spaceBackgroundSprite);
   }

   this->viewedObject->drawInto(renderTarget);
   renderTarget.draw(this->debugLabel);
}

std::unique_ptr<View> View::clone() const
{
   return std::unique_ptr<View>(this->cloneImpl());
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
   this->viewedObject->setCenter(v);

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
   this->viewedObject->setRelativeScaling(m);

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

void View::calculateAbsolutePositionThenShapes2DRecursiveIfNeeded()
{
   if (this->isChanged())
   {
      calculateAbsolutePositionThenShapes2DRecursive(*this);
      this->setChanged(false);
   }
}

void View::registerWidget3D(Control & control)
{
   this->widget3D.insert(&control);
}

void View::unregisterWidget3D(Control & control)
{
   this->widget3D.erase(&control);
}

void View::registerWidgetGui(Control & control)
{
   this->widgetGui.insert(&control);
}

void View::unregisterWidgetGui(Control & control)
{
   this->widgetGui.erase(&control);
}



} // namespace paercebal::KizukoLib::gui

