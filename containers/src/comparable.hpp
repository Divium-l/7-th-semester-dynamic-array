//
// Created by Divium on 18/09/2023.
//

#pragma once

namespace dvm {
    template<class T> concept CComparable = requires(T object, T object2) {
        object > object2;
        object < object2;
    };
}
