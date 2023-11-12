//
// Created by Divium on 18/09/2023.
//

#pragma once

#include <iostream>
#include <format>

/**
 * Structure for testing
 */
struct Dummy {
    inline static int count;
    int id;
    bool enable_print;

    explicit Dummy(bool debug_print = false) {
        id = count++;
        enable_print = debug_print;

        if (enable_print)
            std::cout << std::format("Dummy {} created", id) << std::endl;
    }

    explicit Dummy(int id, bool debug_print = false) {
        this->id = id;
        enable_print = debug_print;
        if (enable_print)
            std::cout << std::format("Dummy {} created", id) << std::endl;
    }

    ~Dummy() {
        if (enable_print)
            std::cout << std::format("Dummy {} DELETED", id) << std::endl;
    }

    friend bool operator< (const Dummy& lhs, const Dummy& rhs) {
        return lhs.id > rhs.id;
    }

    friend bool operator> (const Dummy& lhs, const Dummy& rhs) {
        return lhs.id < rhs.id;
    }
};