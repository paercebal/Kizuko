#ifndef PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_STAR_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_STAR_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/IDrawable.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::shapes
{



class Star : public IDrawable
{
   using super = IDrawable;
public:

   Star(const GlobalResources & globalResources, const std::string & name_, sf::Color color_, sf::Vector3f center_, float size_);

   const std::string &  getName() const;
   sf::Vector3f         getCenter3D() const;
   sf::Color            getColor() const;

   virtual void         drawInto(sf::RenderTarget & renderTarget) const override;

private:
   std::string          name;
   sf::CircleShape      shape;
   sf::Vector3f         center3D;
   sf::Vector2f         center2D;
   float                size;
   sf::Color            color;
   sf::Text             nameLabel;
};



inline Star::Star(const GlobalResources & globalResources, const std::string & name_, sf::Color color_, sf::Vector3f center_, float size_)
   : super(globalResources)
   , name{ name_ }
   , center3D { center_ }
   , center2D{ utilities::convert_3D_to_iso2D(center_) }
   , size{ size_ }
   , color{ color_ }
{
   this->shape.setFillColor(this->color);
   this->shape.setRadius(this->size);
   this->shape.setPosition({ this->center2D.x - this->size, this->center2D.y - this->size });

   this->nameLabel.setString(this->name);
   this->nameLabel.setFont(this->getGlobalResources().getScifiFont());
   this->nameLabel.setCharacterSize(10);
   this->nameLabel.setStyle(sf::Text::Regular);
   this->nameLabel.setFillColor(sf::Color::White);
   this->nameLabel.setPosition({ this->center2D.x + 2 * this->size, this->center2D.y - 2 * this->size });
}

inline void Star::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->shape);
   renderTarget.draw(this->nameLabel);
}

const std::string & Star::getName() const
{
   return this->name;
}

sf::Vector3f Star::getCenter3D() const
{
   return this->center3D;
}

sf::Color Star::getColor() const
{
   return this->color;
}


} // namespace paercebal::KizukoLib::shapes





#endif // PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_STAR_x_HPP

