#include <paercebal/Graphics/world/World.hpp>


namespace paercebal::Graphics::world
{

/// @brief clones the current object
///
/// @return the unique pointer of the cloned object
///
/// @note Exception guarantee: Strong

std::unique_ptr<World> World::clone() const
{
   return std::unique_ptr<World>(this->cloneImpl());
}

/// @brief implementation of cloneing the current object
///
/// @return the pointer to the cloned object
///
/// @note Exception guarantee: Strong
///
/// @warning this functions does a transfer of ownership. You are supposed to *immediately* put that pointer into a smart pointer.

World * World::cloneImpl() const
{
   return new World(*this);
}


} // namespace paercebal::Graphics::world
