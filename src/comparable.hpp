//
// Created by Divium on 18/09/2023.
//

#pragma once

namespace dvm {
    template<class T> concept CComparable = requires(T object, T object2) {
        object > object2;
        object < object2;
    };
    template<class T> concept CIComparable = requires(T object, T object2) {
        object.compare(object);
    };

    /**
     * Interface for comparing
     * @tparam T CComparable
     */
    template<class T> class IComparable {
        /**
         *
         *  <ul>
         *      <li>Must return -1 if lhs \<  rhs</li>
         *      <li>Must return  0 if lhs == rhs</li>
         *      <li>Must return  1 if lhs >  rhs</li>
         * </ul>
         * @return One of the following [-1, 0, 1]
         */
        virtual int8_t compare(T& lhs, T& rhs) = 0;
    };
}
