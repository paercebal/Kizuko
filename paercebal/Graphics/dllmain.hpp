#ifndef PAERCEBAL_x_GRAPHICS_x_DLLMAIN_x_HPP
#define PAERCEBAL_x_GRAPHICS_x_DLLMAIN_x_HPP


#if defined(_MSC_VER)

#ifdef PAERCEBAL_x_GRAPHICS_x_EXPORTS
#define PAERCEBAL_x_GRAPHICS_x_API __declspec(dllexport)
#else
#define PAERCEBAL_x_GRAPHICS_x_API __declspec(dllimport)
#pragma comment(lib, "paercebal.Graphics.lib")
#endif

#endif // _MSC_VER

namespace paercebal::Graphics
{

// This class is exported from the dll
class PAERCEBAL_x_GRAPHICS_x_API MyDummyExportedClass {
public:
	MyDummyExportedClass();
	// TODO: add your methods here.
};

extern PAERCEBAL_x_GRAPHICS_x_API int myDummyExportedVariable ;

PAERCEBAL_x_GRAPHICS_x_API int myDummyExportedFunction();

} // namespace paercebal::Graphics

#endif // PAERCEBAL_x_GRAPHICS_x_DLLMAIN_x_HPP


