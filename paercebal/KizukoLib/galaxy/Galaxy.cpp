#include <paercebal/KizukoLib/galaxy/Galaxy.hpp>

#include <paercebal/KizukoLib/galaxy/GalaxyCircle.hpp>
#include <paercebal/KizukoLib/galaxy/GalaxyLine.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <cmath>

namespace paercebal::KizukoLib::galaxy
{

namespace {

std::vector<std::unique_ptr<GalaxyLine>> createClusterCartesianGrid(const GlobalResources & globalResources, float radius, float gridIncrement_, int gridMajorIncrement_)
{
   std::vector<std::unique_ptr<GalaxyLine>> v;

   // Y lines
   {
      int Increment = 0;

      for (float x = 0, xEnd = radius; x <= xEnd; x += gridIncrement_, ++Increment)
      {
         if (Increment == 0)
         {
            v.push_back(std::make_unique<GalaxyLine>(globalResources, GalaxyLineStyle::AxisY, sf::Vector3f{ x, radius, 0 }, sf::Vector3f{ x, -radius, 0 }));
         }
         else
         {
            const float halfLength = std::pow(std::pow(radius, 2.f) - std::pow(x, 2.f), 0.5f);

            const GalaxyLineStyle style = GalaxyLineStyle::Minor;
            v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ x, halfLength, 0 }, sf::Vector3f{ x, -halfLength, 0 }));
            v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ -x, halfLength, 0 }, sf::Vector3f{ -x, -halfLength, 0 }));
         }
      }
   }

   // X lines
   {
      int Increment = 0;

      for (float y = 0, yEnd = radius; y <= yEnd; y += gridIncrement_, ++Increment)
      {
         if (Increment == 0)
         {
            v.push_back(std::make_unique<GalaxyLine>(globalResources, GalaxyLineStyle::AxisX, sf::Vector3f{ radius, y, 0 }, sf::Vector3f{ -radius, y, 0 }));
         }
         else
         {
            const float halfLength = std::pow(std::pow(radius, 2.f) - std::pow(y, 2.f), 0.5f);

            const GalaxyLineStyle style = GalaxyLineStyle::Minor;
            v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ halfLength, y, 0 }, sf::Vector3f{ -halfLength, y, 0 }));
            v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ halfLength, -y, 0 }, sf::Vector3f{ -halfLength, -y, 0 }));
         }
      }
   }

   return v;
}

std::vector<std::unique_ptr<GalaxyCircle>> createClusterPolarGrid(const GlobalResources & globalResources, float radius, float gridIncrement_, int gridMajorIncrement_)
{
   std::vector<std::unique_ptr<GalaxyCircle>> v;

   int Increment = 0;

   for (float x = 0, xEnd = radius; x <= xEnd; x += gridIncrement_, ++Increment)
   {
      if (Increment == 0)
      {
         v.push_back(std::make_unique<GalaxyCircle>(globalResources, GalaxyCircleStyle::AxisY, x));
      }
      else
      {
         const GalaxyCircleStyle style = ((Increment % gridMajorIncrement_) == 0) ? GalaxyCircleStyle::Major : GalaxyCircleStyle::Minor;
         v.push_back(std::make_unique<GalaxyCircle>(globalResources, style, x));
      }
   }

   return v;
}

} // anonymous namespace


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

#define DO_LOG_ACTIVE

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




Galaxy::Galaxy(const GlobalResources & globalResources, GalaxyCommands galaxyCommands_, gui::ObserverWidget3D & observerWidget3D_)
   : Galaxy(globalResources, galaxyCommands_, observerWidget3D_, globalResources.getData().galaxy.gridIncrement, static_cast<int>(globalResources.getData().galaxy.gridMajorIncrement), 1.f, globalResources.getData().galaxy.radius)
{
}

Galaxy::Galaxy(const GlobalResources & globalResources, GalaxyCommands galaxyCommands_, gui::ObserverWidget3D & observerWidget3D_, float gridIncrement_, int gridMajorIncrement_, float scaling_, float radius_)
   : super(globalResources)
   , galaxyCommands(galaxyCommands_)
   , radius(radius_)
   , gridIncrement(gridIncrement_)
   , gridMajorIncrement(gridMajorIncrement_)
   , scaling(scaling_)
{
   this->registerIntoObserver(observerWidget3D_);

   // we set an isometric presentation
   // this->setCenter()

   //this->setRelativeRotations({ utilities::createRotationToIsometricMatrix<float>() });
   this->setRelativeScaling(Graphics::maths::utilities::createScaleMatrix<float>(this->scaling));

   // We create the cluster lines.
   {
      auto grid = createClusterCartesianGrid(this->getGlobalResources(), this->radius, this->gridIncrement, this->gridMajorIncrement);
      this->galaxyLines.reserve(grid.size());

      for (auto & p : grid)
      {
         GalaxyLine * pp = p.get();
         this->getChildren().push_back(std::move(p));
         this->galaxyLines.push_back(pp);
      }
   }

   // Polar
   {
      // We create the cluster lines.
      auto grid = createClusterPolarGrid(this->getGlobalResources(), this->radius, this->gridIncrement, this->gridMajorIncrement);
      this->galaxyCircles.reserve(grid.size());

      for (auto & p : grid)
      {
         GalaxyCircle * pp = p.get();
         this->getChildren().push_back(std::move(p));
         this->galaxyCircles.push_back(pp);
      }
   }

   for (const auto & cluster : this->getGlobalResources().getData().galaxy.clusterDataList)
   {
      //DO_LOG("               , { \"name\" : \"" << cluster.name << "\"             , \"position\" : \"" << (std::round(cluster.position.x * 100.f * .83f )/100.f)  << ", " << (std::round(cluster.position.y * 100.f * .83f)/100.f) << "\" }");
      this->addCluster({ this->getGlobalResources(), cluster.name, {cluster.position.x, cluster.position.y, 0} });
   }

   const float radius = this->getGlobalResources().getData().galaxy.imageRadius;
   auto image = std::make_unique<objects::FlatImage>(this->getGlobalResources(), this->getGlobalResources().getData().galaxy.image, sf::Vector3f{ -radius, -radius, 0 }, sf::Vector3f{ radius, radius, 0 });
   this->milkyWayImage = image.get();
   this->getChildren().push_back(std::move(image));
}

Galaxy::~Galaxy()
{
   this->unregisterFromObserver();
}

void Galaxy::registerIntoObserver(gui::ObserverWidget3D & observerWidget3D_)
{
   this->unregisterFromObserver();
   observerWidget3D_.registerWidget3D(*this);
   this->observerWidget3D = &observerWidget3D_;
}

void Galaxy::unregisterFromObserver()
{
   if (this->observerWidget3D)
   {
      this->observerWidget3D->unregisterWidget3D(*this);
      this->observerWidget3D = nullptr;
   }
}

void Galaxy::onSelectCluster(const std::string & clusterName)
{
   if (this->galaxyCommands.onSelectCluster)
   {
      this->galaxyCommands.onSelectCluster(clusterName);
   }
}

void Galaxy::createShapes2D()
{
   // Nothing to do: The cluster is the world
   // IF we decide to draw a background image, this will be done here, I guess.
}

void Galaxy::drawInto(sf::RenderTarget & renderTarget) const
{
   // We won't draw through the "World" composite.
   // Instead, we'll draw using pointers to explicit objects
   // This makes easier to decide the order of drawing, and thus, who hides who

   // First, the galaxy
   this->milkyWayImage->drawInto(renderTarget);

   // Then, the galaxy lines
   for (auto & p : this->galaxyLines)
   {
      p->drawInto(renderTarget);
   }

   // Then, the galaxy Circles
   for (auto & p : this->galaxyCircles)
   {
      p->drawInto(renderTarget);
   }

   // Last, the clusters
   for (auto & p : this->clusters)
   {
      p->drawInto(renderTarget);
   }
}

std::unique_ptr<Galaxy> Galaxy::clone() const
{
   return std::unique_ptr<Galaxy>(this->cloneImpl());
}

Galaxy * Galaxy::cloneImpl() const
{
   return new Galaxy(*this);
}

bool Galaxy::isBackgroundImageVisible() const
{
   if (this->milkyWayImage)
   {
      return this->milkyWayImage->isVisible();
   }

   return false;
}

Galaxy & Galaxy::setBackgroundImageVisible(bool visible)
{
   if (this->milkyWayImage)
   {
      this->milkyWayImage->setVisible(visible);
   }

   return *this;
}



Galaxy & Galaxy::addCluster(const GalaxyCluster & cluster)
{
   //const auto starCenter = star.getCenter3D();
   //const auto starColor = star.getColor();

   //this->heightLines.push_back(shapes::HeightLine{ this->getGlobalResources(), starColor, starCenter });

   auto sp = cluster.clone();
   auto * p = sp.get();
   const auto & name = p->getName();

   this->getChildren().push_back(std::move(sp));
   this->clusters.push_back(p);
   p->registerIntoObserver(*(this->observerWidget3D));
   p->setCommand([this, name]()
   {
      this->onSelectCluster(name);
   });

   return *this;
}



} // namespace paercebal::KizukoLib::galaxy
