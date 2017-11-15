#ifndef PAERCEBAL_x_KIZUKOLIB_x_GUI_x_SCREEN_x_HPP
#define PAERCEBAL_x_KIZUKOLIB_x_GUI_x_SCREEN_x_HPP

#include <paercebal/KizukoLib/dllmain.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/clusters/ClusterView.hpp>
#include <paercebal/KizukoLib/galaxy/GalaxyView.hpp>
#include <paercebal/KizukoLib/gui/Button.hpp>
#include <paercebal/KizukoLib/gui/Label.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <string>
#include <sstream>


namespace paercebal::KizukoLib::gui
{


class PAERCEBAL_x_KIZUKOLIB_x_API Screen
{
public:

   Screen(const GlobalResources & globalResources);
   Screen(const Screen & that);
   Screen & operator = (const Screen & that);
   Screen(Screen && that)                                                                    noexcept;
   Screen & operator = (Screen && that)                                                      noexcept;


   const GlobalResources &                   getGlobalResources()                            const;


   void                                      drawInto(sf::RenderTarget & renderTarget)       const;
   std::unique_ptr<Screen>                   clone()                                         const;

   Screen &                                  onLeftKeyPressed();
   Screen &                                  onUpKeyPressed();
   Screen &                                  onRightKeyPressed();
   Screen &                                  onDownKeyPressed();
   Screen &                                  onMouseDragByPixels(int x, int y);
   Screen &                                  onPageUpKeyPressed();
   Screen &                                  onPageDownKeyPressed();
   Screen &                                  onMouseWheelScrollPositive();
   Screen &                                  onMouseWheelScrollNegative();

   Screen &                                  setView(const sf::View & view);

   void                                      warnMouseHovering(int x, int y);
   void                                      warnMouseClicking(sf::Vector2i pressed, sf::Vector2i released);
   void                                      calculateAbsolutePositionThenShapes2DRecursiveIfNeeded();

private:

   virtual Screen *                          cloneImpl()                                     const;

   void                                      onBackFromCluster();
   void                                      onSelectCluster();
   const View *                              getCurrentView()                                const;
   View *                                    getCurrentView();

   const GlobalResources *                   globalResources;
   std::unique_ptr<clusters::ClusterView>    clusterView;
   std::unique_ptr<galaxy::GalaxyView>       galaxyView;
   std::vector<View *>                       views;
   sf::View                                  sfmlView;
};


} // namespace paercebal::KizukoLib::gui





#endif // PAERCEBAL_x_KIZUKOLIB_x_GUI_x_SCREEN_x_HPP

