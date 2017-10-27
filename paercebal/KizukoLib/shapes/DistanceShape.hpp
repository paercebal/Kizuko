#ifndef PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_DISTANCE_SHAPE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_DISTANCE_SHAPE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/shapes/AbstractLine.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <array>
#include <iomanip>

namespace paercebal::KizukoLib::shapes
{

class DistanceShape : public IDrawable
{
   using super = IDrawable;
public:
   DistanceShape(const GlobalResources & globalResources_, const std::string & beginName_, const std::string & endName_);
   DistanceShape(const GlobalResources & globalResources_, sf::Color colorLine_, sf::Color colorBaseLine_, sf::Color colorShape_, const std::string & beginName_, const std::string & endName_);

   DistanceShape &            setBegin(sf::Vector3f begin3D_);
   DistanceShape &            setEnd(sf::Vector3f begin3D_);
   DistanceShape &            setLightYearsLength(float lightYearsLength_);

   const std::string &        getBeginName() const;
   const std::string &        getEndName() const;

   virtual void               drawInto(sf::RenderTarget & renderTarget) const override;

private:

   void                       calculateDistanceInLightYears();

   sf::ConvexShape               polygonShape;
   std::array<sf::Vertex, 4>     polygon2D;
   sf::Vector3f                  begin3D;
   sf::Vector3f                  end3D;
   sf::Vector3f                  center3D;
   sf::Vector2f                  center2D;
   sf::Vector3f                  baseEnd3D;
   sf::Vector3f                  baseBegin3D;
   sf::Color                     colorShape;
   sf::Color                     colorLine;
   sf::Color                     colorBaseLine;
   float                         lightYearsLength                 = 0;
   std::string                   distanceText;
   sf::Text                      distanceLabel;

   std::string beginName;
   std::string endName;
};


inline DistanceShape::DistanceShape(const GlobalResources & globalResources_, const std::string & beginName_, const std::string & endName_)
   : DistanceShape(globalResources_, sf::Color{ 192, 0, 192, 128 }, sf::Color{ 192, 0, 192, 64 }, sf::Color{ 128, 0, 128, 24 }, beginName_, endName_)
{
}

inline DistanceShape::DistanceShape(const GlobalResources & globalResources_, sf::Color colorLine_, sf::Color colorBaseLine_, sf::Color colorShape_, const std::string & beginName_, const std::string & endName_)
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

   this->distanceLabel.setFont(this->getGlobalResources().getScifiFont());
   this->distanceLabel.setCharacterSize(7);
   this->distanceLabel.setStyle(sf::Text::Regular);
   this->distanceLabel.setFillColor(sf::Color::White);
}

inline DistanceShape & DistanceShape::setBegin(sf::Vector3f begin3D_)
{
   this->begin3D = begin3D_;
   this->center3D = utilities::getBarycenter(this->begin3D, this->end3D, .5f);
   this->baseBegin3D = { begin3D_.x, begin3D_.y, 0 };

   this->polygon2D[0].position = utilities::convert_3D_to_iso2D(this->begin3D);
   this->polygon2D[3].position = utilities::convert_3D_to_iso2D(this->baseBegin3D);
   this->center2D = utilities::convert_3D_to_iso2D(this->center3D);

   this->polygonShape.setPoint(0, this->polygon2D[0].position);
   this->polygonShape.setPoint(3, this->polygon2D[3].position);

   this->calculateDistanceInLightYears();

   return *this;
}

inline DistanceShape & DistanceShape::setEnd(sf::Vector3f end3D_)
{
   this->end3D = end3D_;
   this->center3D = utilities::getBarycenter(this->begin3D, this->end3D, .5f);
   this->baseEnd3D = { end3D_.x, end3D_.y, 0 };

   this->polygon2D[1].position = utilities::convert_3D_to_iso2D(this->end3D);
   this->polygon2D[2].position = utilities::convert_3D_to_iso2D(this->baseEnd3D);
   this->center2D = utilities::convert_3D_to_iso2D(this->center3D);

   this->polygonShape.setPoint(1, this->polygon2D[1].position);
   this->polygonShape.setPoint(2, this->polygon2D[2].position);

   this->calculateDistanceInLightYears();

   return *this;
}

inline DistanceShape & DistanceShape::setLightYearsLength(float lightYearsLength_)
{
   this->lightYearsLength = lightYearsLength_;
   this->calculateDistanceInLightYears();
   return *this;
}


void DistanceShape::calculateDistanceInLightYears()
{
   if (this->lightYearsLength != 0)
   {
      auto distance3D = utilities::getDistance(this->begin3D, this->end3D) / this->lightYearsLength;
      std::stringstream str;
      str << std::fixed << std::setprecision(2)  << distance3D << "  LY";
      this->distanceText = str.str();
      this->distanceLabel.setString(this->distanceText);

      this->distanceLabel.setPosition({ this->center2D.x + 20, this->center2D.y - 20 });
   }
}



inline const std::string & DistanceShape::getBeginName() const
{
   return this->beginName;
}

inline const std::string & DistanceShape::getEndName() const
{
   return this->endName;
}

inline void DistanceShape::drawInto(sf::RenderTarget & renderTarget) const
{
   renderTarget.draw(this->polygonShape);
   renderTarget.draw(this->polygon2D.data(), 2, sf::Lines);
   renderTarget.draw(this->polygon2D.data() + 2, 2, sf::Lines);
   renderTarget.draw(this->distanceLabel);
}



} // namespace paercebal::KizukoLib::shapes





#endif // PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_DISTANCE_SHAPE_x_HPP

