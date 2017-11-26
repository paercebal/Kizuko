#ifndef PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_VIEW_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_VIEW_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/objects/Object.hpp>
#include <paercebal/KizukoLib/galaxy/Galaxy.hpp>
#include <paercebal/KizukoLib/gui/View.hpp>
#include <paercebal/KizukoLib/gui/Button.hpp>
#include <paercebal/KizukoLib/gui/Label.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <string>
#include <sstream>


namespace paercebal::KizukoLib::galaxy
{


struct GalaxyViewCommands
{
   std::function<void(const std::string &)> onSelectCluster;
};


class PAERCEBAL_x_KIZUKOLIB_x_API GalaxyView : public gui::View
{
   using super = gui::View;
public:

   GalaxyView(const GlobalResources & globalResources, GalaxyViewCommands galaxyViewCommands);

   virtual void                  createShapes2D()                                      override;
   virtual void                  drawInto(sf::RenderTarget & renderTarget)       const override;
   std::unique_ptr<GalaxyView>   clone()                                         const;

private:
   GalaxyView(const GlobalResources & globalResources, GalaxyViewCommands galaxyViewCommands, float translationIncrement_);

   virtual GalaxyView *          cloneImpl()                                     const override;

   galaxy::Galaxy *              galaxy = nullptr;
   GalaxyViewCommands            commands;
   gui::Button                   button;
   gui::Label                    label;
};

//PAERCEBAL_x_KIZUKOLIB_x_API void calculateAbsolutePositionThenShapes2DRecursiveIfNeeded(GalaxyView & view);


} // namespace paercebal::KizukoLib::galaxy





#endif // PAERCEBAL_x_KIZUKOLIB_x_GALAXY_x_GALAXY_VIEW_x_HPP

