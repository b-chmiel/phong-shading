#define CATCH_CONFIG_MAIN

#include "../src/vectorUtils.h"
#include "../lib/catch.hpp"
#include "SFML/System/Vector3.hpp"

using namespace sf;

TEST_CASE("utils Test")
{
    SECTION("Length of vector")
    {
        SECTION("Easy")
        {
            auto vector = Vector3f(0, 100.0f, 0);
            CHECK(utils::lengthOfVector(vector) == 100.0f);
        }
        SECTION("All coordinates")
        {
            auto vector = Vector3f(12.0, 13.0, 14.0);
            auto result = utils::lengthOfVector(vector);
            CHECK(result >= 22.0f);
            CHECK(result <= 23.0f);
        }
        SECTION("All coordinates negative")
        {
            auto vector = Vector3f(-12.0f, -13.0f, -14.0f);
            auto result = utils::lengthOfVector(vector);
            CHECK(result >= 22.0f);
            CHECK(result <= 23.0f);
        }
    }

    SECTION("Distance between points")
    {
        auto a = Vector3f(7, 4, 3);
        auto b = Vector3f(17, 6, 2);

        auto result = utils::distanceBetweenPoints(a, b);

        CHECK(result >= 10.2f);
        CHECK(result <= 10.3f);
    }

    SECTION("Dot product")
    {
        auto a = Vector3f(12.0, 432.3, 112.8);
        auto b = Vector3f(421.1, 23.1, 2.2);

        auto result = utils::dotProduct(a, b);
        CHECK(result >= 15287.49);
        CHECK(result <= 15287.5);
    }

    SECTION("Divide component wise")
    {
        auto left = Vector3f(142.3, 234.342, 12542.3);
        auto right = Vector3f(2.3, 3.342, 242.5);

        auto result = utils::divideComponentWise(left, right);
        CHECK(result.x >= 61.86f);
        CHECK(result.x <= 61.87f);
        CHECK(result.y >= 70.12f);
        CHECK(result.y <= 70.13f);
        CHECK(result.z >= 51.72f);
        CHECK(result.z <= 51.73);
    }

    SECTION("Unit vector")
    {
        SECTION("Floating points")
        {
            auto vector = Vector3f(453.2, -234.1, 34.52);

            auto result = utils::unitVector(vector);
            CHECK(result.x >= 0.886f);
            CHECK(result.x <= 0.887f);
            CHECK(result.y >= -0.46f);
            CHECK(result.y <= -0.45f);
            CHECK(result.z >= 0.067f);
            CHECK(result.z <= 0.068f);
        }
    }
}