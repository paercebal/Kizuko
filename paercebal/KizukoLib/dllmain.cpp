#include <paercebal/KizukoLib/dllmain.hpp>

#if defined(_WIN32)

#define NOMINMAX
#include <windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
   switch(fdwReason)
   {
      case DLL_PROCESS_ATTACH:
         {
         }
         break ;
      case DLL_PROCESS_DETACH:
         {
         }
         break ;
      case DLL_THREAD_ATTACH:
         {
         }
         break ;
      case DLL_THREAD_DETACH:
         {
         }
         break ;
   }
   
   return TRUE ;
}


#endif // _WIN32

namespace paercebal::KizukoLib
{

// This is an example of an exported variable
PAERCEBAL_x_KIZUKOLIB_x_API int myDummyExportedVariable = 0 ;

// This is an example of an exported function.
PAERCEBAL_x_KIZUKOLIB_x_API int myDummyExportedFunction()
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see dllmain.h for the class definition
MyDummyExportedClass::MyDummyExportedClass()
{
    return;
}

} // namespace paercebal::KizukoLib


