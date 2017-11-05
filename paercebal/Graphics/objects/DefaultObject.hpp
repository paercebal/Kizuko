#ifndef PAERCEBAL_x_GRAPHICS_x_OBJECTS_x_DEFAULT_OBJECT_x_HPP
#define PAERCEBAL_x_GRAPHICS_x_OBJECTS_x_DEFAULT_OBJECT_x_HPP


#include <paercebal/Graphics/objects/Object.hpp>

#include <memory>


namespace paercebal::Graphics::objects
{

/// @brief DefaultObject is an instantiable Object, wit no added features

class PAERCEBAL_x_GRAPHICS_x_API DefaultObject : public Object
{
   using super = Object;
public:
   using super::Object;

   std::unique_ptr<DefaultObject>      clone()           const;

private:
   virtual DefaultObject *             cloneImpl()       const;
};


} // namespace paercebal::Graphics::objects


#endif // PAERCEBAL_x_GRAPHICS_x_OBJECTS_x_DEFAULT_OBJECT_x_HPP


