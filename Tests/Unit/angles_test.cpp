#include "gtest/gtest.h"
#include "transformer.h"

TEST(Transform, ReduceAngles) {
  using namespace Transform;
  Spherical expected{1, 270, 180};
  auto result = ReduceAngles({1, -90, 540});
  EXPECT_NEAR(expected.theta, result.theta, 0.01);
  EXPECT_NEAR(expected.phi, result.phi, 0.01);
  EXPECT_NEAR(expected.range, result.range, 0.01);

  expected = {1, 10, 15};
  result = ReduceAngles({1, -350 - 360, 15 + 720});
  EXPECT_NEAR(expected.theta, result.theta, 0.01);
  EXPECT_NEAR(expected.phi, result.phi, 0.01);
  EXPECT_NEAR(expected.range, result.range, 0.01);
}

TEST(Transform, ReducePositiveAngles) {
  using namespace Transform;
  Spherical expected{1, -120, 45};
  auto result = ReducePositiveAngles({1, 240, 45});
  EXPECT_NEAR(expected.theta, result.theta, 0.01);
  EXPECT_NEAR(expected.phi, result.phi, 0.01);
  EXPECT_NEAR(expected.range, result.range, 0.01);

  expected = {1, 180, -10};
  result = ReducePositiveAngles({1, 180, 350});
  EXPECT_NEAR(expected.theta, result.theta, 0.01);
  EXPECT_NEAR(expected.phi, result.phi, 0.01);
  EXPECT_NEAR(expected.range, result.range, 0.01);
}

TEST(Transform, CartesianToPNU) {
  using namespace Transform;

  Spherical expected{1, 90, 90 - 90};
  auto result = CartesianToPNU({1, 0, 0});
  EXPECT_NEAR(expected.theta, 270.0 - result.theta, 0.01);
  EXPECT_NEAR(expected.phi, result.phi, 0.01);
  EXPECT_NEAR(expected.range, result.range, 0.01);

  expected = {2, 90, 90 - 0};
  result = CartesianToPNU({0, 0, 2});
  EXPECT_NEAR(expected.theta, 270.0 - result.theta, 0.01);
  EXPECT_NEAR(expected.phi, result.phi, 0.01);
  EXPECT_NEAR(expected.range, result.range, 0.01);

  expected = {1.7321, 54.735610, 90 - 45};
  result = CartesianToPNU({1, 1, 1});
  EXPECT_NEAR(expected.theta, 270.0 - result.theta, 0.01);
  EXPECT_NEAR(expected.phi, result.phi, 0.01);
  EXPECT_NEAR(expected.range, result.range, 0.01);

  expected = {3.741657, 122.311533, 90 - 71.565051};
  result = CartesianToPNU({3, -2, 1});
  EXPECT_NEAR(expected.theta, 270.0 - result.theta, 0.01);
  EXPECT_NEAR(expected.phi, result.phi, 0.01);
  EXPECT_NEAR(expected.range, result.range, 0.01);

  expected = {29.899833, 109.539098, 152.5255023};
  result = CartesianToPNU({-25, -10, 13});
  EXPECT_NEAR(expected.theta, 270.0 - result.theta, 0.01);
  EXPECT_NEAR(expected.phi, result.phi, 0.01);
  EXPECT_NEAR(expected.range, result.range, 0.01);

  expected = {178.955302, 127.928573, 90 - 67.067900};
  result = CartesianToPNU({130, -110, 55});
  EXPECT_NEAR(expected.theta, 270.0 - result.theta, 0.01);
  EXPECT_NEAR(expected.phi, result.phi, 0.01);
  EXPECT_NEAR(expected.range, result.range, 0.01);
}
