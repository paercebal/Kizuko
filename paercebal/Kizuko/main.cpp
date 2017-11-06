#include <paercebal/Kizuko/main.hpp>

#include <paercebal/KizukoLib/gui/View.hpp>
#include <paercebal/KizukoLib/Exception.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <algorithm>

// VC++2010: Disable  warning C4482: nonstandard extension used: enum 'xyz' used in qualified name
#pragma warning(disable: 4482)



// This code was inspired by Vittorio Romeo's excellent tutorial on SFML:
// https://www.youtube.com/watch?v=_4K3tsKa1Uc
//
// Vittorio's homepage: http://vittorioromeo.info/
//
// The original license for this code can be found at:
// http://opensource.org/licenses/AFL-3.0



#if defined(_WIN32)

#include <windows.h>

extern int main(int argc, char* argv[]);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
   return main(__argc, __argv);
}

#endif // _WIN32



const unsigned int   windowWidth       = 1200;
const unsigned int   windowHeight      = 800;

struct AskedToQuitException {};

int main(int argc, char * argv[])
{
   using namespace paercebal::KizukoLib;
   
   try
   {
      GlobalResources globalResources(argc, argv);
      
      //clusters::Cluster cluster{ globalResources };

      //cluster.addStar(clusters::Star{ globalResources, "0", sf::Color{ 255, 0, 0, 255 },{ 0, 0, 0 }, 5.f });
      //cluster.addStar(clusters::Star{ globalResources, "10x", sf::Color{ 255, 0, 0, 255 },{ 10, 0, 0 }, 5.f });
      //cluster.addStar(clusters::Star{ globalResources, "10y", sf::Color{ 255, 0, 0, 255 },{ 0, 10, 0 }, 5.f });
      //cluster.addStar(clusters::Star{ globalResources, "10z", sf::Color{ 255, 0, 0, 255 },{ 0, 0, 10 }, 5.f });

      gui::View view{ globalResources };

      calculateAbsolutePositionThenShapes2DRecursive(view);

      sf::View sfml_view(sf::Vector2f(0, 0), sf::Vector2f(static_cast<float>(windowWidth), static_cast<float>(windowHeight)));

      sf::ContextSettings settings;
      settings.antialiasingLevel = 8;
      sf::RenderWindow sfml_window(sf::VideoMode(windowWidth, windowHeight), "Kizuko", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close, settings);
      sfml_window.setFramerateLimit(60);
      sfml_window.setView(sfml_view);

      try
      {
         view.getGlobalResources().getMusicCluster().music.play();

         struct DragData
         {
            using Move = sf::Event::MouseMoveEvent;

            bool isMouseLeftButtonPressed = false;
            bool isMouseRightButtonPressed = false;
            sf::Event::MouseMoveEvent old;
            sf::Event::MouseMoveEvent now;
         };

         DragData dragData;

         while (sfml_window.isOpen())
         {
            sf::Event event;

            while (sfml_window.pollEvent(event))
            {
               switch (event.type)
               {
                  case sf::Event::Closed:
                  {
                     sfml_window.close();
                     break;
                  }
                  case sf::Event::KeyPressed:
                  {
                     switch (event.key.code)
                     {
                        case sf::Keyboard::Key::Left:
                        {
                           view.translateXPositive();
                           calculateAbsolutePositionThenShapes2DRecursive(view);
                           break;
                        }
                        case sf::Keyboard::Key::Right:
                        {
                           view.translateXNegative();
                           calculateAbsolutePositionThenShapes2DRecursive(view);
                           break;
                        }
                        case sf::Keyboard::Key::Up:
                        {
                           view.translateYPositive();
                           calculateAbsolutePositionThenShapes2DRecursive(view);
                           break;
                        }
                        case sf::Keyboard::Key::Down:
                        {
                           view.translateYNegative();
                           calculateAbsolutePositionThenShapes2DRecursive(view);
                           break;
                        }
                        case sf::Keyboard::Key::PageUp:
                        {
                           view.zoomIn();
                           calculateAbsolutePositionThenShapes2DRecursive(view);
                           break;
                        }
                        case sf::Keyboard::Key::PageDown:
                        {
                           view.zoomOut();
                           calculateAbsolutePositionThenShapes2DRecursive(view);
                           break;
                        }
                     }
                     break;
                  }
                  case sf::Event::Resized:
                  {
                     sfml_view.setSize({ static_cast<float>(event.size.width), static_cast<float>(event.size.height) });
                     sfml_window.setView(sfml_view);
                     break;
                  }
                  case sf::Event::MouseButtonPressed:
                  {
                     if (event.mouseButton.button == sf::Mouse::Right)
                     {
                        if (!dragData.isMouseRightButtonPressed)
                        {
                           dragData.isMouseRightButtonPressed = true;
                           dragData.old = DragData::Move();
                           dragData.now.x = event.mouseButton.x;
                           dragData.now.y = event.mouseButton.y;
                        }
                     }
                     break;
                  }
                  case sf::Event::MouseButtonReleased:
                  {
                     if (event.mouseButton.button == sf::Mouse::Right)
                     {
                        dragData.isMouseRightButtonPressed = false;
                        dragData.old = DragData::Move();
                        dragData.now = DragData::Move();
                     }

                     //view.setDebugText("");

                     calculateAbsolutePositionThenShapes2DRecursive(view);
                     break;
                  }
                  case sf::Event::MouseMoved:
                  {
                     if (dragData.isMouseRightButtonPressed)
                     {
                        // Dragging around
                        dragData.old = dragData.now;
                        dragData.now = event.mouseMove;
                        view.translateByPixels(dragData.now.x - dragData.old.x, dragData.now.y - dragData.old.y);

                        //std::stringstream str;
                        //str << "Mouse: " << event.mouseMove.x << "x " << event.mouseMove.y << "y\n";
                        //str << "Drag: " << (dragData.now.x - dragData.old.x) << "x " << (dragData.now.y - dragData.old.y) << "y\n";
                        //str << "DragData:\n"; 
                        //str << "   .isMouseLeftButtonPressed: " << dragData.isMouseLeftButtonPressed << "\n";
                        //str << "   .isMouseRightButtonPressed: " << dragData.isMouseRightButtonPressed << "\n";
                        //str << "   .now: " << dragData.now.x << "x " << dragData.now.y << "y\n";
                        //str << "   .old: " << dragData.old.x << "x " << dragData.old.y << "y\n";
                        //view.setDebugText(str.str());

                        calculateAbsolutePositionThenShapes2DRecursive(view);
                     }
                     break;
                  }
                  case sf::Event::MouseWheelScrolled:
                  {
                     //static int tutu = 0;

                     if (event.mouseWheelScroll.delta > 0)
                     {
                        //tutu += 1;
                        //std::stringstream str;
                        //str << "mouseWheelScroll.delta: " << event.mouseWheelScroll.delta << "\n";
                        //str << "tutu: " << tutu << "\n";
                        //view.setDebugText(str.str());

                        view.zoomInByWheel();
                        calculateAbsolutePositionThenShapes2DRecursive(view);
                        event.mouseWheelScroll.delta = 0;
                     }
                     else  if (event.mouseWheelScroll.delta < 0)
                     {
                        //tutu -= 1;
                        //std::stringstream str;
                        //str << "mouseWheelScroll.delta: " << event.mouseWheelScroll.delta << "\n";
                        //str << "tutu: " << tutu << "\n";
                        //view.setDebugText(str.str());

                        view.zoomOutByWheel();
                        calculateAbsolutePositionThenShapes2DRecursive(view);
                        event.mouseWheelScroll.delta = 0;
                     }
                     break;
                  }
               }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
               sfml_window.close();
               throw AskedToQuitException();
            }

            sfml_window.clear(sf::Color::Black);

            //spaceTime.drawInto(sfml_window);
            view.drawInto(sfml_window);

            sfml_window.display();
         }
      }
      catch (const AskedToQuitException & )
      {
      }
   }
   catch (const ProgramOptionHelpAskedException & e)
   {
      paercebal::Kizuko::messageBox("Help", e.what());
      std::cout << e.what() << "\n";
      return 0;
   }
   catch (const std::runtime_error & e)
   {
      paercebal::Kizuko::messageBox("Exception", e.what());
      return 1;
   }

   return 0 ;
}

namespace paercebal::Kizuko
{

void messageBox(const std::string & title, const std::string & text)
{
#if defined(_WIN32)
   ::MessageBox(NULL, text.c_str(), title.c_str(), MB_OK);
#endif
}

} // namespace paercebal::Kizuko



