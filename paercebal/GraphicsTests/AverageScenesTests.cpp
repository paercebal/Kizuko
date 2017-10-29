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

TEST(AverageScenesTests, SimpleWorldAndObject)
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

TEST(AverageScenesTests, SimpleWorldAndTwoObjects)
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



}