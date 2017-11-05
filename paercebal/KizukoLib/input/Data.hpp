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
   float                      x = 0;
   float                      y = 0;
};

struct Galaxy
{
   sf::Vector2f               size;
   std::vector<ClusterData>   clusterDataList;
};

struct Star
{
   std::string                name;
   float                      x = 0;
   float                      y = 0;
   float                      z = 0;
   float                      size = 0;
   unsigned char              r = 0;
   unsigned char              g = 0;
   unsigned char              b = 0;
   unsigned char              a = 0;
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
   float                      increment = 0.f;
   float                      majorIncrement = 0.f;
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