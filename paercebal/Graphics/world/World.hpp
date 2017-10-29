#ifndef PAERCEBAL_x_GRAPHICS_x_WORLD_x_WORLD_x_HPP
#define PAERCEBAL_x_GRAPHICS_x_WORLD_x_WORLD_x_HPP


#include <paercebal/Graphics/world/Object.hpp>

#include <memory>


namespace paercebal::Graphics::world
{

/// @brief DefaultObject is an instantiable Object, wit no added features

class PAERCEBAL_x_GRAPHICS_x_API World : public Object
{
   using super = Object;
public:
   using super::Object;

   std::unique_ptr<World>     clone()           const;

private:
   virtual World *            cloneImpl()       const;
};


} // namespace paercebal::Graphics::world


#endif // PAERCEBAL_x_GRAPHICS_x_WORLD_x_WORLD_x_HPP


