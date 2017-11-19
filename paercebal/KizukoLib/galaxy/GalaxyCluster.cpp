#include <paercebal/KizukoLib/galaxy/GalaxyCluster.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <paercebal/Graphics/maths/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <cmath>
#include <memory>
#include <string>

namespace paercebal::KizukoLib::galaxy
{

sf::Color getGradient(const sf::Color & lower, const sf::Color & higher, float gradient)
{
   return { static_cast<sf::Uint8>(lower.r + (higher.r - lower.r) * gradient), static_cast<sf::Uint8>(lower.g + (higher.g - lower.g) * gradient), static_cast<sf::Uint8>(lower.b + (higher.b - lower.b) * gradient), static_cast<sf::Uint8>(lower.a + (higher.a - lower.a) * gradient) };
}

void getGradientStar(sf::CircleShape & c, const sf::Color & lower, const sf::Color & higher, float gradient, const GalaxyCluster::Position & position, float size)
{
   const float radius = size - (0.5f * size * gradient);
   c.setFillColor(getGradient(lower, higher, gradient));
   c.setRadius(radius);
   c.setPosition({ position.x - radius, position.y - radius });
}

void getStarHalo(sf::CircleShape & c, const sf::Color & color, sf::Uint8 transparency, const GalaxyCluster::Position & position, float size)
{
   const float radius = size;
   c.setFillColor({ color.r, color.g, color.b, transparency });
   c.setRadius(radius);
   c.setPosition({ position.x - radius, position.y - radius });
}

GalaxyCluster::GalaxyCluster(const GlobalResources & globalResources, const std::string & name_, sf::Vector3f center_)
   : super(globalResources)
   , name{ name_ }
   , size{ 5.f }
   , color{ sf::Color::Red }
   , coreColor{ sf::Color::White }
{
   this->setCenter({ center_.x, center_.y, center_.z });
   this->setRelativePositions({ { 0, 0, 0 } });
}

void GalaxyCluster::createShapes2D()
{
   GalaxyCluster::Positions & positions = this->getAbsolutePositions();

   if (positions.size() > 0)
   {
      GalaxyCluster::Position & position = positions[0];

      const float radius = size;
      this->circle.setFillColor(sf::Color::Transparent);
      this->circle.setOutlineColor(this->color);
      this->circle.setOutlineThickness(2.f);
      this->circle.setRadius(this->size);
      this->circle.setPosition({ position.x - this->size, position.y - this->size });



      this->nameLabel.setString(this->name);
      this->nameLabel.setFont(this->getGlobalResources().getFontScifi().font);
      this->nameLabel.setCharacterSize(this->getGlobalResources().getFontScifi().size);
      this->nameLabel.setStyle(sf::Text::Regular);
      this->nameLabel.setFillColor(sf::Color::White);
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
