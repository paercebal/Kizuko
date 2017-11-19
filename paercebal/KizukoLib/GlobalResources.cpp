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

   {
      const std::string & path = this->data.galaxy.image;
      sf::Texture & texture = this->textures[this->data.galaxy.image];
      PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(texture, this->data.galaxy.image);
   }

   {
      std::string emptyPath;
      sf::Texture & texture = this->textures[emptyPath];
      PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(texture, "./resources/cluster-empty.png");
   }

   for (const auto & cluster : this->data.clusters)
   {
      if (!cluster.image.empty())
      {
         sf::Texture & texture = this->textures[cluster.image];
         PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(texture, cluster.image, "./resources/cluster-empty.png");
      }
   }
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

const sf::Texture & GlobalResources::getTexture(const std::string path) const
{
   auto it = this->textures.find(path);

   if (it != this->textures.end())
   {
      return it->second;
   }

   throw Exception() << "Texture " << path << " wasn't loaded at initialization.";
}

} // namespace paercebal::KizukoLib


