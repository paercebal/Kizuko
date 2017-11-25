#include <paercebal/KizukoLib/clusters/ClusterView.hpp>

#include <paercebal/KizukoLib/clusters/Cluster.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

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
   : super(globalResources, translationIncrement_)
   , commands(clusterViewCommands)
   , button(globalResources, gui::RelativePositionStyle::BottomLeft, { 20.f, -20.f }, { 200.f, 40.f })
   , label(globalResources, gui::RelativePositionStyle::BottomRight, { -20.f, -20.f }, 2.f)
   , milkyWay(globalResources, gui::RelativePositionStyle::TopLeft, { 20.f, 20.f }, 2.f)
{
   this->setViewedObject(std::make_unique<clusters::Cluster>(globalResources));

   this->button.setLabel("Background");
   this->button.setCommand([this]() { this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible; this->setChanged(true); });

   this->label.setLabel("Caleston Rift");
   this->label.setCommand([this]() { this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible; this->setChanged(true); });

   this->milkyWay.setLabel("Milky Way");
   this->milkyWay.setCommand(this->commands.onBack);
}

ClusterView & ClusterView::setView(const sf::View & view)
{
   super::setView(view);

   this->button.setView(view);
   this->label.setView(view);
   this->milkyWay.setView(view);
   this->setChanged(true);

   return *this;
}

void ClusterView::createShapes2D()
{
   super::createShapes2D();

   this->button.createShapes2D();
   this->label.createShapes2D();
   this->milkyWay.createShapes2D();
}

void ClusterView::warnMouseHovering(int x, int y)
{
   super::warnMouseHovering(x, y);

   this->button.warnMouseHovering(x, y);
   this->label.warnMouseHovering(x, y);
   this->milkyWay.warnMouseHovering(x, y);
   this->setChanged(true); // This is wrong. I should do better.
}

void ClusterView::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   super::warnMouseClicking(pressed, released);

   this->button.warnMouseClicking(pressed, released);
   this->label.warnMouseClicking(pressed, released);
   this->milkyWay.warnMouseClicking(pressed, released);
   this->setChanged(true); // This is wrong. I should do better.
}

void ClusterView::warnLoseFocus()
{
   super::warnLoseFocus();

   this->button.warnLoseFocus();
   this->label.warnLoseFocus();
   this->milkyWay.warnLoseFocus();
   this->setChanged(true); // This is wrong. I should do better.
}

void ClusterView::drawInto(sf::RenderTarget & renderTarget) const
{
   super::drawInto(renderTarget);

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


} // namespace paercebal::KizukoLib::clusters
