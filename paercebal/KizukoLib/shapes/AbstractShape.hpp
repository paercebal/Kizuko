#ifndef PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_ABSTRACT_SHAPE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_ABSTRACT_SHAPE_x_HPP

#include <paercebal/KizukoLib/IDrawable.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>


namespace paercebal::KizukoLib::shapes
{

/*
class AbstractShape : public IDrawable
{
public:

   virtual void         drawInto(sf::RenderTarget & renderTarget) const override;

protected:
   AbstractShape(std::unique_ptr<sf::Shape> shape_, sf::Color color_, sf::Vector3f center_, float size_);

private:

   std::unique_ptr<sf::Shape>    shape;
   sf::Vector3f                  center3D;
   sf::Vector2f                  center2D;
   float                         size;
   sf::Color                     color;
};



AbstractShape::AbstractShape(std::unique_ptr<sf::Shape> shape_, sf::Color color_, sf::Vector3f center_, float size_)
   : shape{ std::move(shape_) }
   , center3D{ center_ }
   , center2D{ utilities::convert_3D_to_iso2D(center_) }
   , size{ size_ }
   , color{ color_ }
{
}
*/

} // namespace paercebal::Kizuko::shapes





#endif // PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_ABSTRACT_SHAPE_x_HPP

