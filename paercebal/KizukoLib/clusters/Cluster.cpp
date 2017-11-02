#include <paercebal/KizukoLib/clusters/Cluster.hpp>

#include <paercebal/KizukoLib/clusters/ClusterLine.hpp>
#include <paercebal/KizukoLib/clusters/DistanceShape.hpp>
#include <paercebal/KizukoLib/utilities.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace paercebal::KizukoLib::clusters
{

namespace {

std::vector<std::unique_ptr<ClusterLine>> createClusterGrid(const GlobalResources & globalResources, sf::Vector3f size3D, float gridIncrement_, int gridMajorIncrement_)
{
   std::vector<std::unique_ptr<ClusterLine>> v;

   // Y lines
   {
      int Increment = 0;

      for (float x = 0, xEnd = size3D.x; x <= xEnd; x += gridIncrement_, ++Increment)
      {
         if (Increment == 0)
         {
            v.push_back(std::make_unique<ClusterLine>(globalResources, ClusterLineStyle::AxisY, sf::Vector3f{ x, size3D.y, 0 }, sf::Vector3f{ x, -size3D.y, 0 }));
         }
         else
         {
            const ClusterLineStyle style = ((Increment % gridMajorIncrement_) == 0) ? ClusterLineStyle::Major : ClusterLineStyle::Minor;
            v.push_back(std::make_unique<ClusterLine>(globalResources, style, sf::Vector3f{ x, size3D.y, 0 }, sf::Vector3f{ x, -size3D.y, 0 }));
            v.push_back(std::make_unique<ClusterLine>(globalResources, style, sf::Vector3f{ -x, size3D.y, 0 }, sf::Vector3f{ -x, -size3D.y, 0 }));
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
            v.push_back(std::make_unique<ClusterLine>(globalResources, ClusterLineStyle::AxisX, sf::Vector3f{ size3D.x, y, 0 }, sf::Vector3f{ -size3D.x, y, 0 }));
         }
         else
         {
            const ClusterLineStyle style = ((Increment % gridMajorIncrement_) == 0) ? ClusterLineStyle::Major : ClusterLineStyle::Minor;
            v.push_back(std::make_unique<ClusterLine>(globalResources, style, sf::Vector3f{ size3D.x, y, 0 }, sf::Vector3f{ -size3D.x, y, 0 }));
            v.push_back(std::make_unique<ClusterLine>(globalResources, style, sf::Vector3f{ size3D.x, -y, 0 }, sf::Vector3f{ -size3D.x, -y, 0 }));
         }
      }
   }

   return v;
}

}

Cluster::Cluster(const GlobalResources & globalResources)
   : Cluster(globalResources, globalResources.getData().increment, static_cast<int>(globalResources.getData().majorIncrement), 10.f, globalResources.getData().size)
{
}

Cluster::Cluster(const GlobalResources & globalResources, float gridIncrement_, int gridMajorIncrement_, float scaling_, sf::Vector3f size3D_)
   : super(globalResources)
   , size3D(size3D_)
   , gridIncrement(gridIncrement_)
   , gridMajorIncrement(gridMajorIncrement_)
   , scaling(scaling_)
{
   // we set an isometric presentation
   // this->setCenter()

   this->setRelativeRotations({ utilities::createRotationToIsometricMatrix<float>() });
   this->setRelativeScaling(Graphics::maths::utilities::createScaleMatrix<float>(this->scaling));

   // We create the cluster lines.
   auto grid = createClusterGrid(this->getGlobalResources(), this->size3D, this->gridIncrement, this->gridMajorIncrement);
   this->clusterLines.reserve(grid.size());
   
   for (auto & p : grid)
   {
      ClusterLine * pp = p.get();
      this->getChildren().push_back(std::move(p));
      this->clusterLines.push_back(pp);
   }

   for (const auto & star : this->getGlobalResources().getData().stars)
   {
      this->addStar({ this->getGlobalResources(), star.name, sf::Color{ star.r, star.g, star.b, star.a },{ star.x, star.y, star.z }, star.size });
   }

   for (const auto & distance : this->getGlobalResources().getData().distances)
   {
      this->addDistance({ this->getGlobalResources(), distance.begin, distance.end });
   }
}

void Cluster::createShapes2D()
{
   // Nothing to do: The cluster is the world
   // IF we decide to draw a background image, this will be done here, I guess.
}

void Cluster::drawInto(sf::RenderTarget & renderTarget) const
{
   // We won't draw through the "World" composite.
   // Instead, we'll draw using pointers to explicit objects
   // This makes easier to decide the order of drawing, and thus, who hides who

   // First, the cluster lines
   for (auto & p : this->clusterLines)
   {
      p->drawInto(renderTarget);
   }

   for (auto & p : this->distanceShapes)
   {
      p->drawInto(renderTarget);
   }

   for (auto & p : this->altitudeLine)
   {
      p->drawInto(renderTarget);
   }

   // Last, the stars
   for (auto & p : this->stars)
   {
      p->drawInto(renderTarget);
   }
}

std::unique_ptr<Cluster> Cluster::clone() const
{
   return std::unique_ptr<Cluster>(this->cloneImpl());
}

Cluster * Cluster::cloneImpl() const
{
   return new Cluster(*this);
}

Cluster & Cluster::addStar(const Star & star)
{
   //const auto starCenter = star.getCenter3D();
   //const auto starColor = star.getColor();

   //this->heightLines.push_back(shapes::HeightLine{ this->getGlobalResources(), starColor, starCenter });

   auto sp = star.clone();
   auto * p = sp.get();

   this->getChildren().push_back(std::move(sp));
   this->stars.push_back(p);

   const auto starCenter = p->getCenter();
   auto spAltitudeLine = std::make_unique<AltitudeLine>(this->getGlobalResources(), starCenter);
   this->altitudeLine.push_back(spAltitudeLine.get());
   this->getChildren().push_back(std::move(spAltitudeLine));

   return *this;
}

Cluster & Cluster::addDistance(const DistanceShape & distance)
{
   auto findStarCenter = [](const std::vector<Star *> & stars, const std::string & name)
   {
      sf::Vector3f center;

      for (const auto & star : stars)
      {
         if (star->getName() == name)
         {
            center = star->getCenter();
            break;
         }
      }

      return center;
   };


   auto sp = distance.clone();
   auto * p = sp.get();

   p->setBeginAndEnd(findStarCenter(this->stars, p->getBeginName()), findStarCenter(this->stars, p->getEndName()));

   this->getChildren().push_back(std::move(sp));
   this->distanceShapes.push_back(p);

   return *this;
}


} // namespace paercebal::KizukoLib::clusters