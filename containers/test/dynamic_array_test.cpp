//
// Created by Divium on 09/09/2023.
//
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <iostream>

#include "../src/dynamic_array.hpp"
#include "../src/dummy.hpp"

typedef std::shared_ptr<Dummy> spd;

TEST_CASE("Sample test", "[dyn]") {
    REQUIRE(2 == 2);
}

SCENARIO("Dynamic array must resize correctly") {
    GIVEN("120 objects inside the array") {
        dvm::DynamicArray<Dummy> dynamic_array{};
        {
            for (int i = 1; i <= 120; i++)
                dynamic_array.push_back(std::make_shared<Dummy>());

            REQUIRE(dynamic_array.size() == 119);
        }

        WHEN("Removing 11 objects") {
            for (int i = 1; i <= 11; i++)
                dynamic_array.pop_back();

            THEN("Size changes") {
                REQUIRE(dynamic_array.size() == 108);
            }
        }

        WHEN("Removing 2 objects in the center") {
            dynamic_array.remove(50);
            dynamic_array.remove(50);

            THEN("Size changes") {
                REQUIRE(dynamic_array.size() == 117);
            }
        }

        WHEN("Adding 2 objects in the center") {
            dynamic_array.insert(50, std::make_shared<Dummy>());
            dynamic_array.insert(50, std::make_shared<Dummy>());

            THEN("Size changes") {
                REQUIRE(dynamic_array.size() == 121);
            }
        }
    }
}