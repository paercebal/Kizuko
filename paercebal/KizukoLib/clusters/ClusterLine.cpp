#include <paercebal/KizukoLib/clusters/ClusterLine.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::clusters
{

namespace {

inline sf::Color ClusterLineStyleToColor(ClusterLineStyle style)
{
   switch (style)
   {
      case ClusterLineStyle::AxisX: return sf::Color{ 255, 128, 128, 128 };
      case ClusterLineStyle::AxisY: return sf::Color{ 128, 128, 255, 128 };
      case ClusterLineStyle::Major: return sf::Color{ 255, 255, 255, 64 };
      case ClusterLineStyle::Minor: return sf::Color{ 255, 255, 255, 32 };
   }

   return sf::Color::White;
}

} // namespace


ClusterLine::ClusterLine(const GlobalResources & globalResources, ClusterLineStyle style_, sf::Vector3f begin_, sf::Vector3f end_)
   : ClusterLine(globalResources, ClusterLineStyleToColor(style_), begin_, end_)
{
}

ClusterLine::ClusterLine(const GlobalResources & globalResources, sf::Color color_, sf::Vector3f begin_, sf::Vector3f end_)
   : super(globalResources)
   , color{ color_ }
{
   this->setRelativePositions({ begin_, end_ });
}

void ClusterLine::createShapes2D()
{
   ClusterLine::Positions & positions = this->getAbsolutePositions();

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

void ClusterLine::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->line2D.data(), this->line2D.size(), sf::Lines);
}

std::unique_ptr<ClusterLine> ClusterLine::clone() const
{
   return std::unique_ptr<ClusterLine>(this->cloneImpl());
}

ClusterLine * ClusterLine::cloneImpl() const
{
   return new ClusterLine(*this);
}

sf::Vector3f ClusterLine::getBegin3D() const noexcept
{
   return this->getRelativePositions().at(0);
}

sf::Vector3f ClusterLine::getEnd3D() const noexcept
{
   return this->getRelativePositions().at(1);
}

sf::Color ClusterLine::getColor() const noexcept
{
   return this->color;
}


} // namespace paercebal::KizukoLib::clusters
