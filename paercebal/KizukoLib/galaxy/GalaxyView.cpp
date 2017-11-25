#include <paercebal/KizukoLib/galaxy/GalaxyView.hpp>

#include <paercebal/KizukoLib/galaxy/Galaxy.hpp>
#include <paercebal/Graphics/maths/Matrix3D.hpp>
#include <paercebal/Graphics/maths/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <memory>
#include <string>
#include <sstream>
#include <cmath>

namespace paercebal::KizukoLib::galaxy
{

namespace {

}

GalaxyView::GalaxyView(const GlobalResources & globalResources, GalaxyViewCommands galaxyViewCommands)
   : GalaxyView(globalResources, galaxyViewCommands, 10.0f)
{
}

GalaxyView::GalaxyView(const GlobalResources & globalResources, GalaxyViewCommands galaxyViewCommands, float translationIncrement_)
   : super(globalResources, translationIncrement_)
   , commands(galaxyViewCommands)
   //, button(globalResources, gui::RelativePositionStyle::BottomLeft, { 20.f, -20.f }, { 200.f, 40.f })
   , label(globalResources, gui::RelativePositionStyle::BottomRight, { -20.f, -20.f }, 2.f)
{
   {
      GalaxyCommands galaxyCommands;
      galaxyCommands.onSelectCluster = [this](const std::string & clusterName) { this->commands.onSelectCluster(clusterName); };
      auto viewedGalaxy = std::make_unique<galaxy::Galaxy>(globalResources, galaxyCommands, *this);
      this->galaxy = viewedGalaxy.get();
      this->setViewedObject(std::move(viewedGalaxy));
   }

   //this->button.setLabel("Go to Caleston Rift");
   //this->button.setCommand([]() commands.onSelectCluster();
   //this->button.registerIntoObserver(*this);

   this->label.setLabel("Milky Way");
   this->label.setCommand([this]()
   {
      //this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible;
      this->galaxy->setBackgroundImageVisible(!this->galaxy->isBackgroundImageVisible());
      this->setChanged(true);
   });
   this->label.registerIntoObserver(*this);
}

void GalaxyView::createShapes2D()
{
   super::createShapes2D();

   //this->button.createShapes2D();
   this->label.createShapes2D();
}

void GalaxyView::drawInto(sf::RenderTarget & renderTarget) const
{
   super::drawInto(renderTarget);

   //this->button.drawInto(renderTarget);
   this->label.drawInto(renderTarget);
}

std::unique_ptr<GalaxyView> GalaxyView::clone() const
{
   return std::unique_ptr<GalaxyView>(this->cloneImpl());
}

GalaxyView * GalaxyView::cloneImpl() const
{
   return new GalaxyView(*this);
}


} // namespace paercebal::KizukoLib::clusters
