#include <paercebal/KizukoLib/SpaceTime.hpp>

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/shapes/SpaceTimeLine.hpp>
#include <paercebal/KizukoLib/shapes/Star.hpp>
#include <paercebal/KizukoLib/shapes/HeightLine.hpp>

#include <SFML/Graphics.hpp>

#include <memory>


namespace paercebal::KizukoLib
{

SpaceTime::SpaceTime(const GlobalResources & globalResources_)
   : SpaceTime(globalResources_
      , globalResources_.getData().lightYearsPixels
      , globalResources_.getData().incrementPixels
      , static_cast<int>(globalResources_.getData().majorIncrementPixels)
      , globalResources_.getData().size)
{
   const float ly = globalResources_.getData().lightYearsPixels;
   for (const auto & star : this->getGlobalResources().getData().stars)
   {
      this->addStar({ this->getGlobalResources(), star.name, sf::Color{ star.r, star.g, star.b, star.a },{ star.x * ly, star.y * ly, star.z * ly }, star.size });
   }

   for (const auto & distance : this->getGlobalResources().getData().distances)
   {
      this->addDistance({ this->getGlobalResources(), distance.begin, distance.end });
   }
}

SpaceTime::SpaceTime(const GlobalResources & globalResources_, float lightYearsLength_, float increment_, int majorIncrement_, sf::Vector3f size3D_)
   : super(globalResources_)
   , lightYearsLength{ lightYearsLength_ }
   , increment{ increment_ }
   , majorIncrement{ majorIncrement_ }
{
   this->setSize(size3D_);
}


void SpaceTime::drawInto(sf::RenderTarget & renderTarget) const
{
   for (auto & u : this->linesX)
   {
      u->drawInto(renderTarget);
   }

   for (auto & u : this->linesY)
   {
      u->drawInto(renderTarget);
   }

   for (auto & u : this->heightLines) { u.drawInto(renderTarget); }
   for (auto & u : this->distanceLines) { u.drawInto(renderTarget); }
   for (auto & u : this->distanceShapes) { u.drawInto(renderTarget); }
   for (auto & u : this->stars) { u.drawInto(renderTarget); }
}

float SpaceTime::getLightYearsLength() const
{
   return this->lightYearsLength;
}

SpaceTime & SpaceTime::setLightYearsLength(float lightYearsLength_)
{
   this->lightYearsLength = lightYearsLength_;
   return *this;
}

SpaceTime & SpaceTime::setIncrement(float increment_)
{
   if (this->increment != increment_)
   {
      this->increment = increment_;

      if (this->majorIncrement != int() && this->size3D != sf::Vector3f())
      {
         this->calculateSpaceTimeLines();
      }
   }

   return *this;
}

SpaceTime & SpaceTime::setMajorIncrement(int majorIncrement_)
{
   if (this->majorIncrement != majorIncrement_)
   {
      this->majorIncrement = majorIncrement_;

      if (this->increment != float() && this->size3D != sf::Vector3f())
      {
         this->calculateSpaceTimeLines();
      }
   }

   return *this;
}

SpaceTime & SpaceTime::setSize(sf::Vector3f size3D_)
{
   if (this->size3D != size3D_)
   {
      this->size3D = size3D_;

      if (this->increment != float() && this->majorIncrement != int())
      {
         return this->calculateSpaceTimeLines();
      }
   }

   return *this;
}

SpaceTime & SpaceTime::calculateSpaceTimeLines()
{
   // iterate over the X and Y dimensions (-X to X, and -Y to Y) and create lines

   std::vector<IDrawablePtr> linesX;
   std::vector<IDrawablePtr> linesY;

   {
      int inc = 0;
      for (float iX = 0, iXMax = this->size3D.x; iX <= iXMax; iX += this->increment, ++inc)
      {
         const sf::Vector3f begin3D{ iX, -this->size3D.y, 0 };
         const sf::Vector3f end3D{ iX, this->size3D.y, 0 };

         const shapes::SpaceTimeStyle style = (inc % this->majorIncrement == 0) ? shapes::SpaceTimeStyle::Major : shapes::SpaceTimeStyle::Minor;

         auto u = std::make_unique<shapes::SpaceTimeLine>(this->getGlobalResources(), style, begin3D, end3D);
         linesX.push_back(std::move(u));
      }
   }

   {
      int inc = 0;
      for (float iX = 0, iXMin = -this->size3D.x; iX >= iXMin; iX -= this->increment, ++inc)
      {
         const sf::Vector3f begin3D{ iX, -this->size3D.y, 0 };
         const sf::Vector3f end3D{ iX, this->size3D.y, 0 };

         const shapes::SpaceTimeStyle style = (inc % this->majorIncrement == 0) ? shapes::SpaceTimeStyle::Major : shapes::SpaceTimeStyle::Minor;

         auto u = std::make_unique<shapes::SpaceTimeLine>(this->getGlobalResources(), style, begin3D, end3D);
         linesX.push_back(std::move(u));
      }
   }

   {
      int inc = 0;
      for (float iY = 0, iYMax = this->size3D.y; iY <= iYMax; iY += this->increment, ++inc)
      {
         const sf::Vector3f begin3D{ -this->size3D.x, iY, 0 };
         const sf::Vector3f end3D{ this->size3D.x, iY, 0 };

         const shapes::SpaceTimeStyle style = (inc % this->majorIncrement == 0) ? shapes::SpaceTimeStyle::Major : shapes::SpaceTimeStyle::Minor;

         auto u = std::make_unique<shapes::SpaceTimeLine>(this->getGlobalResources(), style, begin3D, end3D);
         linesY.push_back(std::move(u));
      }
   }

   {
      int inc = 0;
      for (float iY = 0, iYMin = -this->size3D.y; iY >= iYMin; iY -= this->increment, ++inc)
      {
         const sf::Vector3f begin3D{ -this->size3D.x, iY, 0 };
         const sf::Vector3f end3D{ this->size3D.x, iY, 0 };

         const shapes::SpaceTimeStyle style = (inc % this->majorIncrement == 0) ? shapes::SpaceTimeStyle::Major : shapes::SpaceTimeStyle::Minor;

         auto u = std::make_unique<shapes::SpaceTimeLine>(this->getGlobalResources(), style, begin3D, end3D);
         linesY.push_back(std::move(u));
      }
   }

   this->linesX.swap(linesX);
   this->linesY.swap(linesY);

   return *this;
}



SpaceTime & SpaceTime::addStar(const shapes::Star & star)
{
   return this->addStar(shapes::Star(star));
}

SpaceTime & SpaceTime::addStar(shapes::Star && star)
{
   const auto starCenter = star.getCenter3D();
   const auto starColor = star.getColor();

   this->heightLines.push_back(shapes::HeightLine{ this->getGlobalResources(), starColor, starCenter });
   this->stars.push_back(std::move(star));
   return *this;
}

SpaceTime & SpaceTime::addDistance(const shapes::DistanceShape & shape)
{
   return this->addDistance(shapes::DistanceShape(shape));
}

SpaceTime & SpaceTime::addDistance(shapes::DistanceShape && shape)
{
   auto findStarCenter = [](const std::vector<shapes::Star> & stars, const std::string & name)
   {
      sf::Vector3f center;

      for (const auto & star : stars)
      {
         if (star.getName() == name)
         {
            center = star.getCenter3D();
            break;
         }
      }

      return center;
   };

   shape.setBegin(findStarCenter(this->stars, shape.getBeginName()));
   shape.setEnd(findStarCenter(this->stars, shape.getEndName()));
   shape.setLightYearsLength(this->lightYearsLength);

   this->distanceShapes.push_back(std::move(shape));

   return *this;
}



} // namespace paercebal::KizukoLib

