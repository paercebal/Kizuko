#include <paercebal/KizukoLib/clusters/AltitudeLine.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::clusters
{

namespace {

const sf::Color PositiveAltitudeColor{ 0, 128, 0, 255 };
const sf::Color NegativeAltitudeColor{ 128, 0, 0, 255 };

sf::Color defineColor(sf::Vector3f starCenter)
{
   if (starCenter.z >= 0)
   {
      return PositiveAltitudeColor;
   }

   return NegativeAltitudeColor;
}

} // namespace

AltitudeLine::AltitudeLine(const GlobalResources & globalResources, sf::Vector3f starCenter)
   : super(globalResources)
   , color{ defineColor(starCenter) }
{
   this->setRelativePositions({ starCenter, { starCenter.x, starCenter.y, 0} });
}

void AltitudeLine::createShapes2D()
{
   AltitudeLine::Positions & positions = this->getAbsolutePositions();

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

void AltitudeLine::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->line2D.data(), this->line2D.size(), sf::Lines);
}

std::unique_ptr<AltitudeLine> AltitudeLine::clone() const
{
   return std::unique_ptr<AltitudeLine>(this->cloneImpl());
}

AltitudeLine * AltitudeLine::cloneImpl() const
{
   return new AltitudeLine(*this);
}

sf::Vector3f AltitudeLine::getBegin3D() const noexcept
{
   return this->getRelativePositions().at(0);
}

sf::Vector3f AltitudeLine::getEnd3D() const noexcept
{
   return this->getRelativePositions().at(1);
}

sf::Color AltitudeLine::getColor() const noexcept
{
   return this->color;
}


} // namespace paercebal::KizukoLib::clusters
