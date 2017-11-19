#ifndef PAERCEBAL_x_KIZUKOLIB_x_GALAXY_GALAXY_CLUSTER_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GALAXY_GALAXY_CLUSTER_x_HPP

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>


namespace paercebal::KizukoLib::galaxy
{


class PAERCEBAL_x_KIZUKOLIB_x_API GalaxyCluster : public objects::Object
{
   using super = objects::Object;
public:

   GalaxyCluster(const GlobalResources & globalResources, const std::string & name_, sf::Vector3f center_);

   const std::string &                 getName() const;

   virtual void                        createShapes2D()                                      override;
   virtual void                        drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<GalaxyCluster>      clone()                                         const;

private:
   virtual GalaxyCluster *             cloneImpl()                                     const override;

   std::string                         name;
   std::vector<sf::CircleShape>        shapes;
   float                               size;
   sf::Color                           color;
   sf::Color                           coreColor;
   sf::Text                            nameLabel;
};


} // namespace paercebal::KizukoLib::galaxy


#endif // PAERCEBAL_x_KIZUKOLIB_x_GALAXY_GALAXY_CLUSTER_x_HPP

