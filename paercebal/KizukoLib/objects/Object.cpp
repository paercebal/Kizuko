#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::objects
{

Object::Object(const GlobalResources & globalResources_)
   : globalResources(&globalResources_)
{
   PAERCEBAL_x_KIZUKOLIB_x_ASSERT_POINTER_IS_NOT_NULL(this->globalResources);
}

Object::~Object() = default;

const GlobalResources & Object::getGlobalResources() const noexcept
{
   return *(this->globalResources);
}

std::unique_ptr<Object> Object::clone() const
{
   return std::unique_ptr<Object>(this->cloneImpl());
}

PAERCEBAL_x_KIZUKOLIB_x_API void calculateAbsolutePositionThenShapes2DRecursive(Object & o)
{
   Graphics::objects::calculateAbsolutePositionRecursive(o);
   private_::calculateShapes2DRecursive(o);
}

namespace private_
{

PAERCEBAL_x_KIZUKOLIB_x_API void calculateShapes2DRecursive(Object & o)
{
   for (auto & c : o.getChildren())
   {
      // Oops... dynamic_cast-ing is not the fatest way, but for now, we need
      // to go forward on that particular problem.
      // We'll need revisit that inheritance notion in the future
      /// @todo dynamic_cast should be safely replaced by a correct design
      calculateShapes2DRecursive(dynamic_cast<Object&>(*c));
   }

   o.createShapes2D();
}

} // namespace private_


} // namespace paercebal::KizukoLib::objects
