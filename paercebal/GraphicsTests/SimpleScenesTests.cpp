#include <paercebal/GraphicsTests/main.hpp>

#include <paercebal/Graphics/world/DefaultObject.hpp>
#include <paercebal/Graphics/maths/utilities.hpp>

#include <cstdlib>
#include <cmath>
#include <limits>

#include <gtest/gtest.h>


namespace paercebal::Graphics::world::tests
{

TEST(SimpleScenesTests, SimpleInitialization)
{
   DefaultObject o;

   o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });

   EXPECT_EQ(o.getAbsolutePositions().size(), 0);

   private_::initializeAndCalculateAbsolutePosition(o);

   Object::Positions positions = { { 0, 0, 0 },{ 2, 4, 6 } };

   EXPECT_EQ(o.getAbsolutePositions().size(), 2);
   EXPECT_EQ(o.getAbsolutePositions(), positions);
}

TEST(SimpleScenesTests, SimpleTranslation)
{
   DefaultObject o;

   o.setCenter({ 1, 2, 3 });
   o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });

   EXPECT_EQ(o.getAbsolutePositions().size(), 0);

   private_::initializeAndCalculateAbsolutePosition(o);

   Object::Positions positions = { { 1, 2, 3 },{ 3, 6, 9 } };

   EXPECT_EQ(o.getAbsolutePositions().size(), 2);
   EXPECT_EQ(o.getAbsolutePositions(), positions);
}

TEST(SimpleScenesTests, SimpleRotation)
{
   {
      DefaultObject o;
      auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

      o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
      o.setRelativeRotations({ r });

      EXPECT_EQ(o.getAbsolutePositions().size(), 0);

      private_::initializeAndCalculateAbsolutePosition(o);

      Object::Positions positions = { { 0, 0, 0 },{ -4, 2, 6 } };

      EXPECT_EQ(o.getAbsolutePositions().size(), 2);
      EXPECT_TRUE(is_mostly_equal(positions, o.getAbsolutePositions()))
         << "                position: " << anythingPrinter(positions) << "\n"
         << "o.getAbsolutePositions(): " << anythingPrinter(o.getAbsolutePositions()) << "\n";
   }

   {
      DefaultObject o;
      auto r = maths::utilities::createRotationMatrixAroundX(maths::utilities::pi<float>);

      o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
      o.setRelativeRotations({ r });

      EXPECT_EQ(o.getAbsolutePositions().size(), 0);

      private_::initializeAndCalculateAbsolutePosition(o);

      Object::Positions positions = { { 0, 0, 0 },{ 2, -4, -6 } };

      EXPECT_EQ(o.getAbsolutePositions().size(), 2);
      EXPECT_TRUE(is_mostly_equal(positions, o.getAbsolutePositions()))
         << "                position: " << anythingPrinter(positions) << "\n"
         << "o.getAbsolutePositions(): " << anythingPrinter(o.getAbsolutePositions()) << "\n";
   }

   {
      DefaultObject o;
      auto r = maths::utilities::createRotationMatrixAroundX(maths::utilities::pi_1_2<float>);

      o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
      o.setRelativeRotations({ r, r });

      EXPECT_EQ(o.getAbsolutePositions().size(), 0);

      private_::initializeAndCalculateAbsolutePosition(o);

      Object::Positions positions = { { 0, 0, 0 },{ 2, -4, -6 } };

      EXPECT_EQ(o.getAbsolutePositions().size(), 2);
      EXPECT_TRUE(is_mostly_equal(positions, o.getAbsolutePositions()))
         << "                position: " << anythingPrinter(positions) << "\n"
         << "o.getAbsolutePositions(): " << anythingPrinter(o.getAbsolutePositions()) << "\n";
   }

   {
      DefaultObject o;
      auto r = maths::utilities::createRotationMatrixAroundX(maths::utilities::pi_1_2<float>);

      o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
      o.setRelativeRotations({ r, r, r });

      EXPECT_EQ(o.getAbsolutePositions().size(), 0);

      private_::initializeAndCalculateAbsolutePosition(o);

      Object::Positions positions = { { 0, 0, 0 },{ 2, 6, -4 } };

      EXPECT_EQ(o.getAbsolutePositions().size(), 2);
      EXPECT_TRUE(is_mostly_equal(positions, o.getAbsolutePositions()))
         << "                position: " << anythingPrinter(positions) << "\n"
         << "o.getAbsolutePositions(): " << anythingPrinter(o.getAbsolutePositions()) << "\n";
   }

   {
      DefaultObject o;
      auto r = maths::utilities::createRotationMatrixAroundX(maths::utilities::pi_1_2<float>);

      o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
      o.setRelativeRotations({ r, r, r, r });

      EXPECT_EQ(o.getAbsolutePositions().size(), 0);

      private_::initializeAndCalculateAbsolutePosition(o);

      Object::Positions positions = { { 0, 0, 0 },{ 2, 4, 6 } };

      EXPECT_EQ(o.getAbsolutePositions().size(), 2);
      EXPECT_TRUE(is_mostly_equal(positions, o.getAbsolutePositions()))
         << "                position: " << anythingPrinter(positions) << "\n"
         << "o.getAbsolutePositions(): " << anythingPrinter(o.getAbsolutePositions()) << "\n";
   }
}

TEST(SimpleScenesTests, SimpleScaling)
{
   DefaultObject o;

   o.setCenter({ 0, 0, 0 });
   o.setRelativePositions({ { 0, 0, 0 },{ 3, 7, -2 } });
   o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(2, 3, 5));

   EXPECT_EQ(o.getAbsolutePositions().size(), 0);

   private_::initializeAndCalculateAbsolutePosition(o);

   Object::Positions positions = { { 0, 0, 0 },{ 6, 21, -10 } };

   EXPECT_EQ(o.getAbsolutePositions().size(), 2);
   EXPECT_TRUE(is_mostly_equal(positions, o.getAbsolutePositions()))
      << "                position: " << anythingPrinter(positions) << "\n"
      << "o.getAbsolutePositions(): " << anythingPrinter(o.getAbsolutePositions()) << "\n";
}


TEST(SimpleScenesTests, ComplexCaseForOneObject)
{
   DefaultObject o;
   auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   o.setCenter({ 1, 2, 3 });
   o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
   o.setRelativeRotations({ r });

   private_::initializeAndCalculateAbsolutePosition(o);

// Object::Positions positions = { { 0, 0, 0 },{ 2, 4, 6 } };
// Object::Positions positions = { { 0, 0, 0 },{ -4, 2, 6 } }; // after rotation
   Object::Positions positions = { { 1, 2, 3 },{ -3, 4, 9 } }; // after translating

   EXPECT_EQ(o.getAbsolutePositions().size(), 2);
   EXPECT_TRUE(is_mostly_equal(positions, o.getAbsolutePositions()))
      << "                position: " << anythingPrinter(positions) << "\n"
      << "o.getAbsolutePositions(): " << anythingPrinter(o.getAbsolutePositions()) << "\n";
}


TEST(SimpleScenesTests, MoreComplexCaseForOneObject)
{
   DefaultObject o;
   auto r = maths::utilities::createRotationMatrixAroundZ(maths::utilities::pi_1_2<float>);

   o.setCenter({ 1, 2, 3 });
   o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
   o.setRelativeRotations({ r });
   o.setRelativeScaling(maths::utilities::createScaleMatrix<float>(2, 3, 5));

   private_::initializeAndCalculateAbsolutePosition(o);

   // Object::Positions positions = { { 0, 0, 0 },{ 2, 4, 6 } };
   // Object::Positions positions = { { 0, 0, 0 },{ -4, 2, 6 } }; // after rotation
   // Object::Positions positions = { { 0, 0, 0 },{ -8, 6, 30 } }; // after scaling
   Object::Positions positions = { { 1, 2, 3 },{ -7, 8, 33 } }; // after translating

   EXPECT_EQ(o.getAbsolutePositions().size(), 2);
   EXPECT_TRUE(is_mostly_equal(positions, o.getAbsolutePositions()))
      << "                position: " << anythingPrinter(positions) << "\n"
      << "o.getAbsolutePositions(): " << anythingPrinter(o.getAbsolutePositions()) << "\n";
}


}