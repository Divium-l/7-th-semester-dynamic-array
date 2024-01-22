//
// Created by Divium on 08/09/2023.
//
#pragma once

#include <stdexcept>
#include <memory>
#include <format>
#include <iostream>
#include "comparable.hpp"

/*
 * If uncommenting, uncomment at the EOF!!!
#define INITIAL_SIZE 5
#define GROW_SIZE 5
#define SHRINK_UNTIL 5
#define SHRINK_THRESHOLD 5
*/
namespace dvm {
    /**
     * @brief Dynamic array implementation using smart pointers
     */
    template<dvm::CComparable T> class DynamicArray {
    private:
        static const size_t INITIAL_SIZE = 5;
        static const size_t GROW_SIZE = 5;
        static const size_t SHRINK_UNTIL = 5;
        static const size_t SHRINK_THRESHOLD = 10;

        size_t m_last_index;
        size_t m_size;
        std::unique_ptr<std::shared_ptr<T>[]> m_array;

#pragma region "Utils"
        /**
         * Grows the array if capacity is reached by <i>GROW_SIZE</i>
         * <br>
         * <b>Call before adding elements</b>
         */
        void _try_grow() {
            if (m_size - 1 >= m_last_index)
                return;

            _resize_to(m_size + GROW_SIZE);
        }

        /**
         * Shrinks the array if number of empty cells more than <i>SHRINK_THRESHOLD</i> until there are <i>SHRINK_UNTIL</i> empty cells left.
         * <br>
         * <b>Call after removing elements</b>
         */
        void _try_shrink() {
            auto empty_cells_count = m_size - 1 - m_last_index;
            if (empty_cells_count <= SHRINK_THRESHOLD)
                return;

            _resize_to(m_last_index + 1 + SHRINK_UNTIL);
        }

        /**
         * Resizes the array to specified size and moves its data. Changes the <i>m_size</i> and <i>m_array</i>.
         * @param size New array size
         */
        void _resize_to(size_t size) {
            m_size = size;
            auto old_array = &m_array;
            auto new_array = _create_array(size);

            _copy(*old_array, new_array);

            m_array = std::move(new_array);
        }

        /**
         * Shifts array elements to the left by one
         * @param shift_from_index Index to be shifted from. Note: element at this index will be removed.
         */
        void _shift_left(size_t shift_from_index) {
            for (size_t i = shift_from_index; i < m_last_index; i++)
                m_array[i] = m_array[i + 1];
        }

        /**
         * Shifts array elements to the right by one
         * @param shift_from_index Index to be shifted from. Note: element at this index will be removed.
         */
        void _shift_right(size_t shift_from_index) {
            for (size_t i = m_last_index; i > shift_from_index; i--)
                m_array[i] = m_array[i - 1];
        }

        /**
         * Creates array of shared pointers wrapped into unique pointer
         * @param size Real size of the array
         * @return unique pointer to created array
         */
        inline std::unique_ptr<std::shared_ptr<T>[]> _create_array(size_t size) {
            return std::unique_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[size]);
        }

        /**
         * Copies data from old array to new array.
         * @param old_array unique pointer of the <b>old</b> array
         * @param new_array unique pointer of the <b>new</b> array
         */
        void _copy(std::unique_ptr<std::shared_ptr<T>[]>& old_array, std::unique_ptr<std::shared_ptr<T>[]>& new_array) {
            for (size_t i = 0; i < m_last_index; i++)
                new_array[i] = old_array[i];
        }

        /**
         * Asserts index is not out of bounds
         * @param index Index
         * @throws std::out_of_range When index is out of bounds
         */
        inline void _assert_bounds(size_t index) const {
            if (index > m_last_index)
                throw std::out_of_range(std::format("Index {} is out of bounds! Current array size is {}", index, m_last_index));
        }
#pragma endregion "Utils"

    public:
        /**
         * @param size Initial size of the array (Default = 5)
         */
        explicit DynamicArray(size_t size = INITIAL_SIZE) {
            m_size = size;
            m_last_index = -1;
            m_array = _create_array(m_size);
        }

#pragma region "Access"
        /**
         * Returns shared pointer of requested element
         * @param index Element location
         * @return Shared pointer of requested element
         * @throws std::out_of_range When index is out of range
         */
        std::shared_ptr<T> get(size_t index) const {
            _assert_bounds(index);

            return m_array[index];
        }

        /**
         * Returns shared pointer of requested element
         * @param index Element location
         * @returns Shared pointer of requested element
         * @throws std::out_of_range When index is out of range
         */
        std::shared_ptr<T> operator[](size_t index) const {
            return get(index);
        }

        /**
         * @returns First element of the array. If array is empty, returns <b>nullptr</b>.
         */
        [[maybe_unused]] std::shared_ptr<T> first() const noexcept {
            if (!is_empty())
                return m_array[0];
            else
                return nullptr;
        }

        /**
         * @returns Last element of the array. If array is empty, returns <b>nullptr</b>.
         */
        [[maybe_unused]] std::shared_ptr<T> last() const noexcept {
            if (!is_empty())
                return m_array[m_last_index];
            else
                return nullptr;
        }
#pragma endregion "Access"

#pragma region "Modifiers"
        /**
         * Appends element at the end
         * @param object Element to add
         */
        [[maybe_unused]] void push_back(std::shared_ptr<T> object) {
            m_last_index++;
            _try_grow();

            m_array[m_last_index] = object;
        }

        /**
         * Inserts element at the specified index
         * @param index Index
         * @param object Element
         * @throws std::out_of_range When index is out of bounds
         */
        [[maybe_unused]] void insert(size_t index, std::shared_ptr<T> object) {
            _assert_bounds(index);
            m_last_index++;
            _try_grow();

            _shift_right(index);
            m_array[index] = object;
        }

        /**
         * Removes last element
         */
        [[maybe_unused]] void pop_back() {
            if (m_last_index < 0)
                return;

            m_array[m_last_index] = std::shared_ptr<T>(nullptr);

            m_last_index--;
            _try_shrink();
        }

        /**
         * Removes element at the specified index
         * @param index Index
         * @throws std::out_of_range When index is out of bounds
         */
        [[maybe_unused]] void remove(size_t index) {
            _assert_bounds(index);

            m_array[index] = nullptr;

            _shift_left(index);
            m_last_index--;
            _try_shrink();
        }
#pragma endregion "Modifiers"

#pragma region "Memory"
        /**
         * @return Number of elements
         */
        [[maybe_unused]] [[nodiscard]] size_t size() const noexcept {
            return m_last_index + 1;
        }

        /**
         * @return The number of elements that can be held in currently allocated space
         */
        [[maybe_unused]] [[nodiscard]] size_t capacity() const noexcept {
            return m_size;
        }

        /**
         * Checks whether the array has no elements
         * @return Boolean
         */
        [[maybe_unused]] [[nodiscard]] bool is_empty() const noexcept {
            return m_last_index == -1;
        }
#pragma endregion "Memory"

        /**
         * @param comparator Lambda function.
         * <ul>
         *  <li>Must return -1 if lhs \<  rhs</li>
         *  <li>Must return  0 if lhs == rhs</li>
         *  <li>Must return  1 if lhs >  rhs</li>
         * </ul>
         * @return Element with min value
         */
        std::shared_ptr<T> min( int (*comparator)(std::shared_ptr<T>& lhs, std::shared_ptr<T>& rhs)) {
            auto min = m_array[0];

            for (size_t i = 1; i <= m_last_index; i++)
                if (comparator(min, m_array[i]) > 0)
                    min = m_array[i];

            return min;
        }

        /**
         * @param comparator Lambda function.
         * <ul>
         *  <li>Must return -1 if lhs \<  rhs</li>
         *  <li>Must return  0 if lhs == rhs</li>
         *  <li>Must return  1 if lhs >  rhs</li>
         * </ul>
         * @return Element with max value
         */
        std::shared_ptr<T> max( int (*comparator)(std::shared_ptr<T>& lhs, std::shared_ptr<T>& rhs)) {
            auto max = m_array[0];

            for (size_t i = 1; i < m_last_index; i++)
                if (comparator(max, m_array[i]) < 0)
                    max = m_array[i];

            return max;
        }

        /**
         * @return Element with min value
         */
        std::shared_ptr<T> min() {
            auto min = m_array[0];
            for (size_t i = 1; i <= m_last_index; i++)
                if (*min.get() > *m_array[i].get())
                    min = m_array[i];

            return min;
        }

        /**
         * @return Element with max value
         */
        std::shared_ptr<T> max() {
            auto max = m_array[0];

            for (size_t i = 1; i <= m_last_index; i++)
                if (*max.get() < *m_array[i].get())
                    max = m_array[i];

            return max;
        }
    };
}

/*
#undef INITIAL_SIZE
#undef GROW_SIZE
#undef SHRINK_UNTIL
#undef SHRINK_THRESHOLD
 */