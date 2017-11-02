#include <paercebal/KizukoLib/GlobalResources.hpp>

#include <paercebal/KizukoLib/Exception.hpp>
#include <paercebal/KizukoLib/ProgramOptions.hpp>
#include <paercebal/KizukoLib/utilities.hpp>
#include <paercebal/KizukoLib/input/Data.hpp>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

#include <fstream>

namespace paercebal::KizukoLib
{

namespace {

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


template <typename T>
void extractValue(T & t, const std::string & name, std::string & value)
{
   expectTrue(t.IsObject(), "json data is not an object");
   rapidjson::Value::ConstMemberIterator it = t.FindMember(name.c_str());
   expectTrue(it != t.MemberEnd(), concat("json data has no \"", name, "\" property"));
   expectTrue(it->value.IsString(), concat("json data's \"", name, "\" property is not a string"));
   value = it->value.GetString();
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

input::Star extractStar(const rapidjson::Value & t)
{
   input::Star value;

   expectTrue(t.IsObject(), "json data is not an object");
   extractValue(t, "name", value.name);
   extractValue(t, "x", value.x);
   extractValue(t, "y", value.y);
   extractValue(t, "z", value.z);
   extractValue(t, "size", value.size);
   extractValue(t, "r", value.r);
   extractValue(t, "g", value.g);
   extractValue(t, "b", value.b);
   extractValue(t, "a", value.a);
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

   expectTrue(t.IsArray(), "json data is not an array");
   for (rapidjson::SizeType i = 0; i < t.Size(); ++i)
   {
      distances.push_back(extractDistance(t[i]));
   }

   return distances;
}




} // anonymous namespace

GlobalResources::GlobalResources(int argc, char * argv[])
{
   ProgramOptions o(argc, argv);

   if (o.getClusterFileName().empty())
   {
      throw std::runtime_error("There is no cluster file to read from");
   }

   std::string clusterFileContent = utilities::loadFile(o.getClusterFileName());

   {
      using namespace rapidjson;

      Document document;

      if (document.Parse(clusterFileContent.c_str()).HasParseError())
      {
         Exception e;
         e << document.GetParseError() << ":" << document.GetErrorOffset();

         if (document.GetErrorOffset() < clusterFileContent.size())
         {
            e << "[" << &(clusterFileContent[document.GetErrorOffset()]) << "]";
         }

         throw e;
      }

      input::Data data;

      extractValue(document, "cluster-name", data.clusterName);
      extractValue(document, "ly-pixels", data.lightYearsPixels);
      extractValue(document, "increment", data.increment);
      extractValue(document, "major-increment", data.majorIncrement);
      data.incrementPixels = data.increment;
      data.majorIncrementPixels = data.majorIncrement;
      extractValue(document, "zoom-pixels", data.zoom);
      extractValue(document, "size-x", data.size.x);
      extractValue(document, "size-y", data.size.y);
      extractValue(document, "size-z", data.size.z);

      expectTrue(document.HasMember("stars"), "cluster file json content has no \"stars\" property");
      expectTrue(document.HasMember("distances"), "cluster file json content has no \"distances\" property");

      data.stars = extractStars(document["stars"]);
      data.distances = extractDistances(document["distances"]);

      this->data = data;
   }

   PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(this->neutralFont, "./resources/OpenSans-Regular.ttf");
   PAERCEBAL_x_KIZUKOLIB_x_ASSERT_RESOURCE_LOADING(this->scifiFont, "./resources/Formation Sans Regular.ttf", "./resources/OpenSans-Regular.ttf");
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

const input::Data & GlobalResources::getData() const noexcept
{
   return this->data;
}

} // namespace paercebal::KizukoLib


