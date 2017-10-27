#include <paercebal/KizukoLib/ProgramOptions.hpp>

#include <paercebal/KizukoLib/Exception.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <clara.hpp>


namespace paercebal::KizukoLib
{

ProgramOptions::ProgramOptions(int argc, char * argv[])
{
   bool help = false;

   auto cli
      = clara::Help(help)
      + clara::Opt(this->clusterFileName, "cluster")
         ["-c"]["--cluster"]
         ("the cluster json filename");

   auto result = cli.parse(clara::Args(argc, argv));

   if (help)
   {
      ProgramOptionHelpAskedException e;
      e << cli << "\n";
      throw e;
   }
}

ProgramOptions::~ProgramOptions() = default;

const std::string & ProgramOptions::getClusterFileName() const noexcept
{
   return this->clusterFileName;
}


} // namespace paercebal::KizukoLib


