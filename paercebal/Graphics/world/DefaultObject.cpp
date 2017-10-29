#include <paercebal/Graphics/world/DefaultObject.hpp>


namespace paercebal::Graphics::world
{

/// @brief clones the current object
///
/// @return the unique pointer of the cloned object
///
/// @note Exception guarantee: Strong

std::unique_ptr<DefaultObject> DefaultObject::clone() const
{
   return std::unique_ptr<DefaultObject>(this->cloneImpl());
}

/// @brief implementation of cloneing the current object
///
/// @return the pointer to the cloned object
///
/// @note Exception guarantee: Strong
///
/// @warning this functions does a transfer of ownership. You are supposed to *immediately* put that pointer into a smart pointer.

DefaultObject * DefaultObject::cloneImpl() const
{
   return new DefaultObject(*this);
}


} // namespace paercebal::Graphics::world
