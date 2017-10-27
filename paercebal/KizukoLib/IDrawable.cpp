#include <paercebal/KizukoLib/IDrawable.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

namespace paercebal::KizukoLib
{


IDrawable::IDrawable(const GlobalResources & globalResources_)
   : globalResources(&globalResources_)
{
   PAERCEBAL_x_KIZUKOLIB_x_ASSERT_POINTER_IS_NOT_NULL(this->globalResources);
}

IDrawable::~IDrawable() = default;

const GlobalResources & IDrawable::getGlobalResources() const noexcept
{
   return *(this->globalResources);
}


} // namespace paercebal::KizukoLib

