#include <paercebal/KizukoLib/GlobalResources.hpp>

#include <paercebal/KizukoLib/Exception.hpp>
#include <paercebal/KizukoLib/ProgramOptions.hpp>
#include <paercebal/KizukoLib/utilities.hpp>
#include <paercebal/KizukoLib/input/Data.hpp>

#include <fstream>

namespace paercebal::KizukoLib
{

GlobalResources::GlobalResources(int argc, char * argv[])
{
   ProgramOptions o(argc, argv);

   if (o.getClusterFileName().empty())
   {
      throw std::runtime_error("There is no cluster file to read from");
   }

   std::string jsonText = utilities::loadFile(o.getClusterFileName());
   this->data = input::extractDatafromJSon(jsonText);

   PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(this->neutralFont, "./resources/OpenSans-Regular.ttf");
   PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(this->scifiFont, "./resources/Formation Sans Regular.ttf", "./resources/OpenSans-Regular.ttf");
   PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(this->massEffectFont, "./copyrighted/MassEffect.ttf", "./resources/Formation Sans Regular.ttf", "./resources/OpenSans-Regular.ttf");
}

GlobalResources::~GlobalResources() = default;


const sf::Font & GlobalResources::getNeutralFont() const noexcept
{
   return this->neutralFont;
}

const sf::Font & GlobalResources::getScifiFont() const noexcept
{
   return this->scifiFont;
}

const sf::Font & GlobalResources::getMassEffectFont() const noexcept
{
   return this->massEffectFont;
}

const input::Data & GlobalResources::getData() const noexcept
{
   return this->data;
}

} // namespace paercebal::KizukoLib


