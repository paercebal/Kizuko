#include <paercebal/KizukoLib/clusters/DistanceShape.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <array>
#include <iomanip>

namespace paercebal::KizukoLib::clusters
{

DistanceShape::DistanceShape(const GlobalResources & globalResources_, const std::string & beginName_, const std::string & endName_)
   : DistanceShape(globalResources_, sf::Color{ 128, 192, 255, 96 }, sf::Color{ 0, 192, 192, 48 }, sf::Color{ 0, 128, 128, 18 }, sf::Color{ 128, 192, 255, 96 }, sf::Color{ 192, 0, 192, 48 }, sf::Color{ 128, 0, 128, 18 }, beginName_, endName_)
{
}

DistanceShape::DistanceShape(const GlobalResources & globalResources_, sf::Color upperColorLine_, sf::Color upperColorBaseLine_, sf::Color upperColorShape_, sf::Color lowerColorLine_, sf::Color lowerColorBaseLine_, sf::Color lowerColorShape_, const std::string & beginName_, const std::string & endName_)
   : super(globalResources_)
{
   this->upperColorLine = upperColorLine_;
   this->upperColorBaseLine = upperColorBaseLine_;
   this->upperColorShape = upperColorShape_;
   this->lowerColorLine = lowerColorLine_;
   this->lowerColorBaseLine = lowerColorBaseLine_;
   this->lowerColorShape = lowerColorShape_;
   this->upperLineBetweenStars[0].color = this->upperColorLine;
   this->upperLineBetweenStars[1].color = this->upperColorLine;
   this->upperLineBetweenBases[0].color = this->upperColorBaseLine;
   this->upperLineBetweenBases[1].color = this->upperColorBaseLine;
   this->lowerLineBetweenStars[0].color = this->lowerColorLine;
   this->lowerLineBetweenStars[1].color = this->lowerColorLine;
   this->lowerLineBetweenBases[0].color = this->lowerColorBaseLine;
   this->lowerLineBetweenBases[1].color = this->lowerColorBaseLine;

   this->beginName = beginName_;
   this->endName = endName_;

   this->upperPolygonShape.setFillColor(this->upperColorShape);
   this->upperPolygonShape.setOutlineColor(this->upperColorShape);

   this->lowerPolygonShape.setFillColor(this->lowerColorShape);
   this->lowerPolygonShape.setOutlineColor(this->lowerColorShape);

   this->distanceLabel.setFont(this->getGlobalResources().getFontScifi().font);
   this->distanceLabel.setCharacterSize((this->getGlobalResources().getFontScifi().size * 3) / 4);
   this->distanceLabel.setStyle(sf::Text::Regular);
   this->distanceLabel.setFillColor(sf::Color{ 128, 192, 255, 255 });
}

void DistanceShape::createShapes2D()
{
   DistanceShape::Positions & positions = this->getAbsolutePositions();

   auto to2D = [](const sf::Vector3f & position3D) -> sf::Vector2f
   {
      return { position3D.x, position3D.y };
   };

   if (positions.size() > 0)
   {
      /// @todo use an enum, seriously...
      // We assume we always have 6 positions:
      // 0 - the first star
      // 1 - the second star
      // 2 - the base of the second star
      // 3 - the base of the first star
      // 4 - the center between the first and second star
      // 5 - the intersection between the line (first and second star) and the horizontal plane

      if (this->isFirstStarUpper)
      {
         if (this->isSecondStarUpper)
         {
            // Only upper shape, with four points
            this->upperPolygonShape.setPointCount(4);
            this->lowerPolygonShape.setPointCount(0);

            this->upperPolygonShape.setPoint(0, to2D(positions[0]));
            this->upperPolygonShape.setPoint(1, to2D(positions[1]));
            this->upperPolygonShape.setPoint(2, to2D(positions[2]));
            this->upperPolygonShape.setPoint(3, to2D(positions[3]));

            this->upperLineBetweenStars[0].position = to2D(positions[0]);
            this->upperLineBetweenStars[1].position = to2D(positions[1]);
            this->lowerLineBetweenStars[0].position = {};
            this->lowerLineBetweenStars[1].position = {};

            this->upperLineBetweenBases[0].position = to2D(positions[2]);
            this->upperLineBetweenBases[1].position = to2D(positions[3]);
            this->lowerLineBetweenBases[0].position = {};
            this->lowerLineBetweenBases[1].position = {};
         }
         else
         {
            // Upper and lower shape, with three points each
            this->upperPolygonShape.setPointCount(3);
            this->lowerPolygonShape.setPointCount(3);

            this->upperPolygonShape.setPoint(0, to2D(positions[0]));
            this->upperPolygonShape.setPoint(1, to2D(positions[5]));
            this->upperPolygonShape.setPoint(2, to2D(positions[3]));
            this->lowerPolygonShape.setPoint(0, to2D(positions[1]));
            this->lowerPolygonShape.setPoint(1, to2D(positions[5]));
            this->lowerPolygonShape.setPoint(2, to2D(positions[2]));

            this->upperLineBetweenStars[0].position = to2D(positions[0]);
            this->upperLineBetweenStars[1].position = to2D(positions[5]);
            this->lowerLineBetweenStars[0].position = to2D(positions[5]);
            this->lowerLineBetweenStars[1].position = to2D(positions[1]);

            this->upperLineBetweenBases[0].position = to2D(positions[3]);
            this->upperLineBetweenBases[1].position = to2D(positions[5]);
            this->lowerLineBetweenBases[0].position = to2D(positions[5]);
            this->lowerLineBetweenBases[1].position = to2D(positions[2]);
         }
      }
      else
      {
         if (this->isSecondStarUpper)
         {
            // Upper and lower shape, with three points each
            this->upperPolygonShape.setPointCount(3);
            this->lowerPolygonShape.setPointCount(3);

            this->upperPolygonShape.setPoint(0, to2D(positions[1]));
            this->upperPolygonShape.setPoint(1, to2D(positions[5]));
            this->upperPolygonShape.setPoint(2, to2D(positions[2]));
            this->lowerPolygonShape.setPoint(0, to2D(positions[0]));
            this->lowerPolygonShape.setPoint(1, to2D(positions[5]));
            this->lowerPolygonShape.setPoint(2, to2D(positions[3]));

            this->upperLineBetweenStars[0].position = to2D(positions[5]);
            this->upperLineBetweenStars[1].position = to2D(positions[1]);
            this->lowerLineBetweenStars[0].position = to2D(positions[0]);
            this->lowerLineBetweenStars[1].position = to2D(positions[5]);

            this->upperLineBetweenBases[0].position = to2D(positions[5]);
            this->upperLineBetweenBases[1].position = to2D(positions[2]);
            this->lowerLineBetweenBases[0].position = to2D(positions[3]);
            this->lowerLineBetweenBases[1].position = to2D(positions[5]);
         }
         else
         {
            // Only lower shape, with four points
            this->upperPolygonShape.setPointCount(0);
            this->lowerPolygonShape.setPointCount(4);

            this->lowerPolygonShape.setPoint(0, to2D(positions[0]));
            this->lowerPolygonShape.setPoint(1, to2D(positions[1]));
            this->lowerPolygonShape.setPoint(2, to2D(positions[2]));
            this->lowerPolygonShape.setPoint(3, to2D(positions[3]));

            this->upperLineBetweenStars[0].position = {};
            this->upperLineBetweenStars[1].position = {};
            this->lowerLineBetweenStars[0].position = to2D(positions[0]);
            this->lowerLineBetweenStars[1].position = to2D(positions[1]);

            this->upperLineBetweenBases[0].position = {};
            this->upperLineBetweenBases[1].position = {};
            this->lowerLineBetweenBases[0].position = to2D(positions[2]);
            this->lowerLineBetweenBases[1].position = to2D(positions[3]);
         }
      }

      this->center2D = { positions[4].x, positions[4].y };

      std::stringstream str;
      str << std::fixed << std::setprecision(0) << this->lightYearsLength << "  LY";
      this->distanceText = str.str();
      this->distanceLabel.setString(this->distanceText);
      this->distanceLabel.setPosition({ this->center2D.x + 20, this->center2D.y - 20 });
   }
}

void DistanceShape::drawInto(sf::RenderTarget & renderTarget) const
{
   if (this->upperPolygonShape.getPointCount() > 0) { renderTarget.draw(this->upperPolygonShape); }
   if (this->lowerPolygonShape.getPointCount() > 0) { renderTarget.draw(this->lowerPolygonShape); }

   auto drawLine = [&renderTarget](const std::array<sf::Vertex, 2> & line)
   {
      if (line[0].position != line[1].position) { renderTarget.draw(line.data(), 2, sf::Lines); }
   };

   drawLine(upperLineBetweenStars);
   drawLine(upperLineBetweenBases);
   drawLine(lowerLineBetweenStars);
   drawLine(lowerLineBetweenBases);

   renderTarget.draw(this->distanceLabel);
}

std::unique_ptr<DistanceShape> DistanceShape::clone() const
{
   return std::unique_ptr<DistanceShape>(this->cloneImpl());
}

DistanceShape * DistanceShape::cloneImpl() const
{
   return new DistanceShape(*this);
}

const std::string & DistanceShape::getBeginName() const
{
   return this->beginName;
}

const std::string & DistanceShape::getEndName() const
{
   return this->endName;
}

DistanceShape & DistanceShape::setBeginAndEnd(sf::Vector3f begin3D_, sf::Vector3f end3D_)
{
   sf::Vector3f center3D = utilities::getBarycenter(begin3D_, end3D_, .5f);
   sf::Vector3f baseBegin3D = { begin3D_.x, begin3D_.y, 0 };
   sf::Vector3f baseEnd3D = { end3D_.x, end3D_.y, 0 };
   sf::Vector3f intersection3D = utilities::getBarycenter(begin3D_, end3D_, std::abs(begin3D_.z) / std::abs(end3D_.z - begin3D_.z));

   if (begin3D_.z == 0)
   {
      this->isSecondStarUpper = (end3D_.z >= 0);
      this->isFirstStarUpper = this->isSecondStarUpper;
   }
   else if (end3D_.z == 0)
   {
      this->isFirstStarUpper = (begin3D_.z >= 0);
      this->isSecondStarUpper = this->isFirstStarUpper;
   }
   else
   {
      this->isFirstStarUpper = (begin3D_.z >= 0);
      this->isSecondStarUpper = (end3D_.z >= 0);
   }

   this->setRelativePositions({ begin3D_, end3D_, baseEnd3D, baseBegin3D, center3D, intersection3D });

   this->lightYearsLength = utilities::getDistance(begin3D_, end3D_);

   return *this;
}

} // namespace paercebal::KizukoLib::clusters
