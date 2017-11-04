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
   , relativeScaling(that.relativeScaling)
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

/// @brief returns the scaling factor of the object
///
/// @return the scaling factor
///
/// @note Exception guarantee: Nothrow

const Object::Scaling & Object::getRelativeScaling() const noexcept
{
   return this->relativeScaling;
}

/// @brief sets the scaling factor of the object
///
/// @param relativeScaling_ the scaling factor to be set
///
/// @note Exception guarantee: Nothrow

Object & Object::setRelativeScaling(const Scaling & relativeScaling_)
{
   this->relativeScaling = relativeScaling_;
   return *this;
}

/// @brief sets the scaling factor of the object
///
/// @param relativeScaling_ the scaling factor to be set
///
/// @note Exception guarantee: Nothrow

Object & Object::setRelativeScaling(Scaling && relativeScaling_) noexcept
{
   this->relativeScaling.swap(relativeScaling_);
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

namespace private_
{

PAERCEBAL_x_GRAPHICS_x_API void initializeAbsolutePositions(Object & o)
{
   if (o.getRelativePositions().empty())
   {
      static const Object::Positions nothing = { maths::utilities::createTranslationVector<float>(0, 0, 0) };
      o.getAbsolutePositions() = nothing;
   }
   else
   {
      o.getAbsolutePositions() = o.getRelativePositions();
   }
}

PAERCEBAL_x_GRAPHICS_x_API void rotateAbsolutePositionsAroundOrigin(const Object & origin, Object & o)
{
   for (const auto & rotation : origin.getRelativeRotations())
   {
      for (auto & position : o.getAbsolutePositions())
      {
         position = rotation * position;
      }
   }
}

PAERCEBAL_x_GRAPHICS_x_API void scaleAbsolutePositionsRelativeToOrigin(const Object & origin, Object & o)
{
   const auto & scaling = origin.getRelativeScaling();

   for (auto & position : o.getAbsolutePositions())
   {
      position = scaling * position;
   }
}

PAERCEBAL_x_GRAPHICS_x_API void translateAbsolutePositionToOriginCoordinates(const Object & origin, Object & o)
{
   for (auto & position : o.getAbsolutePositions())
   {
      position += origin.getCenter();
   }
}

PAERCEBAL_x_GRAPHICS_x_API void calculateAbsolutePosition(Object & o)
{
   rotateAbsolutePositionsAroundOrigin(o, o);
   scaleAbsolutePositionsRelativeToOrigin(o, o);
   translateAbsolutePositionToOriginCoordinates(o, o);
}

PAERCEBAL_x_GRAPHICS_x_API void initializeAndCalculateAbsolutePosition(Object & o)
{
   initializeAbsolutePositions(o);
   calculateAbsolutePosition(o);
}

PAERCEBAL_x_GRAPHICS_x_API void initializeAbsolutePositionsOfCurrentAndDescendants(Object & o)
{
   for (auto & c : o.getChildren())
   {
      initializeAbsolutePositionsOfCurrentAndDescendants(*c);
   }

   initializeAbsolutePositions(o);
}

PAERCEBAL_x_GRAPHICS_x_API void RotateAndScaleAndTranslateAbsolutePositionsOfObjectAccordingToAncestors(std::vector<Object *> & ancestors, Object & o)
{
   auto applyTranslateAndRotate = [&o](Object * origin)
   {
      rotateAbsolutePositionsAroundOrigin(*origin, o);
      scaleAbsolutePositionsRelativeToOrigin(*origin, o);
      translateAbsolutePositionToOriginCoordinates(*origin, o);
   };

   std::for_each(ancestors.rbegin(), ancestors.rend(), applyTranslateAndRotate);
}

PAERCEBAL_x_GRAPHICS_x_API void RotateAndScaleAndTranslateAbsolutePositionsOfObjectAndDescendantsAccordingToAncestors(std::vector<Object *> & ancestors, Object & o)
{
   ancestors.push_back(&o);

   for (auto & c : o.getChildren())
   {
      RotateAndScaleAndTranslateAbsolutePositionsOfObjectAndDescendantsAccordingToAncestors(ancestors, *c);
   }

   RotateAndScaleAndTranslateAbsolutePositionsOfObjectAccordingToAncestors(ancestors, o);

   ancestors.pop_back();
}

PAERCEBAL_x_GRAPHICS_x_API void RotateAndScaleAndTranslateAbsolutePositionsOfDescendants(Object & o)
{
   std::vector<Object *> ancestors;
   ancestors.push_back(&o);

   for (auto & c : o.getChildren())
   {
      RotateAndScaleAndTranslateAbsolutePositionsOfObjectAndDescendantsAccordingToAncestors(ancestors, *c);
   }
}

} // namespace private_

PAERCEBAL_x_GRAPHICS_x_API void calculateAbsolutePositionRecursive(Object & o)
{
   private_::initializeAbsolutePositionsOfCurrentAndDescendants(o);
   private_::RotateAndScaleAndTranslateAbsolutePositionsOfDescendants(o);
}



} // namespace paercebal::Graphics::world
