#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T>
class UniqueSet {
private:
    T* elements;
    int size;
    int capacity;

public:

    UniqueSet() : elements(nullptr), size(0), capacity(0) {}


    UniqueSet(const T* values, int count) : elements(nullptr), size(0), capacity(0) {
        for (int i = 0; i < count; ++i) {
            insert(values[i]);
        }
    }


    UniqueSet(int count, T min_val, T max_val) : elements(nullptr), size(0), capacity(0) {
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < count; ++i) {
            T value = min_val + static_cast<T>(rand()) % (max_val - min_val + 1);
            insert(value);
        }
    }


    UniqueSet(const UniqueSet<T>& other) : elements(nullptr), size(0), capacity(0) {
        for (int i = 0; i < other.size; ++i) {
            insert(other.elements[i]);
        }
    }


    UniqueSet<T>& operator=(const UniqueSet<T>& other) {
        if (this != &other) {
            clear();
            for (int i = 0; i < other.size; ++i) {
                insert(other.elements[i]);
            }
        }
        return *this;
    }


    ~UniqueSet() {
        clear();
    }

    
    T operator[](int index) const {
        if (index >= 0 && index < size) {
            return elements[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    
    UniqueSet<T> operator+(const UniqueSet<T>& other) const {
        UniqueSet<T> result = *this;
        for (int i = 0; i < other.size; ++i) {
            result.insert(other.elements[i]);
        }
        return result;
    }

    
    UniqueSet<T> operator-(const UniqueSet<T>& other) const {
        UniqueSet<T> result = *this;
        for (int i = 0; i < other.size; ++i) {
            result.remove(other.elements[i]);
        }
        return result;
    }

    
    UniqueSet<T> operator+(const T& value) const {
        UniqueSet<T> result = *this;
        result.insert(value);
        return result;
    }

    
    UniqueSet<T> operator-(const T& value) const {
        UniqueSet<T> result = *this;
        result.remove(value);
        return result;
    }
}