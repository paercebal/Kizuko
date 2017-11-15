#include <paercebal/KizukoLib/clusters/AltitudeLine.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <cmath>

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

bool calcultateAltitudePositivity(sf::Vector3f starCenter)
{
   return (starCenter.z >= 0);
}

AltitudeLine::Positions createBaseShape(sf::Vector3f center_, float radius)
{
   AltitudeLine::Positions positions;

   const float count = 16.f;

   positions.push_back({ center_.x, center_.y, 0 });      // the center of the shape

   for (float i = 0.f; i < count; i += 1.f)
   {
      const float angle = 2 * Graphics::maths::utilities::pi<float> * i / count;
      const float x = std::cos(angle) * radius;
      const float y = std::sin(angle) * radius;
      positions.push_back({ center_.x + x, center_.y + y, 0 });
   }

   return positions;
}

float findRatio(const AltitudeLine::Positions & positions, int baseShapePositionsOnlySize, float starSize)
{
   auto findMaxDistance = [](const AltitudeLine::Positions & positions, int baseShapePositionsOnlySize)->float
   {
      auto findDistance = [](const sf::Vector3f & origin, const sf::Vector3f & position)->float
      {
         return static_cast<float>(std::pow(std::pow(origin.x - position.x, 2) + std::pow(origin.y - position.y, 2), .5));
      };

      float maxDistance = 0.f;

      // Note: As we are looking at distances from a circle, we don't need to go all around 2 PI.
      // Going up to 1/2 PI is enough, as long as the number of points is a multiple of 4.
      for (size_t i = 0, iMax = (baseShapePositionsOnlySize - 1) / 4; i < iMax; ++i)
      {
         auto currentDistance = findDistance(positions[1], positions[2 + i]);
         if (maxDistance < currentDistance)
         {
            maxDistance = currentDistance;
         }
      }

      return maxDistance;
   };

   const auto maxDistance = findMaxDistance(positions, baseShapePositionsOnlySize);

   return starSize / maxDistance;
};

void calculateBaseShapePositions(sf::ConvexShape & baseShape, const AltitudeLine::Positions & allRelativePositions, int allBaseShapePositionsSize, float starSize)
{
   auto to2D = [](float ratio, sf::Vector3f origin, sf::Vector3f position)->sf::Vector2f
   {
      return { (position.x - origin.x) * ratio + origin.x, (position.y - origin.y) * ratio + origin.y };
   };

   const auto ratio = 1 * findRatio(allRelativePositions, allBaseShapePositionsSize, starSize);

   baseShape.setPointCount(allBaseShapePositionsSize - 1);

   for (size_t i = 0, iMax = allBaseShapePositionsSize - 1; i < iMax; ++i)
   {
      auto point = to2D(ratio, allRelativePositions[1], allRelativePositions[2 + i]);
      baseShape.setPoint(i, point);
   }
};


} // namespace

AltitudeLine::AltitudeLine(const GlobalResources & globalResources, sf::Vector3f starCenter)
   : super(globalResources)
   , color{ defineColor(starCenter) }
   , isAltitudePositive{ calcultateAltitudePositivity(starCenter) }
{
   AltitudeLine::Positions relativePositions;

   relativePositions.push_back({ starCenter });       // the star itself

   // Now, we append the points of the base shape
   auto basePositions = createBaseShape(starCenter, 10.f);
   this->baseShapePointCount = static_cast<int>(basePositions.size());
   relativePositions.insert(relativePositions.end(), basePositions.begin(), basePositions.end());

   this->setRelativePositions(relativePositions);
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

      this->baseShape.setFillColor(sf::Color::Transparent);
      this->baseShape.setOutlineColor(this->color);
      this->baseShape.setOutlineThickness(1.f);
      calculateBaseShapePositions(this->baseShape, positions, this->baseShapePointCount - 1, 5.f);
   }
}

void AltitudeLine::drawInto(sf::RenderTarget & renderTarget) const
{
   if (isAltitudePositive)
   {
      renderTarget.draw(this->baseShape);
      renderTarget.draw(this->line2D.data(), this->line2D.size(), sf::Lines);
   }
   else
   {
      renderTarget.draw(this->line2D.data(), this->line2D.size(), sf::Lines);
      renderTarget.draw(this->baseShape);
   }
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
