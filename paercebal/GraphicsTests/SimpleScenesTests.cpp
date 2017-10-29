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

   calculateAbsolutePosition(o);

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

   calculateAbsolutePosition(o);

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

      calculateAbsolutePosition(o);

      Object::Positions positions = { { 0, 0, 0 },{ -4, 2, 6 } };

      EXPECT_EQ(o.getAbsolutePositions().size(), 2);
      EXPECT_TRUE(is_mostly_equal(o.getAbsolutePositions(), positions));
   }

   {
      DefaultObject o;
      auto r = maths::utilities::createRotationMatrixAroundX(maths::utilities::pi<float>);

      o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
      o.setRelativeRotations({ r });

      EXPECT_EQ(o.getAbsolutePositions().size(), 0);

      calculateAbsolutePosition(o);

      Object::Positions positions = { { 0, 0, 0 },{ 2, -4, -6 } };

      EXPECT_EQ(o.getAbsolutePositions().size(), 2);
      EXPECT_TRUE(is_mostly_equal(o.getAbsolutePositions(), positions));
   }

   {
      DefaultObject o;
      auto r = maths::utilities::createRotationMatrixAroundX(maths::utilities::pi_1_2<float>);

      o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
      o.setRelativeRotations({ r, r });

      EXPECT_EQ(o.getAbsolutePositions().size(), 0);

      calculateAbsolutePosition(o);

      Object::Positions positions = { { 0, 0, 0 },{ 2, -4, -6 } };

      EXPECT_EQ(o.getAbsolutePositions().size(), 2);
      EXPECT_TRUE(is_mostly_equal(o.getAbsolutePositions(), positions));
   }

   {
      DefaultObject o;
      auto r = maths::utilities::createRotationMatrixAroundX(maths::utilities::pi_1_2<float>);

      o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
      o.setRelativeRotations({ r, r, r });

      EXPECT_EQ(o.getAbsolutePositions().size(), 0);

      calculateAbsolutePosition(o);

      Object::Positions positions = { { 0, 0, 0 },{ 2, 6, -4 } };

      EXPECT_EQ(o.getAbsolutePositions().size(), 2);
      EXPECT_TRUE(is_mostly_equal(o.getAbsolutePositions(), positions));
   }

   {
      DefaultObject o;
      auto r = maths::utilities::createRotationMatrixAroundX(maths::utilities::pi_1_2<float>);

      o.setRelativePositions({ { 0, 0, 0 },{ 2, 4, 6 } });
      o.setRelativeRotations({ r, r, r, r });

      EXPECT_EQ(o.getAbsolutePositions().size(), 0);

      calculateAbsolutePosition(o);

      Object::Positions positions = { { 0, 0, 0 },{ 2, 4, 6 } };

      EXPECT_EQ(o.getAbsolutePositions().size(), 2);
      EXPECT_TRUE(is_mostly_equal(o.getAbsolutePositions(), positions));
   }
}




}