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
   galaxy::GalaxyViewCommands galaxyViewCommands;
   galaxyViewCommands.onSelectCluster = [this](const std::string & clusterName) { this->onSelectCluster(clusterName); };

   this->galaxyView = std::make_unique<galaxy::GalaxyView>(globalResources_, galaxyViewCommands);

   // WARNING: CLONING WON'T WORK FOR SAME REASONS
   this->views.push_back(this->galaxyView.get());
}

Screen::Screen(const Screen & that)
   : globalResources{ that.globalResources }
   , clusterView{ that.clusterView->clone() }
   , galaxyView{ that.galaxyView->clone() }
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
   , clusterView{ std::move(that.clusterView) }
   , galaxyView{ std::move(that.galaxyView) }
   , sfmlView{ std::move(that.sfmlView) }
{
}

Screen & Screen::operator = (Screen && that) noexcept
{
   if (this != &that)
   {
      this->globalResources = std::move(that.globalResources);
      this->clusterView = std::move(that.clusterView);
      this->galaxyView = std::move(that.galaxyView);
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

   for (auto & view : this->views)
   {
      view->setView(this->sfmlView);
   }

   return *this;
}

void Screen::warnScreenAboutMouseHovering(int x, int y)
{
   this->getCurrentView()->warnViewAboutMouseHovering(x, y);
}

void Screen::warnScreenAboutMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   this->getCurrentView()->warnViewAboutMouseClicking(pressed, released);
}

void Screen::drawInto(sf::RenderTarget & renderTarget) const
{
   this->getCurrentView()->drawInto(renderTarget);
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
   this->getCurrentView()->translateByPixels(x, y);
   return *this;
}


Screen & Screen::onLeftKeyPressed()
{
   this->getCurrentView()->translateXPositive();
   return *this;
}

Screen & Screen::onUpKeyPressed()
{
   this->getCurrentView()->translateYPositive();
   return *this;
}

Screen & Screen::onRightKeyPressed()
{
   this->getCurrentView()->translateXNegative();
   return *this;
}

Screen & Screen::onDownKeyPressed()
{
   this->getCurrentView()->translateYNegative();
   return *this;
}

Screen & Screen::onPageUpKeyPressed()
{
   this->getCurrentView()->zoomIn();
   return *this;
}

Screen & Screen::onPageDownKeyPressed()
{
   this->getCurrentView()->zoomOut();
   return *this;
}

Screen & Screen::onMouseWheelScrollPositive()
{
   this->getCurrentView()->zoomInByWheel();
   return *this;
}

Screen & Screen::onMouseWheelScrollNegative()
{
   this->getCurrentView()->zoomOutByWheel();
   return *this;
}

void Screen::calculateAbsolutePositionThenShapes2DRecursiveIfNeeded()
{
   this->getCurrentView()->calculateAbsolutePositionThenShapes2DRecursiveIfNeeded();
}

void Screen::onBackFromCluster()
{
   this->getCurrentView()->warnViewAboutLoseFocus();
   this->views.pop_back();

   // NOTE: We should send a custom event to the message loop to ask for the closing
   // of the cluster screen. The following line will crash.
   //this->clusterView.reset();
}

void Screen::onSelectCluster(const std::string & clusterName)
{
   if (const input::Cluster * cluster = this->getGlobalResources().getData().getCluster(clusterName))
   {
      this->getCurrentView()->warnViewAboutLoseFocus();

      // WARNING: CLONING WON'T WORK AS THE "THIS" POINTER IN THE LAMBDAS WON'T BE UPDATED
      clusters::ClusterViewCommands clusterViewCommands;
      clusterViewCommands.onBack = [this]() { this->onBackFromCluster(); };
      this->clusterView = std::make_unique<clusters::ClusterView>(this->getGlobalResources(), clusterViewCommands, *cluster);

      this->views.push_back(this->clusterView.get());

      this->clusterView->setView(this->sfmlView);
   }
}

const View * Screen::getCurrentView() const
{
   return this->views[this->views.size() - 1];
}

View * Screen::getCurrentView()
{
   return this->views[this->views.size() - 1];
}


} // namespace paercebal::KizukoLib::gui
