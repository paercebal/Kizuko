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

////////////////////////////////////////////////////////////////////////////////
//
// Translation
//
////////////////////////////////////////////////////////////////////////////////

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

TEST(AverageScenesTests, TranslationOfSimpleWorldAndOneEmptyObjectAndOneObject)
{
   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      // no relative positions.

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

      const Object::Positions positions = { { 1, 2, 3 } };
      EXPECT_EQ(child.getAbsolutePositions(), positions);

      ASSERT_EQ(child.getChildren().size(), 1);

      {
         auto & grandchild = *(child.getChildren()[0]);

         const Object::Positions positions = { { 5, 5, 7 },{ 0, 0, 2 } };
         EXPECT_EQ(grandchild.getAbsolutePositions(), positions);
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
//
// Rotation
//
////////////////////////////////////////////////////////////////////////////////

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


TEST(AverageScenesTests, RotationOfSimpleWorldAndOneEmptyObjectAndOneObject)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 0, 0, 0 });
      // no relative positions
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

      const Object::Positions positions = { { 0, 0, 0 } };
      EXPECT_TRUE(is_mostly_equal(child.getAbsolutePositions(), positions));

      ASSERT_EQ(child.getChildren().size(), 1);

      {
         auto & grandchild = *(child.getChildren()[0]);

         const Object::Positions positions = { { -1, -3, 5 },{ 4, 2, 0 } };
         EXPECT_TRUE(is_mostly_equal(grandchild.getAbsolutePositions(), positions));
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
//
// Rotation And Translation
//
////////////////////////////////////////////////////////////////////////////////

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


TEST(AverageScenesTests, RotationAndTranslationOfSimpleWorldAndOneEmptyObjectAndOneObject)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      // No relative position
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

      const Object::Positions positions = { { 1, 2, 3 } };
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

////////////////////////////////////////////////////////////////////////////////
//
// Scaling
//
////////////////////////////////////////////////////////////////////////////////

TEST(AverageScenesTests, ScalingOfSimpleWorldAndObject)
{
   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(3, 2, 1));
      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   auto & child = *(world.getChildren()[0]);

// const Object::Positions positions = { { 0, 0, 0 },{ 4, 7, 9 } };     // original
// const Object::Positions positions = { { 0, 0, 0 },{ 4, 7, 9 } };     // after rotating
// const Object::Positions positions = { { 0, 0, 0 },{ 12, 14, 9 } };   // after scaling
   const Object::Positions positions = { { 1, 2, 3 },{ 13, 16, 12 } };  // after translating
   EXPECT_EQ(child.getAbsolutePositions(), positions);
}


TEST(AverageScenesTests, ScalingOfSimpleWorldAndTwoObjects)
{
   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(3, 2, 1));
      world.getChildren().push_back(o.clone());
   }

   {
      DefaultObject o;
      o.setCenter({ 3, 0, -1 });
      o.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(4, 3, 2));
      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 2);

   {
      auto & child = *(world.getChildren()[0]);

//    const Object::Positions positions = { { 0, 0, 0 },{ 4, 7, 9 } };     // original
//    const Object::Positions positions = { { 0, 0, 0 },{ 4, 7, 9 } };     // after rotating
//    const Object::Positions positions = { { 0, 0, 0 },{ 12, 14, 9 } };   // after scaling
      const Object::Positions positions = { { 1, 2, 3 },{ 13, 16, 12 } };  // after translating
      EXPECT_EQ(child.getAbsolutePositions(), positions);
   }

   {
      auto & child = *(world.getChildren()[1]);

//    const Object::Positions positions = { { 1, 3, 5 },{ -4, -2, 0 } };   // original
//    const Object::Positions positions = { { 1, 3, 5 },{ -4, -2, 0 } };   // after rotating
//    const Object::Positions positions = { { 4, 9, 10 },{ -16, -6, 0 } }; // after scaling
      const Object::Positions positions = { { 7, 9, 9 },{ -13, -6, -1 } }; // after translating
      EXPECT_EQ(child.getAbsolutePositions(), positions);
   }
}


TEST(AverageScenesTests, ScalingOfSimpleWorldAndOneObjectAndOneObject)
{
   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(3, 2, 1));

      {
         DefaultObject o2;
         o2.setCenter({ 3, 0, -1 });
         o2.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
         o2.setRelativeScaling(maths::utilities::createScaleMatrix<float>(4, 3, 2));
         o.getChildren().push_back(o2.clone());
      }

      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   {
      auto & child = *(world.getChildren()[0]);

//    const Object::Positions positions = { { 0, 0, 0 },{ 4, 7, 9 } };              // original
//    const Object::Positions positions = { { 0, 0, 0 },{ 4, 7, 9 } };              // after rotating
//    const Object::Positions positions = { { 0, 0, 0 },{ 12, 14, 9 } };            // after scaling
      const Object::Positions positions = { { 1, 2, 3 },{ 13, 16, 12 } };           // after translating
      EXPECT_EQ(child.getAbsolutePositions(), positions);

      ASSERT_EQ(child.getChildren().size(), 1);

      {
         auto & grandchild = *(child.getChildren()[0]);

//       const Object::Positions positions = { { 1, 3, 5 },{ -4, -2, 0 } };         // original
//       const Object::Positions positions = { { 1, 3, 5 },{ -4, -2, 0 } };         // after rotating / grandchild
//       const Object::Positions positions = { { 4, 9, 10 },{ -16, -6, 0 } };       // after scaling / grandchild (4, 3, 2)
//       const Object::Positions positions = { { 7, 9, 9 },{ -13, -6, -1 } };       // after translating / into child coordinates { 3, 0, -1 }
//       const Object::Positions positions = { { 7, 9, 9 },{ -13, -6, -1 } };       // after rotating / child
//       const Object::Positions positions = { { 21, 18, 9 },{ -39, -12, -1 } };    // after scaling / child
         const Object::Positions positions = { { 22, 20, 12 },{ -38, -10, 2 } };    // after translating / into world coordinates
         EXPECT_EQ(grandchild.getAbsolutePositions(), positions);
      }
   }
}


TEST(AverageScenesTests, ScalingOfSimpleWorldAndOneEmptyObjectAndOneObject)
{
   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 } });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(3, 2, 1));

      {
         DefaultObject o2;
         o2.setCenter({ 3, 0, -1 });
         o2.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
         o2.setRelativeScaling(maths::utilities::createScaleMatrix<float>(4, 3, 2));
         o.getChildren().push_back(o2.clone());
      }

      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   {
      auto & child = *(world.getChildren()[0]);

      //    const Object::Positions positions = { { 0, 0, 0 }, };                         // original
      //    const Object::Positions positions = { { 0, 0, 0 }, };                         // after rotating
      //    const Object::Positions positions = { { 0, 0, 0 }, };                         // after scaling
      const Object::Positions positions = { { 1, 2, 3 } };                                // after translating
      EXPECT_EQ(child.getAbsolutePositions(), positions);

      ASSERT_EQ(child.getChildren().size(), 1);

      {
         auto & grandchild = *(child.getChildren()[0]);

         //       const Object::Positions positions = { { 1, 3, 5 },{ -4, -2, 0 } };         // original
         //       const Object::Positions positions = { { 1, 3, 5 },{ -4, -2, 0 } };         // after rotating / grandchild
         //       const Object::Positions positions = { { 4, 9, 10 },{ -16, -6, 0 } };       // after scaling / grandchild (4, 3, 2)
         //       const Object::Positions positions = { { 7, 9, 9 },{ -13, -6, -1 } };       // after translating / into child coordinates { 3, 0, -1 }
         //       const Object::Positions positions = { { 7, 9, 9 },{ -13, -6, -1 } };       // after rotating / child
         //       const Object::Positions positions = { { 21, 18, 9 },{ -39, -12, -1 } };    // after scaling / child
         const Object::Positions positions = { { 22, 20, 12 },{ -38, -10, 2 } };    // after translating / into world coordinates
         EXPECT_EQ(grandchild.getAbsolutePositions(), positions);
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
//
// Rotation and Scaling and Translation
//
////////////////////////////////////////////////////////////////////////////////

TEST(AverageScenesTests, RotationAndScalingAndTranslationOfSimpleWorldAndObject)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeRotations({ r });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(3, 2, 1));
      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   auto & child = *(world.getChildren()[0]);

// const Object::Positions positions = { { 0, 0, 0 },{ 4, 7, 9 } };           // original
// const Object::Positions positions = { { 0, 0, 0 },{ -7, 4, 9 } };          // after rotating
// const Object::Positions positions = { { 0, 0, 0 },{ -21, 8, 9 } };         // after scaling
   const Object::Positions positions = { { 1, 2, 3 },{ -20, 10, 12 } };       // after translating

   EXPECT_TRUE(is_mostly_equal(positions, child.getAbsolutePositions()))
      << "                   positions:" << anythingPrinter(positions) << "\n"
      << "child.getAbsolutePositions():" << anythingPrinter(child.getAbsolutePositions()) << "\n";
}


TEST(AverageScenesTests, RotationAndScalingAndTranslationOfSimpleWorldAndTwoObjects)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);
   const auto r2 = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_3_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeRotations({ r });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(3, 2, 1));
      world.getChildren().push_back(o.clone());
   }

   {
      DefaultObject o;
      o.setCenter({ 5, 3, -1 });
      o.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
      o.setRelativeRotations({ r2 });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(4, 3, 2));
      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 2);

   {
      auto & child = *(world.getChildren()[0]);

//    const Object::Positions positions = { { 0, 0, 0 },{ 4, 7, 9 } };           // original
//    const Object::Positions positions = { { 0, 0, 0 },{ -7, 4, 9 } };          // after rotating
//    const Object::Positions positions = { { 0, 0, 0 },{ -21, 8, 9 } };         // after scaling
      const Object::Positions positions = { { 1, 2, 3 },{ -20, 10, 12 } };       // after translating

      EXPECT_TRUE(is_mostly_equal(positions, child.getAbsolutePositions()))
         << "                   positions:" << anythingPrinter(positions) << "\n"
         << "child.getAbsolutePositions():" << anythingPrinter(child.getAbsolutePositions()) << "\n";
   }

   {
      auto & child = *(world.getChildren()[1]);

//    const Object::Positions positions = { { 1, 3, 5 },{ -4, -2, 0 } };         // original
//    const Object::Positions positions = { { 3, -1, 5 },{ -2, 4, 0 } };         // after rotating
//    const Object::Positions positions = { { 12, -3, 10 },{ -8, 12, 0 } };      // after scaling
      const Object::Positions positions = { { 17, 0, 9 },{ -3, 15, -1 } };       // after translating

      EXPECT_TRUE(is_mostly_equal(positions, child.getAbsolutePositions()))
         << "                   positions:" << anythingPrinter(positions) << "\n"
         << "child.getAbsolutePositions():" << anythingPrinter(child.getAbsolutePositions()) << "\n";
   }
}


TEST(AverageScenesTests, RotationAndScalingAndTranslationOfSimpleWorldAndOneObjectAndOneObject)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 },{ 4, 7, 9 } });
      o.setRelativeRotations({ r });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(3, 2, 1));

      {
         DefaultObject o2;
         o2.setCenter({ 5, 3, -1 });
         o2.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
         o2.setRelativeRotations({ r });
         o2.setRelativeScaling(maths::utilities::createScaleMatrix<float>(4, 3, 2));
         o.getChildren().push_back(o2.clone());
      }

      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   {
      auto & child = *(world.getChildren()[0]);

//    const Object::Positions positions = { { 0, 0, 0 },{ 4, 7, 9 } };           // original
//    const Object::Positions positions = { { 0, 0, 0 },{ -7, 4, 9 } };          // after rotating
//    const Object::Positions positions = { { 0, 0, 0 },{ -21, 8, 9 } };         // after scaling
      const Object::Positions positions = { { 1, 2, 3 },{ -20, 10, 12 } };       // after translating

      EXPECT_TRUE(is_mostly_equal(positions, child.getAbsolutePositions()))
         << "                   positions: " << anythingPrinter(positions) << "\n"
         << "child.getAbsolutePositions(): " << anythingPrinter(child.getAbsolutePositions()) << "\n";

      ASSERT_EQ(child.getChildren().size(), 1);

      {
         auto & grandchild = *(child.getChildren()[0]);

//       const Object::Positions positions = { { 1, 3, 5 },{ -4, -2, 0 } };      // original
//       const Object::Positions positions = { { -3, 1, 5 },{ 2, -4, 0 } };      // after rotating / grandchild PI/2
//       const Object::Positions positions = { { -12, 3, 10 },{ 8, -12, 0 } };   // after scaling / grandchild (4, 3, 2)
//       const Object::Positions positions = { { -7, 6, 9 },{ 13, -9, -1 } };    // after translating / into child coordinates { 5, 3, -1 }
//       const Object::Positions positions = { { -6, -7, 9 },{ 9, 13, -1 } };    // after rotating / child PI/2
//       const Object::Positions positions = { { -18, -14, 9 },{ 27, 26, -1 } }; // after scaling / child (3, 2, 1)
         const Object::Positions positions = { { -17, -12, 12 },{ 28, 28, 2 } }; // after translating / into world coordinates { 1, 2, 3 }

         EXPECT_TRUE(is_mostly_equal(positions, grandchild.getAbsolutePositions()))
            << "                        positions: " << anythingPrinter(positions) << "\n"
            << "grandchild.getAbsolutePositions(): " << anythingPrinter(grandchild.getAbsolutePositions()) << "\n";
      }
   }
}


TEST(AverageScenesTests, RotationAndScalingAndTranslationOfSimpleWorldAndOneEmptyObjectAndOneObject)
{
   const auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   World world;

   {
      DefaultObject o;
      o.setCenter({ 1, 2, 3 });
      o.setRelativePositions({ { 0, 0, 0 } });
      o.setRelativeRotations({ r });
      o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(3, 2, 1));

      {
         DefaultObject o2;
         o2.setCenter({ 5, 3, -1 });
         o2.setRelativePositions({ { 1, 3, 5 },{ -4, -2, 0 } });
         o2.setRelativeRotations({ r });
         o2.setRelativeScaling(maths::utilities::createScaleMatrix<float>(4, 3, 2));
         o.getChildren().push_back(o2.clone());
      }

      world.getChildren().push_back(o.clone());
   }

   calculateAbsolutePositionRecursive(world);

   ASSERT_EQ(world.getChildren().size(), 1);

   {
      auto & child = *(world.getChildren()[0]);

      //    const Object::Positions positions = { { 0, 0, 0 }  };                // original
      //    const Object::Positions positions = { { 0, 0, 0 }  };                // after rotating
      //    const Object::Positions positions = { { 0, 0, 0 }  };                // after scaling
      const Object::Positions positions = { { 1, 2, 3 } };                       // after translating

      EXPECT_TRUE(is_mostly_equal(positions, child.getAbsolutePositions()))
         << "                   positions: " << anythingPrinter(positions) << "\n"
         << "child.getAbsolutePositions(): " << anythingPrinter(child.getAbsolutePositions()) << "\n";

      ASSERT_EQ(child.getChildren().size(), 1);

      {
         auto & grandchild = *(child.getChildren()[0]);

         //       const Object::Positions positions = { { 1, 3, 5 },{ -4, -2, 0 } };      // original
         //       const Object::Positions positions = { { -3, 1, 5 },{ 2, -4, 0 } };      // after rotating / grandchild PI/2
         //       const Object::Positions positions = { { -12, 3, 10 },{ 8, -12, 0 } };   // after scaling / grandchild (4, 3, 2)
         //       const Object::Positions positions = { { -7, 6, 9 },{ 13, -9, -1 } };    // after translating / into child coordinates { 5, 3, -1 }
         //       const Object::Positions positions = { { -6, -7, 9 },{ 9, 13, -1 } };    // after rotating / child PI/2
         //       const Object::Positions positions = { { -18, -14, 9 },{ 27, 26, -1 } }; // after scaling / child (3, 2, 1)
         const Object::Positions positions = { { -17, -12, 12 },{ 28, 28, 2 } }; // after translating / into world coordinates { 1, 2, 3 }

         EXPECT_TRUE(is_mostly_equal(positions, grandchild.getAbsolutePositions()))
            << "                        positions: " << anythingPrinter(positions) << "\n"
            << "grandchild.getAbsolutePositions(): " << anythingPrinter(grandchild.getAbsolutePositions()) << "\n";
      }
   }
}


}