#ifndef PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_STAR_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_STAR_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/gui/Control.hpp>
#include <paercebal/KizukoLib/gui/ObserverWidget3D.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::clusters
{


class PAERCEBAL_x_KIZUKOLIB_x_API Star : public objects::Object, public gui::Control
{
   using super = objects::Object;
public:

   Star(const GlobalResources & globalResources, const std::string & name_, sf::Color color_, sf::Color coreColor_, sf::Vector3f center_, float size_);

   const std::string &           getName() const;
   sf::Color                     getColor() const;

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<Star>         clone()                                         const;

   void                          registerIntoObserver(gui::ObserverWidget3D & observerWidget3D_);
   void                          unregisterFromObserver();

private:
   virtual Star *                cloneImpl()                                     const override;

   gui::ObserverWidget3D *       observerWidget3D = nullptr;
   std::string                   name;
   std::vector<sf::CircleShape>  shapes;
   float                         size;
   sf::Color                     color;
   sf::Color                     coreColor;
   sf::Text                      nameLabel;
};


} // namespace paercebal::KizukoLib::clusters


#endif // PAERCEBAL_x_KIZUKOLIB_x_CLUSTERS_x_STAR_x_HPP

