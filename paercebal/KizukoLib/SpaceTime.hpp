#ifndef PAERCEBAL_x_KIZUKOLIB_x_SPACE_TIME_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_SPACE_TIME_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/IDrawable.hpp>
#include <paercebal/KizukoLib/shapes/Star.hpp>
#include <paercebal/KizukoLib/shapes/HeightLine.hpp>
#include <paercebal/KizukoLib/shapes/DistanceLine.hpp>
#include <paercebal/KizukoLib/shapes/DistanceShape.hpp>

#include <SFML/Graphics.hpp>

#include <vector>

namespace paercebal::KizukoLib
{

class PAERCEBAL_x_KIZUKOLIB_x_API SpaceTime : public IDrawable
{
   using super = IDrawable;
public:
   SpaceTime(const GlobalResources & globalResources_);
   SpaceTime(const GlobalResources & globalResources_, float lightYearsLength_, float increment_, int majorIncrement_, sf::Vector3f size3D_);

   SpaceTime(const SpaceTime &) = delete;
   SpaceTime & operator = (const SpaceTime &) = delete;

   float                            getLightYearsLength() const;
   SpaceTime &                      setLightYearsLength(float lightYearsLength_);
   SpaceTime &                      setIncrement(float increment_);
   SpaceTime &                      setMajorIncrement(int majorIncrement_);
   SpaceTime &                      setSize(sf::Vector3f size3D_);

   virtual void                     drawInto(sf::RenderTarget & renderTarget) const override;

   SpaceTime &                      addStar(const shapes::Star & star);
   SpaceTime &                      addStar(shapes::Star && star);

   SpaceTime &                      addDistance(const shapes::DistanceShape & line);
   SpaceTime &                      addDistance(shapes::DistanceShape && line);

private:

   SpaceTime &                      calculateSpaceTimeLines();

   sf::Vector3f                                 size3D;
   float                                        lightYearsLength     = 20.f;
   float                                        increment            = 20.f;
   int                                          majorIncrement       = 5;

   std::vector<std::unique_ptr<IDrawable>>      linesX;
   std::vector<IDrawablePtr>                    linesY;

   std::vector<shapes::HeightLine>              heightLines;
   std::vector<shapes::DistanceLine>            distanceLines;
   std::vector<shapes::DistanceShape>           distanceShapes;

   std::vector<shapes::Star>                    stars;
};





} // namespace paercebal::KizukoLib


#endif // PAERCEBAL_x_KIZUKOLIB_x_SPACE_TIME_x_HPP
