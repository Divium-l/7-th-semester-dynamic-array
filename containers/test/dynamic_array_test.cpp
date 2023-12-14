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
        REQUIRE(dynamic_array.is_empty() == true);

        {
            for (int i = 1; i <= 120; i++)
                dynamic_array.push_back(std::make_shared<Dummy>());

            REQUIRE(dynamic_array.size() == 120);
        }

        WHEN("Removing 11 objects") {
            for (int i = 1; i <= 11; i++)
                dynamic_array.pop_back();

            THEN("Size changes") {
                REQUIRE(dynamic_array.size() == 109);
            }
        }

        WHEN("Removing 2 objects in the center") {
            dynamic_array.remove(50);
            dynamic_array.remove(50);

            THEN("Size changes") {
                REQUIRE(dynamic_array.size() == 118);
            }
        }

        WHEN("Adding 2 objects in the center") {
            dynamic_array.insert(50, std::make_shared<Dummy>());
            dynamic_array.insert(50, std::make_shared<Dummy>());

            THEN("Size changes") {
                REQUIRE(dynamic_array.size() == 122);
            }
        }
    }
}

SCENARIO("Min max functions must work correctly") {
    GIVEN("100 objects inside the array") {
        dvm::DynamicArray<Dummy> dynamic_array{};
        for (int i = 1; i <= 100; i++)
            dynamic_array.push_back(std::make_shared<Dummy>());

        REQUIRE(dynamic_array.size() == 100);

        spd max_dummy{new Dummy(INT32_MAX)};
        dynamic_array.push_back(max_dummy);

        spd min_dummy{new Dummy(INT32_MIN)};
        dynamic_array.push_back(min_dummy);

        auto comparator =  [](auto lhs, auto rhs)  {
            if (lhs->id > rhs->id) {
                return 1;
            }
            else if (lhs->id < rhs->id) {
                return -1;
            }
            else {
                return 0;
            }
        };

        WHEN("Finding max") {
            auto max = dynamic_array.max(comparator);

            THEN("max value must be correct") {
                REQUIRE(max->id == INT32_MAX);
            }
        }

        WHEN("Finding min") {
            auto min = dynamic_array.min(comparator);

            THEN("min value must be correct") {
                REQUIRE(min->id == INT32_MIN);
            }
        }
    }
}