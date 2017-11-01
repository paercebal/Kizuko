#include <paercebal/GraphicsTests/main.hpp>

#include <paercebal/Graphics/world/DefaultObject.hpp>
#include <paercebal/Graphics/world/World.hpp>
#include <paercebal/Graphics/maths/utilities.hpp>

#include <cstdlib>
#include <cmath>
#include <limits>

#include <gtest/gtest.h>


namespace paercebal::Graphics::world::tests
{

TEST(AverageScenesTests, TranslationOfSimpleWorldAndObject)
{
   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ {0, 0, 0}, {4, 7, 9} });
      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   auto & child = *(world.getChildren()[0]);

   const Object::Positions positions = { { 1, 2, 3 },{ 5, 9, 12 } };
   EXPECT_EQ(child.getAbsolutePositions(), positions);
}

TEST(AverageScenesTests, TranslationOfSimpleWorldAndTwoObjects)
{
   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      world.getChildren().push_back(o.clone());
   }

   {
      DefaultObject o;
      o.setCenter({ 3, 0, -1 });
      o.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 2);

   {
      auto & child = *(world.getChildren()[0]);

      const Object::Positions positions = { { 1, 2, 3 },{ 5, 9, 12 } };
      EXPECT_EQ(child.getAbsolutePositions(), positions);
   }

   {
      auto & child = *(world.getChildren()[1]);

      const Object::Positions positions = { { 4, 3, 4 },{ -1, -2, -1 } };
      EXPECT_EQ(child.getAbsolutePositions(), positions);
   }
}


TEST(AverageScenesTests, TranslationOfSimpleWorldAndOneObjectAndOneObject)
{
   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });

      {
         DefaultObject o2;
         o2.setCenter({ 3, 0, -1 });
         o2.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
         o.getChildren().push_back(o2.clone());
      }

      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   {
      auto & child = *(world.getChildren()[0]);

      const Object::Positions positions = { { 1, 2, 3 },{ 5, 9, 12 } };
      EXPECT_EQ(child.getAbsolutePositions(), positions);

      ASSERT_EQ(child.getChildren().size(), 1);

      {
         auto & grandchild = *(child.getChildren()[0]);

         const Object::Positions positions = { { 5, 5, 7 },{ 0, 0, 2 } };
         EXPECT_EQ(grandchild.getAbsolutePositions(), positions);
      }
   }
}


TEST(AverageScenesTests, RotationOfSimpleWorldAndObject)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 0, 0, 0 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeRotations({ r });
      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   auto & child = *(world.getChildren()[0]);

   const Object::Positions positions = { { 0, 0, 0 },{ -7, 4, 9 } };
   EXPECT_TRUE(is_mostly_equal(child.getAbsolutePositions(), positions));
}


TEST(AverageScenesTests, RotationOfSimpleWorldAndTwoObjects)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);
   const auto r2 = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_3_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 0, 0, 0 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeRotations({ r });
      world.getChildren().push_back(o.clone());
   }

   {
      DefaultObject o;
      o.setCenter({ 0, 0, 0 });
      o.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
      o.setRelativeRotations({ r2 });
      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 2);

   {
      auto & child = *(world.getChildren()[0]);

      const Object::Positions positions = { { 0, 0, 0 },{ -7, 4, 9 } };
      EXPECT_TRUE(is_mostly_equal(child.getAbsolutePositions(), positions));
   }

   {
      auto & child = *(world.getChildren()[1]);

      const Object::Positions positions = { { 3, -1, 5 },{ -2, 4, 0 } };
      EXPECT_TRUE(is_mostly_equal(child.getAbsolutePositions(), positions));
   }
}


TEST(AverageScenesTests, RotationOfSimpleWorldAndOneObjectAndOneObject)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 0, 0, 0 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeRotations({ r });

      {
         DefaultObject o2;
         o2.setCenter({ 0, 0, 0 });
         o2.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
         o2.setRelativeRotations({ r });
         o.getChildren().push_back(o2.clone());
      }

      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   {
      auto & child = *(world.getChildren()[0]);

      const Object::Positions positions = { { 0, 0, 0 },{ -7, 4, 9 } };
      EXPECT_TRUE(is_mostly_equal(child.getAbsolutePositions(), positions));

      ASSERT_EQ(child.getChildren().size(), 1);

      {
         auto & grandchild = *(child.getChildren()[0]);

         const Object::Positions positions = { { -1, -3, 5 },{ 4, 2, 0 } };
         EXPECT_TRUE(is_mostly_equal(grandchild.getAbsolutePositions(), positions));
      }
   }

}


TEST(AverageScenesTests, RotationAndTranslationOfSimpleWorldAndObject)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeRotations({ r });
      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   auto & child = *(world.getChildren()[0]);

   const Object::Positions positions = { { 1, 2, 3 },{ -6, 6, 12 } };
   EXPECT_TRUE(is_mostly_equal(child.getAbsolutePositions(), positions));
}


TEST(AverageScenesTests, RotationAndTranslationOfSimpleWorldAndTwoObjects)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);
   const auto r2 = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_3_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeRotations({ r });
      world.getChildren().push_back(o.clone());
   }

   {
      DefaultObject o;
      o.setCenter({ 5, 3, -1 });
      o.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
      o.setRelativeRotations({ r2 });
      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 2);

   {
      auto & child = *(world.getChildren()[0]);

      const Object::Positions positions = { { 1, 2, 3 },{ -6, 6, 12 } };
      EXPECT_TRUE(is_mostly_equal(child.getAbsolutePositions(), positions));
   }

   {
      auto & child = *(world.getChildren()[1]);

      const Object::Positions positions = { { 8, 2, 4 },{ 3, 7, -1 } };
      EXPECT_TRUE(is_mostly_equal(child.getAbsolutePositions(), positions));
   }
}


TEST(AverageScenesTests, RotationAndTranslationOfSimpleWorldAndOneObjectAndOneObject)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeRotations({ r });

      {
         DefaultObject o2;
         o2.setCenter({ 5, 3, -1 });
         o2.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
         o2.setRelativeRotations({ r });
         o.getChildren().push_back(o2.clone());
      }

      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   {
      auto & child = *(world.getChildren()[0]);

      const Object::Positions positions = { { 1, 2, 3 },{ -6, 6, 12 } };
      EXPECT_TRUE(is_mostly_equal(child.getAbsolutePositions(), positions))
         << "                   positions: " << anythingPrinter(positions) << "\n"
         << "child.getAbsolutePositions(): " << anythingPrinter(child.getAbsolutePositions()) << "\n";

      ASSERT_EQ(child.getChildren().size(), 1);

      {
         auto & grandchild = *(child.getChildren()[0]);

//       const Object::Positions positions = { { 1, 3, 5 },{ -4, -2, 0 } };
//       const Object::Positions positions = { { -3, 1, 5 },{ 2, -4, 0 } }; // after rotation /r
//       const Object::Positions positions = { { 2, 4, 4 },{ 7, -1, -1 } }; // after translation /grandchild
//       const Object::Positions positions = { { -4, 2, 4 },{ 1, 7, -1 } }; // after rotation /r
         const Object::Positions positions = { { -3, 4, 7 },{ 2, 9, 2 } }; // after translation /child
         EXPECT_TRUE(is_mostly_equal(grandchild.getAbsolutePositions(), positions))
            << "                        positions: " << anythingPrinter(positions) << "\n"
            << "grandchild.getAbsolutePositions(): " << anythingPrinter(grandchild.getAbsolutePositions()) << "\n";
      }
   }

}

}