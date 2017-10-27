#ifndef PAERCEBAL_x_GRAPHICS_x_WORLD_x_OBJECT_x_HPP
#define PAERCEBAL_x_GRAPHICS_x_WORLD_x_OBJECT_x_HPP


#include <paercebal/Graphics/dllmain.hpp>


namespace paercebal::Graphics::world
{

/// @brief Object is the base class of every object inthe 3D world
///
/// Object is a composite, meaning, an Object will possibly have one
/// parent and possibly multiple children.
///
/// The parent/children relation will be of relative position: Each
/// Object has both a position and an orientation relative to its
/// parent. The graphics pipeline will translate those relative
/// positions/orientations into absolute positions/orientations,
/// before doing anything else (e.g. create 2D isometric positions)

class PAERCEBAL_x_GRAPHICS_x_API Object
{
public:
};


} // namespace paercebal::Graphics::world


#endif // PAERCEBAL_x_GRAPHICS_x_WORLD_x_OBJECT_x_HPP


