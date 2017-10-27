#ifndef PAERCEBAL_x_KIZUKOLIB_x_PROGRAM_OPTIONS_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_PROGRAM_OPTIONS_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <memory>

namespace paercebal::KizukoLib
{


class PAERCEBAL_x_KIZUKOLIB_x_API ProgramOptions
{
public:

   ProgramOptions(int argc, char * argv[]);
   ~ProgramOptions();

   const std::string &           getClusterFileName()          const noexcept;

private:
   std::string          clusterFileName;
};


} // namespace paercebal::KizukoLib


#endif // PAERCEBAL_x_KIZUKOLIB_x_PROGRAM_OPTIONS_x_HPP


