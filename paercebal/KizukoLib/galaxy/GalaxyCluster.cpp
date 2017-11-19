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
   , shapes(8)
   , size{ 5.f }
   , color{ sf::Color::Red }
   , coreColor{ sf::Color::White }
{
   this->setCenter({ center_.x / 10.f, center_.y / 10.f, center_.z / 10.f });
   this->setRelativePositions({ { 0, 0, 0 } });
}

void GalaxyCluster::createShapes2D()
{
   GalaxyCluster::Positions & positions = this->getAbsolutePositions();

   if (positions.size() > 0)
   {
      GalaxyCluster::Position & position = positions[0];

      getStarHalo(this->shapes[0], this->color, 16, positions[0], this->size * 3.f);
      getStarHalo(this->shapes[1], this->color, 32, positions[0], this->size * 2.0f);
      getStarHalo(this->shapes[2], this->color, 64, positions[0], this->size * 1.5f);
      getStarHalo(this->shapes[3], this->color, 128, positions[0], this->size * 1.25f);
      getGradientStar(this->shapes[4], this->color, this->coreColor, 0, positions[0], this->size);
      getGradientStar(this->shapes[5], this->color, this->coreColor, .25f, positions[0], this->size);
      getGradientStar(this->shapes[6], this->color, this->coreColor, .50f, positions[0], this->size);
      getGradientStar(this->shapes[7], this->color, this->coreColor, 1.0f, positions[0], this->size);

      this->nameLabel.setString(this->name);
      this->nameLabel.setFont(this->getGlobalResources().getFontScifi().font);
      this->nameLabel.setCharacterSize(this->getGlobalResources().getFontScifi().size);
      this->nameLabel.setStyle(sf::Text::Regular);
      this->nameLabel.setFillColor(sf::Color::White);
      this->nameLabel.setPosition({ position.x + 2 * this->size, position.y - 4 * this->size });
   }
}

void GalaxyCluster::drawInto(sf::RenderTarget & renderTarget) const
{
   for (const auto & c : this->shapes)
   {
      renderTarget.draw(c);
   }

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
