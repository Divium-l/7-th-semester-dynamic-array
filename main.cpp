//
// Created by Divium on 09/09/2023.
//
#include <iostream>
#include "dynamic_array.hpp"

struct Dummy {
    inline static int count;
    int id;
    Dummy() {
        id = count++;
        std::cout << std::format("Dummy {} created", id) << std::endl;
    }
    ~Dummy() {
        std::cout << std::format("Dummy {} DELETED", id) << std::endl;
    }
};

int main() {
    auto arr = dvm::DynamicArray<Dummy>();

    for (int i = 0; i < 10; i++) {
        std::shared_ptr<Dummy> dummy(new Dummy());
        arr.push_back(dummy);
    }

    for (int i = 0; i < 10; i++) {
        arr.pop_back();
    }

    return 0;
}