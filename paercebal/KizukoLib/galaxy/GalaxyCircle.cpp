#include <paercebal/KizukoLib/galaxy/GalaxyCircle.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::galaxy
{

namespace {

inline sf::Color GalaxyLineStyleToColor(GalaxyCircleStyle style)
{
   switch (style)
   {
      //case GalaxyCircleStyle::AxisX: return sf::Color{ 255, 128, 128, 128 };
      //case GalaxyCircleStyle::AxisY: return sf::Color{ 128, 128, 255, 128 };
      case GalaxyCircleStyle::AxisX: return sf::Color{ 255, 255, 255, 128 };
      case GalaxyCircleStyle::AxisY: return sf::Color{ 255, 255, 255, 128 };
      case GalaxyCircleStyle::Major: return sf::Color{ 255, 255, 255, 128 };
      case GalaxyCircleStyle::Minor: return sf::Color{ 255, 255, 255, 64 };
   }

   return sf::Color::White;
}

} // namespace


GalaxyCircle::GalaxyCircle(const GlobalResources & globalResources, GalaxyCircleStyle style_, float radius)
   : GalaxyCircle(globalResources, GalaxyLineStyleToColor(style_), radius)
{
}

GalaxyCircle::GalaxyCircle(const GlobalResources & globalResources, sf::Color color_, float radius)
   : super(globalResources)
   , color{ color_ }
{
   this->setRelativePositions({ { -radius, -radius, 0 },{ 0, 0, 0 },{radius, 0, 0} });
}

void GalaxyCircle::createShapes2D()
{
   GalaxyCircle::Positions & positions = this->getAbsolutePositions();

   if (positions.size() > 0)
   {
      const float radius = std::sqrt(std::pow(positions[2].x - positions[1].x, 2.f) + std::pow(positions[2].y - positions[1].y, 2.f) + std::pow(positions[2].z - positions[1].z, 2.f));
      this->circle.setPosition({ positions[0].x, positions[0].y });
      this->circle.setRadius(radius);
      const size_t minPoints = std::max(static_cast<size_t>(radius / 5.f), static_cast<size_t>(30));
      this->circle.setPointCount(minPoints);
      this->circle.setFillColor(sf::Color::Transparent);
      this->circle.setOutlineColor(this->color);
      this->circle.setOutlineThickness(1.f);
   }
}

void GalaxyCircle::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->circle);
}

std::unique_ptr<GalaxyCircle> GalaxyCircle::clone() const
{
   return std::unique_ptr<GalaxyCircle>(this->cloneImpl());
}

GalaxyCircle * GalaxyCircle::cloneImpl() const
{
   return new GalaxyCircle(*this);
}


} // namespace paercebal::KizukoLib::galaxy
