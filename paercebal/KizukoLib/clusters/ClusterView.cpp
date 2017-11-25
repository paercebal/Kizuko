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

ClusterView::ClusterView(const GlobalResources & globalResources, ClusterViewCommands clusterViewCommands, const input::Cluster & inputCluster)
   : ClusterView(globalResources, clusterViewCommands, inputCluster, 10.0f)
{
}

ClusterView::ClusterView(const GlobalResources & globalResources, ClusterViewCommands clusterViewCommands, const input::Cluster & inputCluster, float translationIncrement_)
   : super(globalResources, translationIncrement_)
   , commands(clusterViewCommands)
   , button(globalResources, gui::RelativePositionStyle::BottomLeft, { 20.f, -20.f }, { 200.f, 40.f })
   , label(globalResources, gui::RelativePositionStyle::BottomRight, { -20.f, -20.f }, 2.f)
   , milkyWay(globalResources, gui::RelativePositionStyle::TopLeft, { 20.f, 20.f }, 2.f)
{
   this->setViewedObject(std::make_unique<clusters::Cluster>(globalResources, inputCluster));

   this->button.setLabel("Background");
   this->button.registerIntoObserver(*this);
   this->button.setCommand([this]() { this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible; this->setChanged(true); });

   this->label.setLabel(inputCluster.name);
   this->label.registerIntoObserver(*this);
   this->label.setCommand([this]() { this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible; this->setChanged(true); });

   this->milkyWay.setLabel("Milky Way");
   this->milkyWay.registerIntoObserver(*this);
   this->milkyWay.setCommand(this->commands.onBack);
}

void ClusterView::createShapes2D()
{
   super::createShapes2D();

   this->button.createShapes2D();
   this->label.createShapes2D();
   this->milkyWay.createShapes2D();
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
