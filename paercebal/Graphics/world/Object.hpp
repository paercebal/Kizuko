#ifndef PAERCEBAL_x_GRAPHICS_x_WORLD_x_OBJECT_x_HPP
#define PAERCEBAL_x_GRAPHICS_x_WORLD_x_OBJECT_x_HPP


#include <paercebal/Graphics/dllmain.hpp>

#include <paercebal/Graphics/maths/Matrix3D.hpp>
#include <paercebal/Graphics/maths/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>


namespace paercebal::Graphics::world
{

/// @brief Object is the base class of every object in the 3D world
///
/// Object is a composite, meaning, an Object will possibly have one
/// parent and possibly multiple children.
///
/// The parent/children relation will be of relative position: Each
/// Object has both a position and an orientation relative to its
/// parent. The graphics pipeline will translate those relative
/// positions/orientations into absolute positions/orientations,
/// before doing anything else (e.g. create 2D isometric positions)
///
/// @note the encapsulation could be overkill. There are no real invariants, there. Or are there?

class PAERCEBAL_x_GRAPHICS_x_API Object
{
protected:
   Object()                                                 = default;
   Object(const Object & that);
   Object & operator = (const Object & that);
   Object(Object &&)                            noexcept    = default;
   Object & operator = (Object &&)              noexcept    = default;

public:

   using Position = sf::Vector3f;
   using Positions = std::vector<sf::Vector3f>;
   using Rotation = maths::Matrix3D<float>;
   using Rotations = std::vector<maths::Matrix3D<float>>;
   using Children = std::vector<std::unique_ptr<Object>>;

   virtual ~Object()                                        = default;

   const Position &                    getCenter()                                                                      const noexcept;
   Object &                            setCenter(const Position & center_)                                                    noexcept;

   const Positions &                   getRelativePositions()                                                           const noexcept;
   Object &                            setRelativePositions(const Positions & relativePositions_);
   Object &                            setRelativePositions(Positions && relativePositions_)                                  noexcept;

   const Rotations &                   getRelativeRotations()                                                           const noexcept;
   Object &                            setRelativeRotations(const Rotations & relativeRotation_);
   Object &                            setRelativeRotations(Rotations && relativeRotation_)                                   noexcept;

   const Positions &                   getAbsolutePositions()                                                           const noexcept;
   Positions &                         getAbsolutePositions()                                                                 noexcept;
   Object &                            resetAbsolutePositions();

   std::unique_ptr<Object>             clone()                                                                          const;

   const Children &                    getChildren()                                                                    const noexcept;
   Children &                          getChildren()                                                                          noexcept;

protected:
   Object &                            calculateAbsolutePositions();

private:
   virtual Object *                    cloneImpl()                                                                      const;

   Position                            center;                       ///< position of the center of the object, relative to its parent
   Positions                           relativePositions;            ///< positions of each important point of the object, relative to its center
   Rotations                           relativeRotations;            ///< rotations of the object, in successive order of application, relative to its center
   Positions                           absolutePositions;            ///< positions of each important point of the object, in absolute coordinates

   Children                            children;                     ///< the children objects of the current object
};

PAERCEBAL_x_GRAPHICS_x_API void calculateAbsolutePositionRecursive(Object & o);

namespace private_
{

PAERCEBAL_x_GRAPHICS_x_API void initializeAbsolutePositions(Object & o);
PAERCEBAL_x_GRAPHICS_x_API void rotateAbsolutePositionsAroundCenter(const Object & center, Object & o);
PAERCEBAL_x_GRAPHICS_x_API void translateAbsolutePositionToCenterCoordinates(const Object & center, Object & o);
PAERCEBAL_x_GRAPHICS_x_API void calculateAbsolutePosition(Object & o);
PAERCEBAL_x_GRAPHICS_x_API void initializeAndCalculateAbsolutePosition(Object & o);
PAERCEBAL_x_GRAPHICS_x_API void initializeAbsolutePositionsOfCurrentAndDescendants(Object & o);
PAERCEBAL_x_GRAPHICS_x_API void RotateAndTranslateAbsolutePositionsOfObjectAccordingToAncestors(std::vector<Object *> & ancestors, Object & o);
PAERCEBAL_x_GRAPHICS_x_API void RotateAndTranslateAbsolutePositionsOfObjectAndDescendantsAccordingToAncestors(std::vector<Object *> & ancestors, Object & o);
PAERCEBAL_x_GRAPHICS_x_API void RotateAndTranslateAbsolutePositionsOfDescendants(Object & o);

} // namespace private_

} // namespace paercebal::Graphics::world


#endif // PAERCEBAL_x_GRAPHICS_x_WORLD_x_OBJECT_x_HPP


