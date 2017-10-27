#ifndef PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_ABSTRACT_LINE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_ABSTRACT_LINE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/IDrawable.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <array>

namespace paercebal::KizukoLib::shapes
{


class AbstractLine : public IDrawable
{
   using super = IDrawable;
public:

   virtual void         drawInto(sf::RenderTarget & renderTarget) const override;

   AbstractLine &       setBegin(sf::Vector3f point);
   AbstractLine &       setEnd(sf::Vector3f point);

protected:
   AbstractLine(const GlobalResources & globalResources_, sf::Color color_);
   AbstractLine(const GlobalResources & globalResources_, sf::Color color_, sf::Vector3f begin3D_, sf::Vector3f end3D_);

private:

   std::array<sf::Vertex, 2> line2D;

   sf::Vector3f begin3D;
   sf::Vector3f end3D;
   sf::Color    color;
};



inline AbstractLine::AbstractLine(const GlobalResources & globalResources_, sf::Color color_)
   : AbstractLine(globalResources_, color_, sf::Vector3f(), sf::Vector3f())
{
}

inline AbstractLine::AbstractLine(const GlobalResources & globalResources_, sf::Color color_, sf::Vector3f begin3D_, sf::Vector3f end3D_)
   : super(globalResources_)
{
   this->setBegin(begin3D_);
   this->setEnd(end3D_);
   this->color = color_;
   this->line2D[0].color = color_;
   this->line2D[1].color = color_;
}

inline AbstractLine & AbstractLine::setBegin(sf::Vector3f point)
{
   this->begin3D = point;
   this->line2D[0].position = utilities::convert_3D_to_iso2D(this->begin3D);
   return *this;
}

inline AbstractLine & AbstractLine::setEnd(sf::Vector3f point)
{
   this->end3D = point;
   this->line2D[1].position = utilities::convert_3D_to_iso2D(this->end3D);
   return *this;
}

inline void AbstractLine::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->line2D.data(), this->line2D.size(), sf::Lines);
}




} // namespace paercebal::Kizuko::shapes





#endif // PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_ABSTRACT_LINE_x_HPP

