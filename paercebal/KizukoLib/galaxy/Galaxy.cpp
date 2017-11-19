#include <paercebal/KizukoLib/galaxy/Galaxy.hpp>

#include <paercebal/KizukoLib/galaxy/GalaxyLine.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <cmath>

namespace paercebal::KizukoLib::galaxy
{

namespace {

std::vector<std::unique_ptr<GalaxyLine>> createClusterGrid(const GlobalResources & globalResources, sf::Vector3f size3D, float gridIncrement_, int gridMajorIncrement_)
{
   std::vector<std::unique_ptr<GalaxyLine>> v;

   if (size3D.x == size3D.y)
   {
      // Y lines
      {
         int Increment = 0;

         for (float x = 0, xEnd = size3D.x; x <= xEnd; x += gridIncrement_, ++Increment)
         {
            if (Increment == 0)
            {
               v.push_back(std::make_unique<GalaxyLine>(globalResources, GalaxyLineStyle::AxisY, sf::Vector3f{ x, size3D.y, 0 }, sf::Vector3f{ x, -size3D.y, 0 }));
            }
            else
            {
               const float halfLength = std::pow(std::pow(size3D.x, 2.f) - std::pow(x, 2.f), 0.5f);

               const GalaxyLineStyle style = ((Increment % gridMajorIncrement_) == 0) ? GalaxyLineStyle::Major : GalaxyLineStyle::Minor;
               v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ x, halfLength, 0 }, sf::Vector3f{ x, -halfLength, 0 }));
               v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ -x, halfLength, 0 }, sf::Vector3f{ -x, -halfLength, 0 }));
            }
         }
      }

      // X lines
      {
         int Increment = 0;

         for (float y = 0, yEnd = size3D.y; y <= yEnd; y += gridIncrement_, ++Increment)
         {
            if (Increment == 0)
            {
               v.push_back(std::make_unique<GalaxyLine>(globalResources, GalaxyLineStyle::AxisX, sf::Vector3f{ size3D.x, y, 0 }, sf::Vector3f{ -size3D.x, y, 0 }));
            }
            else
            {
               const float halfLength = std::pow(std::pow(size3D.y, 2.f) - std::pow(y, 2.f), 0.5f);

               const GalaxyLineStyle style = ((Increment % gridMajorIncrement_) == 0) ? GalaxyLineStyle::Major : GalaxyLineStyle::Minor;
               v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ halfLength, y, 0 }, sf::Vector3f{ -halfLength, y, 0 }));
               v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ halfLength, -y, 0 }, sf::Vector3f{ -halfLength, -y, 0 }));
            }
         }
      }
   }
   else
   {
      // Y lines
      {
         int Increment = 0;

         for (float x = 0, xEnd = size3D.x; x <= xEnd; x += gridIncrement_, ++Increment)
         {
            if (Increment == 0)
            {
               v.push_back(std::make_unique<GalaxyLine>(globalResources, GalaxyLineStyle::AxisY, sf::Vector3f{ x, size3D.y, 0 }, sf::Vector3f{ x, -size3D.y, 0 }));
            }
            else
            {
               const GalaxyLineStyle style = ((Increment % gridMajorIncrement_) == 0) ? GalaxyLineStyle::Major : GalaxyLineStyle::Minor;
               v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ x, size3D.y, 0 }, sf::Vector3f{ x, -size3D.y, 0 }));
               v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ -x, size3D.y, 0 }, sf::Vector3f{ -x, -size3D.y, 0 }));
            }
         }
      }

      // X lines
      {
         int Increment = 0;

         for (float y = 0, yEnd = size3D.y; y <= yEnd; y += gridIncrement_, ++Increment)
         {
            if (Increment == 0)
            {
               v.push_back(std::make_unique<GalaxyLine>(globalResources, GalaxyLineStyle::AxisX, sf::Vector3f{ size3D.x, y, 0 }, sf::Vector3f{ -size3D.x, y, 0 }));
            }
            else
            {
               const GalaxyLineStyle style = ((Increment % gridMajorIncrement_) == 0) ? GalaxyLineStyle::Major : GalaxyLineStyle::Minor;
               v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ size3D.x, y, 0 }, sf::Vector3f{ -size3D.x, y, 0 }));
               v.push_back(std::make_unique<GalaxyLine>(globalResources, style, sf::Vector3f{ size3D.x, -y, 0 }, sf::Vector3f{ -size3D.x, -y, 0 }));
            }
         }
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




Galaxy::Galaxy(const GlobalResources & globalResources)
   : Galaxy(globalResources, globalResources.getData().clusters.at(0).increment, static_cast<int>(globalResources.getData().clusters.at(0).majorIncrement), 1.f, globalResources.getData().clusters.at(0).size)
{
}

Galaxy::Galaxy(const GlobalResources & globalResources, float gridIncrement_, int gridMajorIncrement_, float scaling_, sf::Vector3f size3D_)
   : super(globalResources)
   , size3D(size3D_)
   , gridIncrement(gridIncrement_)
   , gridMajorIncrement(gridMajorIncrement_)
   , scaling(scaling_)
{
   // we set an isometric presentation
   // this->setCenter()

   //this->setRelativeRotations({ utilities::createRotationToIsometricMatrix<float>() });
   this->setRelativeScaling(Graphics::maths::utilities::createScaleMatrix<float>(this->scaling));

   // We create the cluster lines.
   auto grid = createClusterGrid(this->getGlobalResources(), this->size3D, this->gridIncrement, this->gridMajorIncrement);
   this->galaxyLines.reserve(grid.size());
   
   for (auto & p : grid)
   {
      GalaxyLine * pp = p.get();
      this->getChildren().push_back(std::move(p));
      this->galaxyLines.push_back(pp);
   }

   for (const auto & cluster : this->getGlobalResources().getData().galaxy.clusterDataList)
   {
      //DO_LOG("               , { \"name\" : \"" << cluster.name << "\"             , \"position\" : \"" << (std::round(cluster.position.x * 100.f - 5000.f )/100.f)  << ", " << (std::round(cluster.position.y * 100.f - 5000.f)/100.f) << "\" }");
      this->addCluster({ this->getGlobalResources(), cluster.name, {cluster.position.x * 10, cluster.position.y * 10, 0} });
   }

   const float sizeGalaxy = 80.f;
   auto image = std::make_unique<objects::FlatImage>(this->getGlobalResources(), sf::Vector3f{ -sizeGalaxy, -sizeGalaxy, 0 }, sf::Vector3f{ sizeGalaxy, sizeGalaxy, 0 });
   this->milkyWayImage = image.get();
   this->getChildren().push_back(std::move(image));
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

Galaxy & Galaxy::addCluster(const GalaxyCluster & cluster)
{
   //const auto starCenter = star.getCenter3D();
   //const auto starColor = star.getColor();

   //this->heightLines.push_back(shapes::HeightLine{ this->getGlobalResources(), starColor, starCenter });

   auto sp = cluster.clone();
   auto * p = sp.get();

   this->getChildren().push_back(std::move(sp));
   this->clusters.push_back(p);

   return *this;
}



} // namespace paercebal::KizukoLib::galaxy
