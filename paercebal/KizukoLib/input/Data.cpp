#include <paercebal/KizukoLib/input/Data.hpp>

#include <paercebal/KizukoLib/Exception.hpp>

#include <SFML/Graphics.hpp>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

namespace paercebal::KizukoLib::input
{

namespace {

///////////////////////////////////////////////////////////////////////////////
//
// Utils
//
///////////////////////////////////////////////////////////////////////////////

void expectTrue(bool b, const std::string & msg)
{
   if (b != true)
   {
      throw Exception() << msg;
   }
}

void expectFalse(bool b, const std::string & msg)
{
   if (b != false)
   {
      throw Exception() << msg;
   }
}

std::ostream & do_concat(std::ostream & str)
{
   return str;
}

template <typename T, typename... Args>
std::ostream & do_concat(std::ostream & str, const T & value, Args... args)
{
   str << value;
   return do_concat(str, args...);
   return str;
}

template <typename... Args>
std::string concat(Args... args)
{
   std::stringstream str;
   do_concat(str, args...);
   return str.str();
}

///////////////////////////////////////////////////////////////////////////////
//
// Generic: C++
//
///////////////////////////////////////////////////////////////////////////////

template <typename T>
void extractValueImpl(T & t, const std::string & name, std::string & value, bool isFacultative)
{
   expectTrue(t.IsObject(), "json data is not an object");
   rapidjson::Value::ConstMemberIterator it = t.FindMember(name.c_str());
   if (isFacultative)
   {
      if (it == t.MemberEnd())
      {
         value.clear();
         return;
      }
   }
   else
   {
      expectTrue(it != t.MemberEnd(), concat("json data has no \"", name, "\" property"));
   }

   expectTrue(it->value.IsString(), concat("json data's \"", name, "\" property is not a string"));
   value = it->value.GetString();
}

template <typename T>
void extractValueFacultative(T & t, const std::string & name, std::string & value)
{
   extractValueImpl(t, name, value, true);
}

template <typename T>
void extractValue(T & t, const std::string & name, std::string & value)
{
   extractValueImpl(t, name, value, false);
}

template <typename T>
void extractValue(T & t, const std::string & name, bool & value)
{
   expectTrue(t.IsObject(), "json data is not an object");
   rapidjson::Value::ConstMemberIterator it = t.FindMember(name.c_str());
   expectTrue(it != t.MemberEnd(), concat("json data has no \"", name, "\" property"));
   expectTrue(it->value.IsBool(), concat("json data's \"", name, "\" property is not a bool"));
   value = it->value.GetBool();
}

template <typename T>
void extractValue(T & t, const std::string & name, int & value)
{
   expectTrue(t.IsObject(), "json data is not an object");
   rapidjson::Value::ConstMemberIterator it = t.FindMember(name.c_str());
   expectTrue(it != t.MemberEnd(), concat("json data has no \"", name, "\" property"));
   expectTrue(it->value.IsInt(), concat("json data's \"", name, "\" property is not an int"));
   value = it->value.GetInt();
}

template <typename T>
void extractValue(T & t, const std::string & name, unsigned char & value)
{
   expectTrue(t.IsObject(), "json data is not an object");
   rapidjson::Value::ConstMemberIterator it = t.FindMember(name.c_str());
   expectTrue(it != t.MemberEnd(), concat("json data has no \"", name, "\" property"));
   expectTrue(it->value.IsInt(), concat("json data's \"", name, "\" property is not an int"));
   const int valueInt = it->value.GetInt();
   if (valueInt < 0) throw Exception() << "json data's \"" << name << "\" property is less than 0";
   if (valueInt > 255) throw Exception() << "json data's \"" << name << "\" property is greater than 255";
   value = static_cast<unsigned char>(valueInt);
}

template <typename T>
void extractValue(T & t, const std::string & name, float & value)
{
   expectTrue(t.IsObject(), "json data is not an object");
   rapidjson::Value::ConstMemberIterator it = t.FindMember(name.c_str());
   expectTrue(it != t.MemberEnd(), concat("json data has no \"", name, "\" property"));

   expectTrue(it->value.IsNumber(), concat("json data's \"", name, "\" property is not a number"));

   if (it->value.IsInt())
   {
      value = static_cast<float>(it->value.GetInt());
   }
   else if (it->value.IsDouble())
   {
      value = static_cast<float>(it->value.GetDouble());
   }
   else
   {
      throw Exception() << "json data's \"" << name << "\" property is not a float";
   }
}

template <typename T>
void extractValue(T & t, const std::string & name, double & value)
{
   expectTrue(t.IsObject(), "json data is not an object");
   rapidjson::Value::ConstMemberIterator it = t.FindMember(name.c_str());
   expectTrue(it != t.MemberEnd(), concat("json data has no \"", name, "\" property"));

   if (it->value.IsInt())
   {
      value = static_cast<double>(it->value.GetInt());
   }
   else if (it->value.IsDouble())
   {
      value = static_cast<double>(it->value.GetDouble());
   }
   else
   {
      throw Exception() << "json data's \"" << name << "\" property is not a double";
   }
}

///////////////////////////////////////////////////////////////////////////////
//
// Specific: SFML
//
///////////////////////////////////////////////////////////////////////////////

sf::Color parseColorFromString(const std::string & value) // throws std::stringstream::failure
{
   using namespace std::string_literals;

   std::stringstream str(value);
   //auto flags = str.flags();
   //flags &= ~std::ios::skipws; // Unset the skip white space flag
   //str.flags(flags);
   str.exceptions(std::ios::failbit);

   auto extractSeparator = [&str](const char c0)
   {
      char c;
      str >> c;
      if (c != c0)
         throw std::stringstream::failure("Bad separator!");
   };

   auto extractValue = [&str]()
   {
      int i;
      str >> i;
      if (i < 0 || i > 255)
         throw std::stringstream::failure("Bad value!");
      return static_cast<sf::Uint8>(i);
   };

   sf::Color color = sf::Color::Black;

   color.r = extractValue();
   extractSeparator(',');
   color.g = extractValue();
   extractSeparator(',');
   color.b = extractValue();
   extractSeparator(',');
   color.a = extractValue();

   if ((!str.eof()) || (str.fail()))
   {
      throw std::stringstream::failure("Garbage!");
   }

   return color;
}

template <typename T>
void extractValue(T & t, const std::string & name, sf::Color & value)
{
   expectTrue(t.IsObject(), "json data is not an object");
   rapidjson::Value::ConstMemberIterator it = t.FindMember(name.c_str());
   expectTrue(it != t.MemberEnd(), concat("json data has no \"", name, "\" property"));

   expectTrue(it->value.IsString(), concat("json data's \"", name, "\" property should be at least a String"));

   try
   {
      value = parseColorFromString(it->value.GetString());
   }
   catch (const std::stringstream::failure & e)
   {
      throw Exception() << "json data's \"" << name << "\" property is not a sf::Color: " << e.what();
   }
}

sf::Vector2f parse2DDataFromString(const std::string & value) // throws std::stringstream::failure
{
   using namespace std::string_literals;

   std::stringstream str(value);
   //auto flags = str.flags();
   //flags &= ~std::ios::skipws; // Unset the skip white space flag
   //str.flags(flags);
   str.exceptions(std::ios::failbit);

   auto extractSeparator = [&str](const char c0)
   {
      char c;
      str >> c;
      if (c != c0)
         throw std::stringstream::failure("Bad separator!");
   };

   auto extractValue = [&str]()
   {
      float f;
      str >> f;
      return f;
   };

   sf::Vector2f data = {};

   data.x = extractValue();
   extractSeparator(',');
   data.y = extractValue();

   if ((!str.eof()) || (str.fail()))
   {
      throw std::stringstream::failure("Garbage!");
   }

   return data;
}

template <typename T>
void extractValue(T & t, const std::string & name, sf::Vector2f & value)
{
   expectTrue(t.IsObject(), "json data is not an object");
   rapidjson::Value::ConstMemberIterator it = t.FindMember(name.c_str());
   expectTrue(it != t.MemberEnd(), concat("json data has no \"", name, "\" property"));

   expectTrue(it->value.IsString(), concat("json data's \"", name, "\" property should be at least a String"));

   try
   {
      value = parse2DDataFromString(it->value.GetString());
   }
   catch (const std::stringstream::failure & e)
   {
      throw Exception() << "json data's \"" << name << "\" property is not a sf::Vector2f: " << e.what();
   }
}

sf::Vector3f parse3DDataFromString(const std::string & value) // throws std::stringstream::failure
{
   using namespace std::string_literals;

   std::stringstream str(value);
   //auto flags = str.flags();
   //flags &= ~std::ios::skipws; // Unset the skip white space flag
   //str.flags(flags);
   str.exceptions(std::ios::failbit);

   auto extractSeparator = [&str](const char c0)
   {
      char c;
      str >> c;
      if (c != c0)
         throw std::stringstream::failure("Bad separator!");
   };

   auto extractValue = [&str]()
   {
      float f;
      str >> f;
      return f;
   };

   sf::Vector3f data = {};

   data.x = extractValue();
   extractSeparator(',');
   data.y = extractValue();
   extractSeparator(',');
   data.z = extractValue();

   if ((!str.eof()) || (str.fail()))
   {
      throw std::stringstream::failure("Garbage!");
   }

   return data;
}

template <typename T>
void extractValue(T & t, const std::string & name, sf::Vector3f & value)
{
   expectTrue(t.IsObject(), "json data is not an object");
   rapidjson::Value::ConstMemberIterator it = t.FindMember(name.c_str());
   expectTrue(it != t.MemberEnd(), concat("json data has no \"", name, "\" property"));

   expectTrue(it->value.IsString(), concat("json data's \"", name, "\" property should be at least a String"));

   try
   {
      value = parse3DDataFromString(it->value.GetString());
   }
   catch (const std::stringstream::failure & e)
   {
      throw Exception() << "json data's \"" << name << "\" property is not a sf::Vector3f: " << e.what();
   }
}

///////////////////////////////////////////////////////////////////////////////
//
// Specific: Style
//
///////////////////////////////////////////////////////////////////////////////

input::Font extractStyleFont(const rapidjson::Value & t)
{
   input::Font value;

   expectTrue(t.IsObject(), "json 'font' is not an object");
   extractValue(t, "filename", value.filename);
   extractValue(t, "size", value.size);

   return value;
}

std::vector<input::Font> extractStyleFonts(const rapidjson::Value & t)
{
   std::vector<input::Font> fonts;

   expectTrue(t.IsArray(), "json 'fonts' is not an array");
   for (rapidjson::SizeType i = 0; i < t.Size(); ++i)
   {
      fonts.push_back(extractStyleFont(t[i]));
   }

   return fonts;
}

input::Music extractStyleMusic(const rapidjson::Value & t)
{
   input::Music value;

   expectTrue(t.IsObject(), "json 'music' is not an object");
   extractValue(t, "filename", value.filename);

   return value;
}

std::vector<input::Music> extractStyleMusics(const rapidjson::Value & t)
{
   std::vector<input::Music> musics;

   expectTrue(t.IsArray(), "json 'musics' is not an array");
   for (rapidjson::SizeType i = 0; i < t.Size(); ++i)
   {
      musics.push_back(extractStyleMusic(t[i]));
   }

   return musics;
}

input::Style extractStyle(const rapidjson::Value & t)
{
   expectTrue(t.IsObject(), "json 'style' is not an object");

   expectTrue(t.HasMember("font-sci-fi"), "cluster file json content has no \"font-sci-fi\" property");
   expectTrue(t.HasMember("font-normal"), "cluster file json content has no \"font-normal\" property");
   expectTrue(t.HasMember("music-cluster"), "cluster file json content has no \"music-cluster\" property");
   expectTrue(t.HasMember("music-galaxy"), "cluster file json content has no \"music-galaxy\" property");

   input::Style style;

   style.fontSciFi = extractStyleFonts(t["font-sci-fi"]);
   style.fontNormal = extractStyleFonts(t["font-normal"]);
   style.musicCluster = extractStyleMusics(t["music-cluster"]);
   style.musicGalaxy = extractStyleMusics(t["music-galaxy"]);

   return style;
}

///////////////////////////////////////////////////////////////////////////////
//
// Specific: Galaxy
//
///////////////////////////////////////////////////////////////////////////////

input::ClusterData extractClusterData(const rapidjson::Value & t)
{
   input::ClusterData value;

   expectTrue(t.IsObject(), "json 'cluster-data' is not an object");
   extractValue(t, "name", value.name);
   extractValue(t, "position", value.position);

   return value;
}

std::vector<input::ClusterData> extractClusterDatas(const rapidjson::Value & t)
{
   std::vector<input::ClusterData> clusterDatas;

   expectTrue(t.IsArray(), "json 'cluster-data-list' is not an array");
   for (rapidjson::SizeType i = 0; i < t.Size(); ++i)
   {
      clusterDatas.push_back(extractClusterData(t[i]));
   }

   return clusterDatas;
}

input::Galaxy extractGalaxy(const rapidjson::Value & t)
{
   input::Galaxy galaxy;

   expectTrue(t.IsObject(), "json 'galaxy' is not an object");

   extractValue(t, "image-radius", galaxy.imageRadius);
   extractValue(t, "image", galaxy.image);
   extractValue(t, "radius", galaxy.radius);
   extractValue(t, "grid-increment", galaxy.gridIncrement);
   extractValue(t, "grid-major-increment", galaxy.gridMajorIncrement);

   expectTrue(t.HasMember("cluster-data-list"), "cluster file json content has no \"cluster-data-list\" property");
   galaxy.clusterDataList = extractClusterDatas(t["cluster-data-list"]);

   return galaxy;
}

///////////////////////////////////////////////////////////////////////////////
//
// Specific: Clusters
//
///////////////////////////////////////////////////////////////////////////////

input::Star extractStar(const rapidjson::Value & t)
{
   input::Star value;

   expectTrue(t.IsObject(), "json data is not an object");
   extractValue(t, "name", value.name);
   extractValue(t, "position", value.position);
   extractValue(t, "size", value.size);
   extractValue(t, "color", value.color);
   extractValue(t, "core-color", value.coreColor);
   extractValue(t, "relay", value.relay);

   return value;
}

std::vector<input::Star> extractStars(const rapidjson::Value & t)
{
   std::vector<input::Star> stars;

   expectTrue(t.IsArray(), "json data is not an array");
   for (rapidjson::SizeType i = 0; i < t.Size(); ++i)
   {
      stars.push_back(extractStar(t[i]));
   }

   return stars;
}

input::Distance extractDistance(const rapidjson::Value & t)
{
   input::Distance value;

   expectTrue(t.IsObject(), "json data is not an object");
   extractValue(t, "begin", value.begin);
   extractValue(t, "end", value.end);

   return value;
}

std::vector<input::Distance> extractDistances(const rapidjson::Value & t)
{
   std::vector<input::Distance> distances;

   expectTrue(t.IsArray(), "json 'distances' is not an array");
   for (rapidjson::SizeType i = 0; i < t.Size(); ++i)
   {
      distances.push_back(extractDistance(t[i]));
   }

   return distances;
}

input::Cluster extractCluster(const rapidjson::Value & t)
{
   input::Cluster value;

   expectTrue(t.IsObject(), "json 'cluster' is not an object");

   extractValue(t, "name", value.name);
   extractValueFacultative(t, "image", value.image);
   extractValue(t, "grid-increment", value.gridIncrement);
   extractValue(t, "grid-major-increment", value.gridMajorIncrement);
   extractValue(t, "size", value.size);

   expectTrue(t.HasMember("stars"), "cluster file json content has no \"stars\" property");
   expectTrue(t.HasMember("distances"), "cluster file json content has no \"distances\" property");

   value.stars = extractStars(t["stars"]);
   value.distances = extractDistances(t["distances"]);

   return value;
}

std::vector<input::Cluster> extractClusters(const rapidjson::Value & t)
{
   std::vector<input::Cluster> clusters;

   expectTrue(t.IsArray(), "json 'clusters' is not an array");
   for (rapidjson::SizeType i = 0; i < t.Size(); ++i)
   {
      clusters.push_back(extractCluster(t[i]));
   }

   return clusters;
}


} // anonymous namespace

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

Data extractDatafromJSon(const std::string & jsonText)
{
   using namespace rapidjson;

   Document document;

   if (document.Parse(jsonText.c_str()).HasParseError())
   {
      Exception e;
      e << document.GetParseError() << ":" << document.GetErrorOffset();

      if (document.GetErrorOffset() < jsonText.size())
      {
         e << "[" << &(jsonText[document.GetErrorOffset()]) << "]";
      }

      throw e;
   }

   input::Data data;

   // Style
   expectTrue(document.HasMember("style"), "cluster file json content has no \"style\" property");
   data.style = extractStyle(document["style"]);

   // Galaxy
   expectTrue(document.HasMember("galaxy"), "cluster file json content has no \"galaxy\" property");
   data.galaxy = extractGalaxy(document["galaxy"]);

   // Clusters
   expectTrue(document.HasMember("clusters"), "cluster file json content has no \"style\" property");
   data.clusters = extractClusters(document["clusters"]);

   return data;
}

} // namespace paercebal::KizukoLib::input
