#include <paercebal/Kizuko/main.hpp>

#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/SpaceTime.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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

int main(int argc, char * argv[])
{
   using namespace paercebal::KizukoLib;
   
   try
   {
      GlobalResources globalResources(argc, argv);
      
      //SpaceTime spaceTime{ globalResources, 20, 20, 5, sf::Vector3f{ 1000, 1000, 1000 } };
      //spaceTime.addStar({ globalResources, "Aaaa", sf::Color{ 255, 255, 0, 255 },{ 0.f, 0.f, 0.f }, 5 });
      //spaceTime.addStar({ globalResources, "Bbbb", sf::Color{ 255, 0, 0, 255 },{ 200.f, -100.f, -100.f }, 7 });
      //spaceTime.addStar({ globalResources, "Cccc", sf::Color{ 128, 128, 255, 255 },{ 200.f, -300.f, 100.f }, 6 });
      //spaceTime.addDistance({ globalResources, "Aaaa", "Bbbb" });
      //spaceTime.addDistance({ globalResources, "Cccc", "Bbbb" });

      SpaceTime spaceTime{ globalResources };

      sf::View sfml_view(sf::Vector2f(0, 0), sf::Vector2f(static_cast<float>(windowWidth), static_cast<float>(windowHeight)));

      sf::ContextSettings settings;
      settings.antialiasingLevel = 8;
      sf::RenderWindow sfml_window(sf::VideoMode(windowWidth, windowHeight), "Mass Effect Clusters", sf::Style::Titlebar | sf::Style::Close, settings);
      sfml_window.setFramerateLimit(60);
      sfml_window.setView(sfml_view);


      while (sfml_window.isOpen())
      {
         sf::Event event;

         while (sfml_window.pollEvent(event))
         {
            if (event.type == sf::Event::Closed)
            {
               sfml_window.close();
            }
         }

         sfml_window.clear(sf::Color::Black);

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
         {
            break;
         }

         if (event.type == sf::Event::MouseWheelScrolled)
         {
            //if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            //   std::cout << "wheel type: vertical" << std::endl;
            //else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
            //   std::cout << "wheel type: horizontal" << std::endl;
            //else
            //   std::cout << "wheel type: unknown" << std::endl;
            //std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
            //std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
            //std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
            if (event.mouseWheelScroll.delta > 0)
            {
               sfml_view.zoom(1.01f);
               sfml_window.setView(sfml_view);
            }
            else if (event.mouseWheelScroll.delta < 0)
            {
               sfml_view.zoom(1.f / 1.01f);
               sfml_window.setView(sfml_view);
            }
         }

         spaceTime.drawInto(sfml_window);

         sfml_window.display();
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



