#include <paercebal/KizukoLib/objects/FlatImage.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::objects
{

FlatImage::FlatImage(const GlobalResources & globalResources_, const std::string & filename_, sf::Vector3f topLeft_, sf::Vector3f bottomRight_)
   : super(globalResources_)
   , topLeft{ topLeft_ }
   , bottomRight{ bottomRight_ }
   , filename(filename_)
{
   this->image.loadFromFile(this->filename);
   this->image.setSmooth(true);

   this->sprite.setTexture(this->image);
   //this->sprite.setColor(sf::Color(255, 255, 255, 96));

   this->setRelativePositions({ topLeft_, bottomRight_ });
}

FlatImage::~FlatImage() = default;

std::unique_ptr<FlatImage> FlatImage::clone() const
{
   return std::unique_ptr<FlatImage>(this->cloneImpl());
}

FlatImage * FlatImage::cloneImpl() const
{
   return new FlatImage(*this);
}

FlatImage & FlatImage::setVisible(bool isVisible)
{
   this->visible = isVisible;
   return *this;
}

bool FlatImage::isVisible() const
{
   return this->visible;
}

void FlatImage::createShapes2D()
{
   FlatImage::Positions & positions = this->getAbsolutePositions();

   if (positions.size() > 0)
   {
      auto topLeft = positions[0];
      auto bottomRight = positions[1];

      auto width = bottomRight.x - topLeft.x;
      auto height = bottomRight.y - topLeft.y;

      auto imageSize = this->image.getSize();

      auto scaleX = width / static_cast<float>(imageSize.x);
      auto scaleY = height / static_cast<float>(imageSize.y);

      this->sprite.setScale(sf::Vector2f(scaleX, scaleY));
      this->sprite.setPosition(topLeft.x, topLeft.y);
   }
}

void FlatImage::drawInto(sf::RenderTarget & renderTarget) const
{
   if (this->visible)
   {
      renderTarget.draw(this->sprite);
   }
}

} // namespace paercebal::KizukoLib::objects
