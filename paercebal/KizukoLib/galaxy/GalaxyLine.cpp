#include <paercebal/KizukoLib/galaxy/GalaxyLine.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::galaxy
{

namespace {

inline sf::Color GalaxyLineStyleToColor(GalaxyLineStyle style)
{
   switch (style)
   {
      //case GalaxyLineStyle::AxisX: return sf::Color{ 255, 128, 128, 128 };
      //case GalaxyLineStyle::AxisY: return sf::Color{ 128, 128, 255, 128 };
      case GalaxyLineStyle::AxisX: return sf::Color{ 255, 255, 255, 128 };
      case GalaxyLineStyle::AxisY: return sf::Color{ 255, 255, 255, 128 };
      case GalaxyLineStyle::Major: return sf::Color{ 255, 255, 255, 64 };
      case GalaxyLineStyle::Minor: return sf::Color{ 255, 255, 255, 32 };
   }

   return sf::Color::White;
}

} // namespace


GalaxyLine::GalaxyLine(const GlobalResources & globalResources, GalaxyLineStyle style_, sf::Vector3f begin_, sf::Vector3f end_)
   : GalaxyLine(globalResources, GalaxyLineStyleToColor(style_), begin_, end_)
{
}

GalaxyLine::GalaxyLine(const GlobalResources & globalResources, sf::Color color_, sf::Vector3f begin_, sf::Vector3f end_)
   : super(globalResources)
   , color{ color_ }
{
   this->setRelativePositions({ begin_, end_ });
}

void GalaxyLine::createShapes2D()
{
   GalaxyLine::Positions & positions = this->getAbsolutePositions();

   if (positions.size() > 0)
   {
      this->line2D[0].color = this->color;
      this->line2D[1].color = this->color;

      this->line2D[0].position.x = positions[0].x;
      this->line2D[0].position.y = positions[0].y;
      this->line2D[1].position.x = positions[1].x;
      this->line2D[1].position.y = positions[1].y;
   }
}

void GalaxyLine::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->line2D.data(), this->line2D.size(), sf::Lines);
}

std::unique_ptr<GalaxyLine> GalaxyLine::clone() const
{
   return std::unique_ptr<GalaxyLine>(this->cloneImpl());
}

GalaxyLine * GalaxyLine::cloneImpl() const
{
   return new GalaxyLine(*this);
}

sf::Vector3f GalaxyLine::getBegin3D() const noexcept
{
   return this->getRelativePositions().at(0);
}

sf::Vector3f GalaxyLine::getEnd3D() const noexcept
{
   return this->getRelativePositions().at(1);
}

sf::Color GalaxyLine::getColor() const noexcept
{
   return this->color;
}


} // namespace paercebal::KizukoLib::galaxy
