#include <paercebal/KizukoLib/gui/Screen.hpp>

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

Screen::Screen(const GlobalResources & globalResources_)
   : globalResources{ &globalResources_ }
{
   this->clustersView = std::make_unique<clusters::View>(globalResources_);
}

Screen::Screen(const Screen & that)
   : globalResources{ that.globalResources }
   , clustersView{ that.clustersView->clone() }
   , sfmlView{ that.sfmlView }
{
}

Screen & Screen::operator = (const Screen & that)
{
   if (this != &that)
   {
      Screen tmp(that);
      *this = std::move(tmp);
   }

   return *this;
}

Screen::Screen(Screen && that) noexcept
   : globalResources{ std::move(that.globalResources) }
   , clustersView{ std::move(that.clustersView) }
   , sfmlView{ std::move(that.sfmlView) }
{
}

Screen & Screen::operator = (Screen && that) noexcept
{
   if (this != &that)
   {
      this->globalResources = std::move(that.globalResources);
      this->clustersView = std::move(that.clustersView);
      this->sfmlView = std::move(that.sfmlView);
   }

   return *this;
}


const GlobalResources & Screen::getGlobalResources() const
{
   return *this->globalResources;
}


Screen & Screen::setView(const sf::View & view)
{
   this->sfmlView = view;
   this->clustersView->setView(view);
   return *this;
}

void Screen::warnMouseHovering(int x, int y)
{
   this->clustersView->warnMouseHovering(x, y);
}

void Screen::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   this->clustersView->warnMouseClicking(pressed, released);
}

void Screen::drawInto(sf::RenderTarget & renderTarget) const
{
   this->clustersView->drawInto(renderTarget);
}

std::unique_ptr<Screen> Screen::clone() const
{
   return std::unique_ptr<Screen>(this->cloneImpl());
}

Screen * Screen::cloneImpl() const
{
   return new Screen(*this);
}

Screen & Screen::onMouseDragByPixels(int x, int y)
{
   this->clustersView->translateByPixels(x, y);
   return *this;
}


Screen & Screen::onLeftKeyPressed()
{
   this->clustersView->translateXPositive();
   return *this;
}

Screen & Screen::onUpKeyPressed()
{
   this->clustersView->translateYPositive();
   return *this;
}

Screen & Screen::onRightKeyPressed()
{
   this->clustersView->translateXNegative();
   return *this;
}

Screen & Screen::onDownKeyPressed()
{
   this->clustersView->translateYNegative();
   return *this;
}

Screen & Screen::onPageUpKeyPressed()
{
   this->clustersView->zoomIn();
   return *this;
}

Screen & Screen::onPageDownKeyPressed()
{
   this->clustersView->zoomOut();
   return *this;
}

Screen & Screen::onMouseWheelScrollPositive()
{
   this->clustersView->zoomInByWheel();
   return *this;
}

Screen & Screen::onMouseWheelScrollNegative()
{
   this->clustersView->zoomOutByWheel();
   return *this;
}

void Screen::calculateAbsolutePositionThenShapes2DRecursiveIfNeeded()
{
   clusters::calculateAbsolutePositionThenShapes2DRecursiveIfNeeded(*this->clustersView);
}

} // namespace paercebal::KizukoLib::gui
