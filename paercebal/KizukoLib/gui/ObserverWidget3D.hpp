#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_OBSERVER_WIDGET_3D_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_OBSERVER_WIDGET_3D_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/gui/Control.hpp>


namespace paercebal::KizukoLib::gui
{


class PAERCEBAL_x_KIZUKOLIB_x_API ObserverWidget3D
{
public:
   virtual void                  registerWidget3D(Control & control)    = 0;
   virtual void                  unregisterWidget3D(Control & control)  = 0;

protected:
   ObserverWidget3D() = default;
   virtual ~ObserverWidget3D() = default;
   ObserverWidget3D(const ObserverWidget3D &) = default;
   ObserverWidget3D & operator = (const ObserverWidget3D &) = default;
   ObserverWidget3D(ObserverWidget3D &&) = default;
   ObserverWidget3D & operator = (ObserverWidget3D &&) = default;
};


} // namespace paercebal::KizukoLib::gui


#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_OBSERVER_WIDGET_3D_x_HPP

