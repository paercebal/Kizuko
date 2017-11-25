#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_OBSERVER_WIDGET_GUI_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_OBSERVER_WIDGET_GUI_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/gui/Control.hpp>


namespace paercebal::KizukoLib::gui
{


class PAERCEBAL_x_KIZUKOLIB_x_API ObserverWidgetGui
{
public:
   virtual void                  registerWidgetGui(Control & control)      = 0;
   virtual void                  unregisterWidgetGui(Control & control)    = 0;

protected:
   ObserverWidgetGui() = default;
   virtual ~ObserverWidgetGui() = default;
   ObserverWidgetGui(const ObserverWidgetGui &) = default;
   ObserverWidgetGui & operator = (const ObserverWidgetGui &) = default;
   ObserverWidgetGui(ObserverWidgetGui &&) = default;
   ObserverWidgetGui & operator = (ObserverWidgetGui &&) = default;
};


} // namespace paercebal::KizukoLib::gui


#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_OBSERVER_WIDGET_GUI_x_HPP

