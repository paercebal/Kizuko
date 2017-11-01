#include <paercebal/Graphics/world/DefaultObject.hpp>

#include <gtest/gtest.h>

namespace paercebal::Graphics::world::tests
{


TEST(ObjectTests, Simple)
{
   {
      DefaultObject o;

      const sf::Vector3f vZero{ 0, 0, 0 };
      const sf::Vector3f v{ 1, 2, 3 };

      EXPECT_EQ(vZero, o.getCenter());
      o.setCenter({ 1, 2, 3 });
      EXPECT_EQ(v, o.getCenter());
   }

   {
      DefaultObject o;

      Object::Positions positionsEmpty;
      Object::Positions positionsAlpha = { { 1, 2, 3 },{ 10, 20, 30 } };
      Object::Positions positionsBeta = { { 9, 8, 7 },{ 5, 10, 20 }, { 14, 16, 18} };

      EXPECT_EQ(positionsEmpty, o.getRelativePositions());
      EXPECT_EQ(positionsEmpty, o.getAbsolutePositions());
      o.setRelativePositions({ { 1, 2, 3 },{ 10, 20, 30 } });
      EXPECT_EQ(positionsAlpha, o.getRelativePositions());
      EXPECT_EQ(positionsEmpty, o.getAbsolutePositions());
      o.getAbsolutePositions() = { { 9, 8, 7 },{ 5, 10, 20 },{ 14, 16, 18 } };
      EXPECT_EQ(positionsAlpha, o.getRelativePositions());
      EXPECT_EQ(positionsBeta, o.getAbsolutePositions());
   }

   {
      DefaultObject o;

      Object::Rotations rotationsEmpty;
      Object::Rotations rotationsAlpha = { { 1, 2, 3, 10, 20, 30, 100, 200, 300 },{ 40, 50, 60, 8, 5, 2, 521, 814, 12 } };

      EXPECT_EQ(rotationsEmpty, o.getRelativeRotations());
      o.setRelativeRotations({ { 1, 2, 3, 10, 20, 30, 100, 200, 300 },{ 40, 50, 60, 8, 5, 2, 521, 814, 12 } });
      EXPECT_EQ(rotationsAlpha, o.getRelativeRotations());
   }

   {
      DefaultObject o;

      Object::Scaling scalingNone = maths::utilities::createScaleMatrix<float>(1);
      Object::Scaling scalingAlpha = maths::utilities::createScaleMatrix<float>(1, 2, 3);

      EXPECT_EQ(scalingNone, o.getRelativeScaling());
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(1, 2, 3));
      EXPECT_EQ(scalingAlpha, o.getRelativeScaling());
   }

   
}

TEST(ObjectTests, CloningSimple)
{
   {
      DefaultObject o;

      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 1, 2, 3 },{ 10, 20, 30 } });
      o.getAbsolutePositions() = { { 9, 8, 7 },{ 5, 10, 20 },{ 14, 16, 18 } };
      o.setRelativeRotations({ { 1, 2, 3, 10, 20, 30, 100, 200, 300 },{ 40, 50, 60, 8, 5, 2, 521, 814, 12 } });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(1, 2, 3));

      auto p = o.clone();

      EXPECT_EQ(o.getCenter(), p->getCenter());
      EXPECT_EQ(o.getRelativePositions(), p->getRelativePositions());
      EXPECT_EQ(o.getAbsolutePositions(), p->getAbsolutePositions());
      EXPECT_EQ(o.getRelativeRotations(), p->getRelativeRotations());
      EXPECT_EQ(o.getRelativeScaling(), p->getRelativeScaling())
         << " o.getRelativeScaling(): " << o.getRelativeScaling() << "\n"
         << "p->getRelativeScaling(): " << p->getRelativeScaling() << "\n";

      o.setCenter({ 10, 20, 30 });
      o.setRelativePositions({ { 10, 20, 30 },{ 100, 200, 300 } });
      o.getAbsolutePositions() = { { 90, 80, 70 },{ 50, 100, 200 },{ 140, 160, 180 } };
      o.setRelativeRotations({ { 10, 20, 30, 100, 200, 300, 1000, 2000, 3000 },{ 400, 500, 600, 80, 50, 20, 5210, 8140, 120 } });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(10, 20, 30));

      EXPECT_NE(o.getCenter(), p->getCenter());
      EXPECT_NE(o.getRelativePositions(), p->getRelativePositions());
      EXPECT_NE(o.getAbsolutePositions(), p->getAbsolutePositions());
      EXPECT_NE(o.getRelativeRotations(), p->getRelativeRotations());
      EXPECT_NE(o.getRelativeScaling(), p->getRelativeScaling())
         << " o.getRelativeScaling(): " << o.getRelativeScaling() << "\n"
         << "p->getRelativeScaling(): " << p->getRelativeScaling() << "\n";
   }
}


TEST(ObjectTests, CloningWithChildren)
{
   auto createChildren = [](float a, float b, float c, float d, float e)
   {
      std::unique_ptr<Object> p = std::make_unique<DefaultObject>();
      p->setCenter({ a, a * 2, a * 3 });
      p->setRelativePositions({ { b * 1, b * 2, b * 3 },{ b * 10, b * 20, b * 30 } });
      p->getAbsolutePositions() = { { c * 2, c * 3, c * 5 },{ c * 7, c * 9, c * 3 },{ c * 13, c * 7, c * 11 } };
      p->setRelativeRotations({ { d * 10, d * 20, d * 30, d * 100, d * 200, d * 300, d * 1000, d * 2000, d * 3000 },{ d * 400, d * 500, d * 600, d * 80, d * 50, d * 20, d * 5210, d * 8140, d * 120 } });
      p->setRelativeScaling(maths::utilities::createScaleMatrix<float>(e * 1, e * 2, e * 3));
      return p;
   };

   {
      DefaultObject o;
      o.getChildren().push_back(createChildren(1, 2, 3, 4, 5));
      o.getChildren().push_back(createChildren(13, 8, 4, 7, 1));

      auto p = o.clone();

      ASSERT_EQ(o.getChildren().size(), 2);
      ASSERT_EQ(o.getChildren().size(), p->getChildren().size());

      {
         const auto & cA = *(o.getChildren()[0]);
         const auto & cB = *(p->getChildren()[0]);
         const auto & cAA = *(o.getChildren()[1]);
         const auto & cBB = *(p->getChildren()[1]);

         EXPECT_EQ(cA.getCenter(), cB.getCenter());
         EXPECT_EQ(cA.getRelativePositions(), cB.getRelativePositions());
         EXPECT_EQ(cA.getAbsolutePositions(), cB.getAbsolutePositions());
         EXPECT_EQ(cA.getRelativeRotations(), cB.getRelativeRotations());
         EXPECT_EQ(cA.getRelativeRotations(), cB.getRelativeRotations());
         EXPECT_EQ(cA.getRelativeScaling(), cB.getRelativeScaling())
            << "cA.getRelativeScaling(): " << cA.getRelativeScaling() << "\n"
            << "cB.getRelativeScaling(): " << cB.getRelativeScaling() << "\n";

         EXPECT_EQ(cAA.getCenter(), cBB.getCenter());
         EXPECT_EQ(cAA.getRelativePositions(), cBB.getRelativePositions());
         EXPECT_EQ(cAA.getAbsolutePositions(), cBB.getAbsolutePositions());
         EXPECT_EQ(cAA.getRelativeRotations(), cBB.getRelativeRotations());
         EXPECT_EQ(cAA.getRelativeRotations(), cBB.getRelativeRotations());
         EXPECT_EQ(cAA.getRelativeScaling(), cBB.getRelativeScaling())
            << "cAA.getRelativeScaling(): " << cAA.getRelativeScaling() << "\n"
            << "cBB.getRelativeScaling(): " << cBB.getRelativeScaling() << "\n";

         EXPECT_NE(cAA.getCenter(), cB.getCenter());
         EXPECT_NE(cAA.getRelativePositions(), cB.getRelativePositions());
         EXPECT_NE(cAA.getAbsolutePositions(), cB.getAbsolutePositions());
         EXPECT_NE(cAA.getRelativeRotations(), cB.getRelativeRotations());
         EXPECT_NE(cAA.getRelativeRotations(), cB.getRelativeRotations());
         EXPECT_NE(cAA.getRelativeScaling(), cB.getRelativeScaling())
            << "cAA.getRelativeScaling(): " << cAA.getRelativeScaling() << "\n"
            << " cB.getRelativeScaling(): " << cB.getRelativeScaling() << "\n";
      }
   }
}


}