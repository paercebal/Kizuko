#ifndef PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_IDRAWABLE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_IDRAWABLE_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>

#include <SFML/Graphics.hpp>

#include <memory>

namespace paercebal::KizukoLib
{


class PAERCEBAL_x_KIZUKOLIB_x_API IDrawable
{
public:
   IDrawable(const GlobalResources & globalResources_);
	virtual ~IDrawable();

	virtual void                  drawInto(sf::RenderTarget & renderTarget)       const = 0;
   const GlobalResources &       getGlobalResources()                            const noexcept;

private:
   const GlobalResources * globalResources;
};


using IDrawablePtr = std::unique_ptr<IDrawable>;
using IDrawableCPtr = std::unique_ptr<const IDrawable>;

} // namespace paercebal::KizukoLib


#endif // PAERCEBAL_x_KIZUKOLIB_x_SHAPES_x_IDRAWABLE_x_HPP

