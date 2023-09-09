#include <stdexcept>
#include <format>

class DynamicArray {
private:
    static const size_t INITIAL_SIZE = 5;
    static const size_t GROW_SIZE = 5;
    static const size_t SHRINK_SIZE = 5;
    static const size_t SHRINK_THRESHOLD = 5;
    
    size_t size;
    short* array;

    size_t index;

    void _grow(size_t growBy) {
        size += growBy;
        short* oldArray = array;
        short* newArray = new short[size];

        __copy(oldArray, newArray);
        __delete(oldArray);

        array = newArray;
    }

    void _shrink() {
        
    }

    void __copy(short* oldArray, short* newArray) {
        for (size_t i = 0; i < size; i++)
            newArray[i] = oldArray[i];
    }

    void __delete(short* array) {
        delete [] array;
    }

public:
    DynamicArray(size_t size = INITIAL_SIZE) {
        this->size = INITIAL_SIZE;
        index = 0;
        array = new short[size];
    }

    ~DynamicArray() {
        delete[] array;
    }

    short* get(size_t index) const {
        if (index > size - 1)
            throw std::out_of_range("Index '" + index + "' is out of bounds! Array size: " + size);

        return &array[index];
    }

    void pushBack(short object) {
        if (size - 1 == index)
            _grow(GROW_SIZE);

        array[++index] = object;
    }

    void popBack() {

    }

    size_t getSize() const {
        return this->size; 
    }
};