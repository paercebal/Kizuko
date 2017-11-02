#include <paercebal/KizukoLib/clusters/Star.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::clusters
{

Star::Star(const GlobalResources & globalResources, const std::string & name_, sf::Color color_, sf::Vector3f center_, float size_)
   : super(globalResources)
   , name{ name_ }
   , size{ size_ }
   , color{ color_ }
{
   this->setCenter(center_);
   this->setRelativePositions({ { 0, 0, 0 } });
}

void Star::createShapes2D()
{
   Star::Positions & positions = this->getAbsolutePositions();

   if (positions.size() > 0)
   {
      Star::Position & position = positions[0];

      this->shape.setFillColor(this->color);
      this->shape.setRadius(this->size);
      this->shape.setPosition({ position.x - this->size, position.y - this->size });

      this->nameLabel.setString(this->name);
      this->nameLabel.setFont(this->getGlobalResources().getScifiFont());
      this->nameLabel.setCharacterSize(20);
      this->nameLabel.setStyle(sf::Text::Regular);
      this->nameLabel.setFillColor(sf::Color::White);
      this->nameLabel.setPosition({ position.x + 2 * this->size, position.y - 4 * this->size });
   }
}

void Star::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->shape);
   renderTarget.draw(this->nameLabel);
}

std::unique_ptr<Star> Star::clone() const
{
   return std::unique_ptr<Star>(this->cloneImpl());
}

Star * Star::cloneImpl() const
{
   return new Star(*this);
}

const std::string & Star::getName() const
{
   return this->name;
}

sf::Color Star::getColor() const
{
   return this->color;
}


} // namespace paercebal::KizukoLib::clusters
