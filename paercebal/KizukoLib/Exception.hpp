#ifndef PAERCEBAL_x_KIZUKOLIB_x_EXCEPTION_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_EXCEPTION_x_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <sstream>
#include <memory>
#include <exception>
#include <stdexcept>

namespace paercebal::KizukoLib
{

class Exception;

template <typename T>
Exception & operator << (Exception & lhs, const T & value);

class Exception
   : public std::runtime_error
{
public:

   Exception() : std::runtime_error("") {}

   virtual char const* what() const override
   {
      return this->message.c_str();
   }

private:
   std::string             message;

   template <typename T>
   friend Exception & operator << (Exception & lhs, const T & value);
};


template <typename T>
Exception & operator << (Exception & e, const T & value)
{
   std::stringstream str;
   str << value;
   e.message += str.str();
   return e;
}



class ResourceLoadingException : public Exception
{
public:

   ResourceLoadingException() : Exception() {}
};


class ProgramOptionHelpAskedException : public Exception
{
public:

   ProgramOptionHelpAskedException() : Exception() {}
};


} // namespace paercebal::KizukoLib


#endif // PAERCEBAL_x_KIZUKOLIB_x_EXCEPTION_x_HPP


