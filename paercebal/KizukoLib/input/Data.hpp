#ifndef PAERCEBAL_x_KIZUKOLIB_x_INPUT_x_DATA_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_INPUT_x_DATA_x_HPP

#include <SFML/Graphics.hpp>

#include <array>
#include <iostream>
#include <cmath>

namespace paercebal::KizukoLib::input
{

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
   std::string begin;
   std::string end;
};

struct Data
{
   std::string                clusterName;
   float                      lightYearsPixels;
   float                      incrementPixels;
   float                      majorIncrementPixels;
   sf::Vector3f               size;
   std::vector<Star>          stars;
   std::vector<Distance>      distances;
};

}



#endif // PAERCEBAL_x_KIZUKOLIB_x_INPUT_x_DATA_x_HPP