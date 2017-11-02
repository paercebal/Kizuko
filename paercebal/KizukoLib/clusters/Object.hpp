#ifndef PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_OBJECT_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_OBJECT_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>

#include <paercebal/Graphics/world/Object.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::clusters
{

// IMPORTANT: 3D Units in clusters are in light years.

class PAERCEBAL_x_KIZUKOLIB_x_API Object : public Graphics::world::Object
{
public:
   Object(const GlobalResources & globalResources_);
   virtual ~Object();

   virtual void                  createShapes2D()                                      = 0;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const = 0;
   std::unique_ptr<Object>       clone()                                         const;

   const GlobalResources &       getGlobalResources()                            const noexcept;

private:
   virtual Object *              cloneImpl()                                     const = 0;

   const GlobalResources *       globalResources;
};


PAERCEBAL_x_KIZUKOLIB_x_API void calculateAbsolutePositionThenShapes2DRecursive(Object & o);

namespace private_
{

PAERCEBAL_x_KIZUKOLIB_x_API void calculateShapes2DRecursive(Object & o);

} // namespace private_

} // namespace paercebal::KizukoLib::clusters


#endif // PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_OBJECT_x_HPP

