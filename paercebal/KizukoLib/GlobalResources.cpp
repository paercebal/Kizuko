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

   const size_t foundFontNormalIndex = PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(this->fontNormal.font, generateResourceList(this->data.style.fontNormal));
   this->fontNormal.size = this->data.style.fontNormal.at(foundFontNormalIndex).size;
   const size_t foundFontScifiIndex = PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(this->fontScifi.font, generateResourceList(this->data.style.fontSciFi));
   this->fontScifi.size = this->data.style.fontSciFi.at(foundFontScifiIndex).size;

   PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(this->musicCluster.music, generateResourceList(this->data.style.musicCluster));
   PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(this->musicGalaxy.music, generateResourceList(this->data.style.musicGalaxy));
}

GlobalResources::~GlobalResources() = default;


const GlobalFont & GlobalResources::getFontNormal() const noexcept
{
   return this->fontNormal;
}

const GlobalFont & GlobalResources::getFontScifi() const noexcept
{
   return this->fontScifi;
}

const GlobalMusic & GlobalResources::getMusicCluster() const noexcept
{
   return this->musicCluster;
}

const GlobalMusic & GlobalResources::getMusicGalaxy() const noexcept
{
   return this->musicGalaxy;
}

const input::Data & GlobalResources::getData() const noexcept
{
   return this->data;
}

} // namespace paercebal::KizukoLib


