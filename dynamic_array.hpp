//
// Created by Divium on 08/09/2023.
//

#include <stdexcept>
#include <memory>
#include <format>

namespace dvm {
    /**
        * @brief Dynamic array implementation using smart pointers
    */
    template<class T> class DynamicArray {
    private:
        static const size_t INITIAL_SIZE = 5;
        static const size_t GROW_SIZE = 5;
        static const size_t SHRINK_SIZE = 5;
        static const size_t SHRINK_THRESHOLD = 5;

        size_t m_last_index;
        size_t m_size;
        std::unique_ptr<std::shared_ptr<T>[]> m_array;

        /**
         * Grows array
         * @param grow_by How much to grow
         */
        void _grow(size_t grow_by) {
            m_size += grow_by;
            auto old_array = std::move(m_array);
            auto new_array = _create_array(m_size);

            _copy(old_array, new_array);

            m_array = std::move(new_array);
        }


        void _shrink() {

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
            for (size_t i = 0; i < m_size; i++)
                new_array[i] = old_array[i];
        }

        [[deprecated]] void _delete(T *array) {
            delete[] array;
        }

    public:
        /**
         * @param size Initial size of the array (Default = 5)
         */
        explicit DynamicArray(size_t size = INITIAL_SIZE) {
            m_size = size;
            m_last_index = 0;
            m_array = _create_array(m_size);
        }

        /**
         * Returns shared pointer of requested element
         * @param index Element location
         * @returns Shared pointer of requested element
         * @throws std::out_of_range When index is out of range
         */
        std::shared_ptr<T> get(size_t index) const {
            if (index > m_last_index)
                throw std::out_of_range(std::format("Index {} is out of bounds! Current array size is {}", index, m_last_index));

            return m_array[index];
        }

        /**
         * Appends element at the end
         * @param object Element to add
         */
        void push_back(std::shared_ptr<T> object) {
            if (m_size - 1 >= m_last_index)
                _grow(GROW_SIZE);

            m_array[++m_last_index] = object;
        }

        /**
         * Removes last element
         */
        void pop_back() {
            m_array[m_last_index] = nullptr;
            m_last_index--;
        }

        /**
         * @return Array size
         */
        [[nodiscard]] size_t size() const noexcept {
            return m_last_index;
        }
    };
}