#ifndef PAERCEBAL_x_KIZUKOLIB_x_OBJECTS_x_FLAT_IMAGE_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_OBJECTS_x_FLAT_IMAGE_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::objects
{

// IMPORTANT: 3D Units in clusters are in light years.

class PAERCEBAL_x_KIZUKOLIB_x_API FlatImage : public Object
{
   using super = Object;
public:
   FlatImage(const GlobalResources & globalResources_, const std::string & filename_, sf::Vector3f topLeft_, sf::Vector3f bottomRight_);
   virtual ~FlatImage();

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<FlatImage>    clone()                                         const;

   FlatImage &                   setVisible(bool isVisible);
   bool                          isVisible()                                     const;

private:
   virtual FlatImage *           cloneImpl()                                     const override;
   const sf::Texture &           getTexture()                                    const noexcept;


   sf::Vector3f topLeft = {};
   sf::Vector3f bottomRight = {};

   std::string                   filename;
   const sf::Texture *           texture;
   sf::Sprite                    sprite;
   bool                          visible = true;
};


} // namespace paercebal::KizukoLib::objects


#endif // PAERCEBAL_x_KIZUKOLIB_x_OBJECTS_x_FLAT_IMAGE_x_HPP

