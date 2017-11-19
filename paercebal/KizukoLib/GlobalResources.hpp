#ifndef PAERCEBAL_x_KIZUKOLIB_x_GLOBAL_RESOURCES_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GLOBAL_RESOURCES_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>

#include <paercebal/KizukoLib/input/Data.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <memory>

namespace paercebal::KizukoLib
{

struct GlobalFont
{
   sf::Font    font;
   int         size = 20;
};

struct GlobalMusic
{
   mutable sf::Music   music;    ///< @todo this "mutable" is a problem. See if we can change the design to accomodate constness and need to play the music
};


class PAERCEBAL_x_KIZUKOLIB_x_API GlobalResources
{
public:

   GlobalResources(int argc, char * argv[]);
   ~GlobalResources();

   GlobalResources(const GlobalResources &) = delete;
   GlobalResources &       operator = (const GlobalResources &) = delete;

   const GlobalFont &      getFontNormal()                           const noexcept;
   const GlobalFont &      getFontScifi()                            const noexcept;
   const GlobalMusic &     getMusicCluster()                         const noexcept;
   const GlobalMusic &     getMusicGalaxy()                          const noexcept;

   const sf::Texture &     getTexture(const std::string path)        const;

   const input::Data &     getData()                                 const noexcept;

private:
   GlobalFont                             fontNormal;
   GlobalFont                             fontScifi;
   GlobalMusic                            musicCluster;
   GlobalMusic                            musicGalaxy;
   input::Data                            data;
   std::map<std::string, sf::Texture>     textures;
};


} // namespace paercebal::KizukoLib


#endif // PAERCEBAL_x_KIZUKOLIB_x_GLOBAL_RESOURCES_x_HPP


