//
// Created by Divium on 09/09/2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include "dynamic_array.hpp"
#include "test/dummy.hpp"

int main() {
    auto arr = dvm::DynamicArray<Dummy>();
    std::vector<int> v{};

    for (int i = 0; i < 11; i++) {
        std::shared_ptr<Dummy> dummy(new Dummy());
        arr.push_back(dummy);
    }

    auto max = arr.max([](auto lhs, auto rhs) {
        return lhs->id - rhs->id;
    });

    auto min = arr.min([](auto lhs, auto rhs) {
        return lhs->id - rhs->id;
    });

    std::cout << max->id << std::endl;
    std::cout << min->id << std::endl;

    for (int i = 0; i < 10; i++) {
        arr.pop_back();
    }

    return 0;
}