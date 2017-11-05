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
   : DistanceShape(globalResources_, sf::Color{ 192, 0, 192, 128 }, sf::Color{ 192, 0, 192, 64 }, sf::Color{ 128, 0, 128, 24 }, beginName_, endName_)
{
}

DistanceShape::DistanceShape(const GlobalResources & globalResources_, sf::Color colorLine_, sf::Color colorBaseLine_, sf::Color colorShape_, const std::string & beginName_, const std::string & endName_)
   : super(globalResources_)
{
   this->colorLine = colorLine_;
   this->colorBaseLine = colorBaseLine_;
   this->colorShape = colorShape_;
   this->polygon2D[0].color = this->colorLine;
   this->polygon2D[1].color = this->colorLine;
   this->polygon2D[2].color = this->colorBaseLine;
   this->polygon2D[3].color = this->colorBaseLine;

   this->beginName = beginName_;
   this->endName = endName_;

   this->polygonShape.setPointCount(4);
   this->polygonShape.setFillColor(this->colorShape);
   this->polygonShape.setOutlineColor(this->colorShape);

   this->distanceLabel.setFont(this->getGlobalResources().getFontScifi().font);
   this->distanceLabel.setCharacterSize((this->getGlobalResources().getFontScifi().size * 3) / 4);
   this->distanceLabel.setStyle(sf::Text::Regular);
   this->distanceLabel.setFillColor(sf::Color::White);
}

void DistanceShape::createShapes2D()
{
   DistanceShape::Positions & positions = this->getAbsolutePositions();

   if (positions.size() > 0)
   {
      this->polygon2D[0].position = { positions[0].x, positions[0].y };
      this->polygon2D[1].position = { positions[1].x, positions[1].y };
      this->polygon2D[2].position = { positions[2].x, positions[2].y };
      this->polygon2D[3].position = { positions[3].x, positions[3].y };
      this->center2D = { positions[4].x, positions[4].y };

      this->polygonShape.setPoint(0, this->polygon2D[0].position);
      this->polygonShape.setPoint(1, this->polygon2D[1].position);
      this->polygonShape.setPoint(2, this->polygon2D[2].position);
      this->polygonShape.setPoint(3, this->polygon2D[3].position);

      std::stringstream str;
      str << std::fixed << std::setprecision(2) << this->lightYearsLength << "  LY";
      this->distanceText = str.str();
      this->distanceLabel.setString(this->distanceText);
      this->distanceLabel.setPosition({ this->center2D.x + 20, this->center2D.y - 20 });
   }
}

void DistanceShape::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->polygonShape);
   renderTarget.draw(this->polygon2D.data(), 2, sf::Lines);
   renderTarget.draw(this->polygon2D.data() + 2, 2, sf::Lines);
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

   this->setRelativePositions({ begin3D_, end3D_, baseEnd3D, baseBegin3D, center3D });

   this->lightYearsLength = utilities::getDistance(begin3D_, end3D_);

   return *this;
}



//sf::Vector3f ClusterLine::getBegin3D() const noexcept
//{
//   return this->getRelativePositions().at(0);
//}
//
//sf::Vector3f ClusterLine::getEnd3D() const noexcept
//{
//   return this->getRelativePositions().at(1);
//}
//
//sf::Color ClusterLine::getColor() const noexcept
//{
//   return this->color;
//}


} // namespace paercebal::KizukoLib::clusters
