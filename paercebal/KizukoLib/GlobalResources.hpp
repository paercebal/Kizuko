#ifndef PAERCEBAL_x_KIZUKOLIB_x_GLOBAL_RESOURCES_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GLOBAL_RESOURCES_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>

#include <paercebal/KizukoLib/input/Data.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <memory>

namespace paercebal::KizukoLib
{


class PAERCEBAL_x_KIZUKOLIB_x_API GlobalResources
{
public:

   GlobalResources(int argc, char * argv[]);
   ~GlobalResources();

   GlobalResources(const GlobalResources &) = delete;
   GlobalResources &       operator = (const GlobalResources &) = delete;

   const sf::Font &        getNeutralFont()              const noexcept;
   const sf::Font &        getScifiFont()                const noexcept;
   const sf::Font &        getMassEffectFont()           const noexcept;
   const input::Data &     getData()                     const noexcept;

private:
   sf::Font                neutralFont;
   sf::Font                scifiFont;
   sf::Font                massEffectFont;
   input::Data             data;
};


} // namespace paercebal::KizukoLib


#endif // PAERCEBAL_x_KIZUKOLIB_x_GLOBAL_RESOURCES_x_HPP


