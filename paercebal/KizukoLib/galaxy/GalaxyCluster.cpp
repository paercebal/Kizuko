#include <paercebal/KizukoLib/galaxy/GalaxyCluster.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <paercebal/Graphics/maths/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <cmath>
#include <memory>
#include <string>

namespace paercebal::KizukoLib::galaxy
{

GalaxyCluster::GalaxyCluster(const GlobalResources & globalResources, const std::string & name_, sf::Vector3f center_)
   : super(globalResources)
   , name{ name_ }
   , size{ 5.f }
   , color{ sf::Color::Red }
   , hoverColor{ sf::Color::Cyan }
{
   this->setCenter({ center_.x, center_.y, center_.z });
   this->setRelativePositions({ { 0, 0, 0 } });

   this->isClusterDefined = this->getGlobalResources().getData().getCluster(name_) != nullptr;
}

void GalaxyCluster::registerIntoObserver(gui::ObserverWidget3D & observerWidget3D_)
{
   this->unregisterFromObserver();
   observerWidget3D_.registerWidget3D(*this);
   this->observerWidget3D = &observerWidget3D_;
}

void GalaxyCluster::unregisterFromObserver()
{
   if (this->observerWidget3D)
   {
      this->observerWidget3D->unregisterWidget3D(*this);
      this->observerWidget3D = nullptr;
   }
}

void GalaxyCluster::createShapes2D()
{
   GalaxyCluster::Positions & positions = this->getAbsolutePositions();

   if (positions.size() > 0)
   {
      GalaxyCluster::Position & position = positions[0];

      const sf::Vector2f controlPosition = { position.x - this->size, position.y - this->size };
      const sf::Vector2f controlSize = { this->size * 2, this->size * 2 };
      this->setControlBounds({ controlPosition, controlSize });

      if (this->isClusterDefined)
      {
         if (this->isMouseHovering())
         {
            this->circle.setFillColor(sf::Color::Transparent);
            this->circle.setOutlineColor(this->hoverColor);
            this->circle.setOutlineThickness(3.f);
            this->circle.setRadius(this->size);
         }
         else
         {
            this->circle.setFillColor(sf::Color::Transparent);
            this->circle.setOutlineColor(this->color);
            this->circle.setOutlineThickness(2.f);
            this->circle.setRadius(this->size);
         }
      }
      else
      {
         this->circle.setFillColor(sf::Color::Transparent);
         this->circle.setOutlineColor({ 192, 192, 192 ,128 });
         this->circle.setOutlineThickness(2.f);
         this->circle.setRadius(this->size);
      }

      this->circle.setPosition(controlPosition);

      this->nameLabel.setString(this->name);
      this->nameLabel.setFont(this->getGlobalResources().getFontScifi().font);
      this->nameLabel.setCharacterSize(this->getGlobalResources().getFontScifi().size);
      this->nameLabel.setStyle(sf::Text::Regular);

      if (this->isClusterDefined)
      {
         if (this->isMouseHovering())
         {
            this->nameLabel.setFillColor(sf::Color::White);
         }
         else
         {
            this->nameLabel.setFillColor({ 255, 255, 255, 192 });
         }
      }
      else
      {
         this->nameLabel.setFillColor({ 192, 192, 192, 128 });
      }

      this->nameLabel.setOutlineColor({0, 0, 0, 128});
      this->nameLabel.setOutlineThickness(2.f);
      this->nameLabel.setPosition({ position.x + 2 * this->size, position.y - 4 * this->size });
   }
}

void GalaxyCluster::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->circle);
   renderTarget.draw(this->nameLabel);
}

std::unique_ptr<GalaxyCluster> GalaxyCluster::clone() const
{
   return std::unique_ptr<GalaxyCluster>(this->cloneImpl());
}

GalaxyCluster * GalaxyCluster::cloneImpl() const
{
   return new GalaxyCluster(*this);
}

const std::string & GalaxyCluster::getName() const
{
   return this->name;
}

} // namespace paercebal::KizukoLib::galaxy
