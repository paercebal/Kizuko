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
   , button(globalResources, gui::RelativePositionStyle::BottomLeft, { 20.f, -20.f }, { 200.f, 40.f })
   , label(globalResources, gui::RelativePositionStyle::BottomRight, { -20.f, -20.f }, 2.f)
{
   {
      auto viewedGalaxy = std::make_unique<galaxy::Galaxy>(globalResources);
      this->galaxy = viewedGalaxy.get();
      this->setViewedObject(std::move(viewedGalaxy));
   }

   this->button.setLabel("Go to Caleston Rift");
   this->button.setCommand(commands.onBack);

   this->label.setLabel("Milky Way");
   this->label.setCommand([this]()
   {
      //this->isSpaceBackgroundVisible = !this->isSpaceBackgroundVisible;
      this->galaxy->setBackgroundImageVisible(!this->galaxy->isBackgroundImageVisible());
      this->setChanged(true);
   });
}

GalaxyView & GalaxyView::setView(const sf::View & view)
{
   super::setView(view);

   this->button.setView(view);
   this->label.setView(view);
   this->setChanged(true);

   return *this;
}

void GalaxyView::createShapes2D()
{
   super::createShapes2D();

   this->button.createShapes2D();
   this->label.createShapes2D();
}

void GalaxyView::warnMouseHovering(int x, int y)
{
   super::warnMouseHovering(x, y);

   this->button.warnMouseHovering(x, y);
   this->label.warnMouseHovering(x, y);
   this->setChanged(true); // This is wrong. I should do better.
}

void GalaxyView::warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released)
{
   super::warnMouseClicking(pressed, released);

   this->button.warnMouseClicking(pressed, released);
   this->label.warnMouseClicking(pressed, released);
   this->setChanged(true); // This is wrong. I should do better.
}

void GalaxyView::warnLoseFocus()
{
   super::warnLoseFocus();

   this->button.warnLoseFocus();
   this->label.warnLoseFocus();
   this->setChanged(true); // This is wrong. I should do better.
}

void GalaxyView::drawInto(sf::RenderTarget & renderTarget) const
{
   super::drawInto(renderTarget);

   this->button.drawInto(renderTarget);
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
