#ifndef PAERCEBAL_x_KIZUKOLIB_x_INPUT_x_DATA_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_INPUT_x_DATA_x_HPP

#include <SFML/Graphics.hpp>

#include <array>
#include <iostream>
#include <cmath>

namespace paercebal::KizukoLib::input
{

struct Font
{
   std::string                filename;
   int                        size = 20;
};

struct Music
{
   std::string                filename;
};

struct Style
{
   std::vector<Font>          fontSciFi;
   std::vector<Font>          fontNormal;
   std::vector<Music>         musicGalaxy;
   std::vector<Music>         musicCluster;
};

template <typename T>
std::vector<std::string> generateResourceList(const std::vector<T> & resources)
{
   std::vector<std::string> v;
   for (const auto & r : resources)
   {
      v.push_back(r.filename);
   }
   return v;
}

struct ClusterData
{
   std::string                name;
   sf::Vector2f               position = {};
};

struct Galaxy
{
   float                      imageRadius;
   std::string                image;
   float                      radius;
   float                      gridIncrement = 0.f;
   float                      gridMajorIncrement = 0.f;
   std::vector<ClusterData>   clusterDataList;
};

struct Star
{
   std::string                name;
   sf::Vector3f               position = {};
   float                      size = 0;
   sf::Color                  color = {};
   sf::Color                  coreColor = {};
   bool                       relay = false;
};

struct Distance
{
   std::string                begin;
   std::string                end;
};

struct Cluster
{
   std::string                name;                         // Not used currently
   float                      gridIncrement = 0.f;
   float                      gridMajorIncrement = 0.f;
   sf::Vector3f               size;
   std::vector<Star>          stars;
   std::vector<Distance>      distances;
};

struct Data
{
   Style                      style;
   Galaxy                     galaxy;
   std::vector<Cluster>       clusters;
};

Data extractDatafromJSon(const std::string & jsonText);


} // namespace paercebal::KizukoLib::input


#endif // PAERCEBAL_x_KIZUKOLIB_x_INPUT_x_DATA_x_HPP