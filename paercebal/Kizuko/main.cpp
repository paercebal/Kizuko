#include <paercebal/Kizuko/main.hpp>

#include <paercebal/KizukoLib/gui/screen.hpp>
#include <paercebal/KizukoLib/Exception.hpp>
#include <paercebal/KizukoLib/GlobalResources.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <algorithm>
#include <fstream>
#include <ios>


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

bool clearLog()
{
   std::fstream f("__log.txt", std::ios_base::out);
   f << "\n";
   return true;
}

void doLog(const std::stringstream & str)
{
   static bool dummy = clearLog();

   std::fstream f("__log.txt", std::ios_base::app);
   if (f.is_open())
   {
      f << str.str() << "\n";
   }
}

#ifdef DO_LOG_ACTIVE

#define DO_LOG(m_str)                                          \
{                                                              \
   std::stringstream str;                                      \
   str << m_str;                                               \
   doLog(str);                                                 \
}                                                              \

#else // DO_LOG_ACTIVE

#define DO_LOG(m_str)

#endif // DO_LOG_ACTIVE


template <typename Derived>
class ApplicationBase
{
public:

   struct Drag
   {
      Drag(ApplicationBase & applicationBase_)
         : applicationBase(applicationBase_)
      {
      }

      using Move = sf::Event::MouseMoveEvent;

      ApplicationBase & applicationBase;
      bool isDraggingActive = false;
      bool isMouseButtonPressed = false;
      sf::Event::MouseMoveEvent old = Move();
      sf::Event::MouseMoveEvent now = Move();

      bool isDragging() const
      {
         return this->isDraggingActive && this->isMouseButtonPressed;
      }

      void onMouseButtonPress(const sf::Event::MouseButtonEvent & event)
      {
         if (this->isDraggingActive)
         {
            this->isMouseButtonPressed = true;
            this->old = Drag::Move();
            this->now.x = event.x;
            this->now.y = event.y;
         }
      }

      void onMouseButtonRelease(const sf::Event::MouseButtonEvent & event)
      {
         if (this->isDraggingActive)
         {
            this->isMouseButtonPressed = false;
            this->old = Drag::Move();
            this->now = Drag::Move();
         }
      }

      void onMouseMove(const sf::Event::MouseMoveEvent & event)
      {
         if (this->isDraggingActive)
         {
            if (this->isMouseButtonPressed)
            {
               this->old = this->now;
               this->now = event;
               static_cast<Derived &>(this->applicationBase).onMouseDrag(this->now, this->old);
            }
         }
      }
   };

public:
   ApplicationBase(sf::RenderWindow & sfml_window_, sf::View & sfml_view_)
      : sfml_window(sfml_window_)
      , sfml_view(sfml_view_)
      , dragLeft(*this)
      , dragMiddle(*this)
      , dragRight(*this)
   {
   }

   void processEvents()
   {
      sf::Event event;

      while (this->sfml_window.pollEvent(event))
      {
         this->onEvent(event);
      }
   }

   void onWindowClose()
   {
      this->sfml_window.close();
   }

   void onWindowResize(const sf::Event::SizeEvent & event)
   {
   }

   void onKeyPress(const sf::Event::KeyEvent & event)
   {
   }

   void onKeyRelease(const sf::Event::KeyEvent & event)
   {
   }

   void onMouseButtonPress(const sf::Event::MouseButtonEvent & event)
   {
   }

   void onMouseButtonRelease(const sf::Event::MouseButtonEvent & event)
   {
   }

   void onMouseMove(const sf::Event::MouseMoveEvent & event)
   {
   }

   void onMouseDrag(const sf::Event::MouseMoveEvent & eventNow, const sf::Event::MouseMoveEvent & eventOld)
   {
   }

   void onMouseWheelScroll(const sf::Event::MouseWheelScrollEvent & event)
   {
   }

   bool isKeyPressed(sf::Keyboard::Key key) const
   {
      if (key >= 0 && key < sf::Keyboard::Key::KeyCount)
      {
         return this->keyboard[key];
      }

      return false;
   }

   template <sf::Keyboard::Key key>
   bool isKeyPressed() const
   {
      if (key >= 0 && key < sf::Keyboard::Key::KeyCount)
      {
         return this->keyboard[key];
      }

      return false;
   }

   bool isDragging() const
   {
      return this->dragLeft.isDragging() || this->dragMiddle.isDragging() || this->dragRight.isDragging();
   }

private:

   void onEvent(const sf::Event & event)
   {
      Derived * derived = static_cast<Derived *>(this);

      switch (event.type)
      {
         case sf::Event::Closed: derived->onWindowClose(); break;
         case sf::Event::Resized: derived->onWindowResize(event.size); break;
         case sf::Event::KeyPressed: this->onKeyPressUpdateState(event.key); derived->onKeyPress(event.key); break;
         case sf::Event::KeyReleased: this->onKeyReleaseUpdateState(event.key); derived->onKeyRelease(event.key); break;
         case sf::Event::MouseButtonPressed: this->onMouseButtonPressUpdateState(event.mouseButton); derived->onMouseButtonPress(event.mouseButton); break;
         case sf::Event::MouseButtonReleased: this->onMouseButtonReleaseUpdateState(event.mouseButton); derived->onMouseButtonRelease(event.mouseButton); break;
         case sf::Event::MouseMoved: this->onMouseMoveUpdateState(event.mouseMove); derived->onMouseMove(event.mouseMove); break;
         case sf::Event::MouseWheelScrolled: derived->onMouseWheelScroll(event.mouseWheelScroll); break;
      }
   }

   void onKeyPressUpdateState(const sf::Event::KeyEvent & event)
   {
      if (event.code >= 0 && event.code < sf::Keyboard::Key::KeyCount)
      {
         DO_LOG("Event: KeyPress : " << event.code);
         this->keyboard[event.code] = true;
      }
   }

   void onKeyReleaseUpdateState(const sf::Event::KeyEvent & event)
   {
      if (event.code >= 0 && event.code < sf::Keyboard::Key::KeyCount)
      {
         DO_LOG("Event: KeyRelease : " << event.code);
         this->keyboard[event.code] = false;
      }
   }

   void onMouseButtonPressUpdateState(const sf::Event::MouseButtonEvent & event)
   {
      switch (event.button)
      {
         case sf::Mouse::Left: this->dragLeft.onMouseButtonPress(event); break;
         case sf::Mouse::Middle: this->dragMiddle.onMouseButtonPress(event); break;
         case sf::Mouse::Right: this->dragRight.onMouseButtonPress(event); break;
      }

      if (event.button == sf::Mouse::Left)
      {
         if (!this->dragLeft.isDragging())
         {
            if ((this->leftButtonClicked.size() % 2) == 0)
            {
               this->leftButtonClicked.push_back({ event.x, event.y });
            }
         }
         else
         {
            this->leftButtonClicked.clear();
         }
      }
   }

   void onMouseButtonReleaseUpdateState(const sf::Event::MouseButtonEvent & event)
   {
      switch (event.button)
      {
         case sf::Mouse::Left: this->dragLeft.onMouseButtonRelease(event); break;
         case sf::Mouse::Middle: this->dragMiddle.onMouseButtonRelease(event); break;
         case sf::Mouse::Right: this->dragRight.onMouseButtonRelease(event); break;
      }

      if (event.button == sf::Mouse::Left)
      {
         if (!this->dragLeft.isDragging())
         {
            if ((this->leftButtonClicked.size() % 2) == 1)
            {
               this->leftButtonClicked.push_back({ event.x, event.y });
            }
         }
         else
         {
            this->leftButtonClicked.clear();
         }
      }
   }

   void onMouseMoveUpdateState(const sf::Event::MouseMoveEvent & event)
   {
      this->dragLeft.onMouseMove(event);
      this->dragMiddle.onMouseMove(event);
      this->dragRight.onMouseMove(event);
   }

protected:
   sf::RenderWindow & sfml_window;
   sf::View & sfml_view;

   std::array<bool, sf::Keyboard::Key::KeyCount> keyboard = {};
   Drag dragLeft;
   Drag dragMiddle;
   Drag dragRight;
   std::vector<sf::Vector2i> leftButtonClicked;
};




class Application : public ApplicationBase<Application>
{
   using super = ApplicationBase<Application>;
public:
   Application(paercebal::KizukoLib::gui::Screen & screen_, sf::RenderWindow & sfml_window_, sf::View & sfml_view_)
      : super(sfml_window_, sfml_view_)
      , screen(screen_)
   {
      this->dragRight.isDraggingActive = true;
   }

   void onWindowResize(const sf::Event::SizeEvent & event)
   {
      this->sfml_view.setSize({ static_cast<float>(event.width), static_cast<float>(event.height) });
      this->screen.setView(this->sfml_view);
      this->sfml_window.setView(this->sfml_view);
   }

   void onMouseWheelScroll(const sf::Event::MouseWheelScrollEvent & event)
   {
      if (event.delta > 0)
      {
         screen.onMouseWheelScrollPositive();
      }
      else  if (event.delta < 0)
      {
         screen.onMouseWheelScrollNegative();
      }
   }

   void onMouseDrag(const sf::Event::MouseMoveEvent & eventNow, const sf::Event::MouseMoveEvent & eventOld)
   {
      screen.onMouseDragByPixels(eventNow.x - eventOld.x, eventNow.y - eventOld.y);
   }

   void processState()
   {
      if (this->isKeyPressed<sf::Keyboard::Key::Escape>())
      {
         this->sfml_window.close();
         throw AskedToQuitException();
      }

      if (this->isKeyPressed<sf::Keyboard::Key::Left>())
      {
         this->screen.onLeftKeyPressed();
      }
      if (this->isKeyPressed<sf::Keyboard::Key::Right>())
      {
         this->screen.onRightKeyPressed();
      }
      if (this->isKeyPressed<sf::Keyboard::Key::Up>())
      {
         this->screen.onUpKeyPressed();
      }
      if (this->isKeyPressed<sf::Keyboard::Key::Down>())
      {
         this->screen.onDownKeyPressed();
      }
      if (this->isKeyPressed<sf::Keyboard::Key::PageUp>())
      {
         this->screen.onPageUpKeyPressed();
      }
      if (this->isKeyPressed<sf::Keyboard::Key::PageDown>())
      {
         this->screen.onPageDownKeyPressed();
      }

      this->screen.warnScreenAboutMouseHovering(sf::Mouse::getPosition(this->sfml_window).x, sf::Mouse::getPosition(this->sfml_window).y);

      {
         size_t steps = this->leftButtonClicked.size() / 2;

         for (size_t i = 0; i < steps; ++i)
         {
            screen.warnScreenAboutMouseClicking(this->leftButtonClicked[i * 2], this->leftButtonClicked[i * 2 + 1]);
         }

         if (this->leftButtonClicked.size() % 2 != 0)
         {
            this->leftButtonClicked[0] = this->leftButtonClicked[this->leftButtonClicked.size() - 1];
            this->leftButtonClicked.resize(1);
         }
         else
         {
            this->leftButtonClicked.clear();
         }
      }

      this->screen.calculateAbsolutePositionThenShapes2DRecursiveIfNeeded();
   }

   void display()
   {
      this->sfml_window.clear(sf::Color::Black);

      this->screen.drawInto(sfml_window);

      //sfml_window.setView(sfml_view);
      this->sfml_window.display();
   }

private:
   paercebal::KizukoLib::gui::Screen & screen;
};


int main(int argc, char * argv[])
{
   using namespace paercebal::KizukoLib;
   
   try
   {
      GlobalResources globalResources(argc, argv);
      
      gui::Screen screen{ globalResources };

      screen.calculateAbsolutePositionThenShapes2DRecursiveIfNeeded();

      sf::View sfml_view(sf::Vector2f(0, 0), sf::Vector2f(static_cast<float>(windowWidth), static_cast<float>(windowHeight)));
      screen.setView(sfml_view);

      sf::ContextSettings settings;
      settings.antialiasingLevel = 8;
      sf::RenderWindow sfml_window(sf::VideoMode(windowWidth, windowHeight), "Kizuko", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close, settings);
      sfml_window.setFramerateLimit(60);
      sfml_window.setView(sfml_view);

      Application application(screen, sfml_window, sfml_view);

      try
      {
         screen.getGlobalResources().getMusicCluster().music.play();


         while (sfml_window.isOpen())
         {
            application.processEvents();
            application.processState();
            application.display();
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



