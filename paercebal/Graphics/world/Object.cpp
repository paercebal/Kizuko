#include <paercebal/Graphics/world/Object.hpp>


namespace paercebal::Graphics::world
{

namespace
{

/// @brief clone the children container
///
/// @param the source children container
///
/// @return the cloned children container

Object::Children cloneChildren(const Object::Children & children)
{
   Object::Children result;
   result.reserve(children.size());

   for (const auto & child : children)
   {
      result.push_back(child->clone());
   }

   return result;
}

} // anonymous namespace

/// @brief copy-constructor
///
/// @param that the object to be copied from
///
/// @note exception guarantee: Strong

Object::Object(const Object & that)
   : center(that.center)
   , relativePositions(that.relativePositions)
   , relativeRotations(that.relativeRotations)
   , absolutePositions(that.absolutePositions)
   , children(cloneChildren(that.children))
{
}

/// @brief copy-assignment operator
///
/// @param that the object to be copied from
///
/// @return the current object
///
/// @note exception guarantee: Strong

Object & Object::operator = (const Object & that)
{
   if (this != &that)
   {
      Object tmp(that);
      *this = std::move(that);
   }

   return *this;
}

/// @brief returns the relative positions of the object
///
/// @return the relative positions
///
/// @note Exception guarantee: Nothrow

const Object::Position & Object::getCenter() const noexcept
{
   return this->center;
}

/// @brief sets the relative positions of the object
///
/// @param position_ the relative positions to be set
///
/// @note Exception guarantee: Strong

Object & Object::setCenter(const Position & center_) noexcept
{
   this->center = center_;
   return *this;
}

/// @brief returns the relative positions of the object
///
/// @return the relative positions
///
/// @note Exception guarantee: Nothrow

const Object::Positions & Object::getRelativePositions() const noexcept
{
   return this->relativePositions;
}

/// @brief sets the relative positions of the object
///
/// @param position_ the relative positions to be set
///
/// @note Exception guarantee: Strong

Object & Object::setRelativePositions(const Positions & relativePositions_)
{
   this->relativePositions = relativePositions_;
   return *this;
}

/// @brief sets the rotation positions of the object
///
/// @param position_ the relative positions to be set
///
/// @note Exception guarantee: Nothrow (assuming the std::vector's swap operator is nothrow)

Object & Object::setRelativePositions(Positions && relativePositions_) noexcept
{
   this->relativePositions.swap(relativePositions_);
   return *this;
}

/// @brief returns the successive rotations of the object
///
/// @return the orientation
///
/// @note Exception guarantee: Nothrow

const Object::Rotations & Object::getRelativeRotations() const noexcept
{
   return this->relativeRotations;
}

/// @brief sets the successive rotations of the object
///
/// @param relativeRotation_ the rotations to be set
///
/// @note Exception guarantee: Nothrow (a sf::Vector3f is a trivial type, with no surprises, unless I missed something)

Object & Object::setRelativeRotations(const Rotations & relativeRotations_)
{
   this->relativeRotations = relativeRotations_;
   return *this;
}

/// @brief sets the successive rotations of the object
///
/// @param relativeRotation_ the rotations to be set
///
/// @note Exception guarantee: Nothrow (assuming the std::vector's swap operator is nothrow)

Object & Object::setRelativeRotations(Rotations && relativeRotations_) noexcept
{
   this->relativeRotations.swap(relativeRotations_);
   return *this;
}

/// @brief returns the absolute positions of this object
///
/// @return the absolute positions
///
/// @note Exception guarantee: Nothrow

const Object::Positions & Object::getAbsolutePositions() const noexcept
{
   return this->absolutePositions;
}

/// @brief returns the absolute positions of this object
///
/// @return the absolute positions
///
/// @note Exception guarantee: Nothrow

Object::Positions & Object::getAbsolutePositions() noexcept
{
   return this->absolutePositions;
}

/// @brief resets the absolute positions of this object
///
/// @return the current object
///
/// @note Exception guarantee: Basic
///
/// @todo when we change the relative positions (and relative rotations), we should mark the absolute positions dirty in some way

Object & Object::resetAbsolutePositions()
{
   for (auto & child : this->children)
   {
      child->resetAbsolutePositions();
   }

   auto reset = [](Positions & absolutePositions, const Positions & relativePositions)
   {
      absolutePositions.resize(relativePositions.size());

      for (auto & position : absolutePositions)
      {
         position.x = 0;
         position.y = 0;
         position.z = 0;
      }
   };

   reset(this->absolutePositions, this->relativePositions);

   return *this;
}

/// @brief returns the children of this object
///
/// @return the children
///
/// @note Exception guarantee: Nothrow

const Object::Children & Object::getChildren() const noexcept
{
   return this->children;
}

/// @brief returns the children of this object
///
/// @return the children
///
/// @note Exception guarantee: Nothrow

Object::Children & Object::getChildren() noexcept
{
   return this->children;
}

/// @brief clones the current object
///
/// @return the unique pointer of the cloned object
///
/// @note Exception guarantee: Strong

std::unique_ptr<Object> Object::clone() const
{
   return std::unique_ptr<Object>(this->cloneImpl());
}

/// @brief implementation of cloneing the current object
///
/// @return the pointer to the cloned object
///
/// @note Exception guarantee: Strong
///
/// @warning this functions does a transfer of ownership. You are supposed to *immediately* put that pointer into a smart pointer.

Object * Object::cloneImpl() const
{
   return new Object(*this);
}

/// @brief calculate the absolute position assuming the current object is the origin
///
/// This is recursive, first working on the children, then on the object itself

Object & Object::calculateAbsolutePositions()
{
   return *this;
}




/*

Simple case: Parent->Child
0. the current object's center is in the parent's origin.
1. The current object's relative positions are set to zero
2. we apply the translation/rotation of the current object (to orient it in the desired way)
2. then we translate the current object depending on the parent's origin


Complex case: Ancestor->Parent->Child
0. all the current objects' centers are in their parent's origin
1. we move to the Child
2. We apply the rotation on the current object (i.e. the child)
3. we translate the current object (i.e. the child) depending on its parent's (i.e. Parent's) origin
4. we move to the current object's parent (i.e. Parent)
5. We apply the rotation on the current object (i.e. the Parent) and all its descendant
5. We translate the current object (i.e. the Parent) and all its descendant on the current object's parent's (i.e. Ancestor's) origin
6. we move to the current object's parent (i.e. Ancestor)
7. etc.

*/
/*
void resetAbsolutePositionsRecursively(Object & current)
{
   current.resetAbsolutePositions();
}

void applyRelativeTransformationsToTheCurrentObjectAbsolutePositions(const Object & origin, Object & object)
{
   for (auto & position : object.getAbsolutePositions())
   {
      position = origin.getCenter() + position;
   }

   for (auto & rotation : origin.getRelativeRotations())
   {
      for (auto & position : object.getAbsolutePositions())
      {
         position = rotation * position;
      }
   }
}

void applyRelativeTransformationsToTheCurrentObjectAndItsDescendentsAbsolutePositions(const Object & origin, Object & object)
{
   for (auto & child : object.getChildren())
   {
      applyRelativeTransformationsToTheCurrentObjectAndItsDescendentsAbsolutePositions(origin, *child);
   }

   applyRelativeTransformationsToTheCurrentObjectAbsolutePositions(object, object);
}

void applyRelativeRotationsToAbsolutePositionsRecursively(Object & object)
{
   for (auto & child : object.getChildren())
   {
      applyRelativeRotationsToAbsolutePositionsRecursively(*child);
   }

   applyRelativeTransformationsToTheCurrentObjectAndItsDescendentsAbsolutePositions(object, object);
}

void calculateAbsolutePositions(Object & current)
{
   resetAbsolutePositionsRecursively(current);


   for (auto & child : this->children)
   {
      child->calculateAbsolutePositions();
   }

   this->applyRotationsOnCurrentAndDescendants(this->relativeRotations);
}

void Object::applyRotationsOnCurrentAndDescendants(const Rotations & rotations)
{
}
*/




} // namespace paercebal::Graphics::world
