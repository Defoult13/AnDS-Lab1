#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>

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

    
    UniqueSet<T> intersection(const UniqueSet<T>& other) const {
        UniqueSet<T> result;
        for (int i = 0; i < size; ++i) {
            if (other.contains(elements[i])) {
                result.insert(elements[i]);
            }
        }
        return result;
    }

    // Перегрузка операторов для std::string
    UniqueSet<std::string> operator+(const UniqueSet<std::string>& other) const {
        UniqueSet<std::string> result = *this;
        for (int i = 0; i < other.size; ++i) {
            result.insert(other.elements[i]);
        }
        return result;
    }

    UniqueSet<std::string> operator-(const UniqueSet<std::string>& other) const {
        UniqueSet<std::string> result = *this;
        for (int i = 0; i < other.size; ++i) {
            result.remove(other.elements[i]);
        }
        return result;
    }

    UniqueSet<std::string> operator+(const std::string& value) const {
        UniqueSet<std::string> result = *this;
        result.insert(value);
        return result;
    }

    UniqueSet<std::string> operator-(const std::string& value) const {
        UniqueSet<std::string> result = *this;
        result.remove(value);
        return result;
    }

    // Перегрузка операторов для std::pair<int, double>
    UniqueSet<std::pair<int, double>> operator+(const UniqueSet<std::pair<int, double>>& other) const {
        UniqueSet<std::pair<int, double>> result = *this;
        for (int i = 0; i < other.size; ++i) {
            result.insert(other.elements[i]);
        }
        return result;
    }

    UniqueSet<std::pair<int, double>> operator-(const UniqueSet<std::pair<int, double>>& other) const {
        UniqueSet<std::pair<int, double>> result = *this;
        for (int i = 0; i < other.size; ++i) {
            result.remove(other.elements[i]);
        }
        return result;
    }

    UniqueSet<std::pair<int, double>> operator+(const std::pair<int, double>& value) const {
        UniqueSet<std::pair<int, double>> result = *this;
        result.insert(value);
        return result;
    }

    UniqueSet<std::pair<int, double>> operator-(const std::pair<int, double>& value) const {
        UniqueSet<std::pair<int, double>> result = *this;
        result.remove(value);
        return result;
    }

   
    bool contains(const T& value) const {
        for (int i = 0; i < size; ++i) {
            if (elements[i] == value) {
                return true;
            }
        }
        return false;
    }

    
    void insert(const T& value) {
        if (!contains(value)) {
            if (size == capacity) {
                resize();
            }
            elements[size++] = value;
        }
    }

   
    void remove(const T& value) {
        for (int i = 0; i < size; ++i) {
            if (elements[i] == value) {
                for (int j = i; j < size - 1; ++j) {
                    elements[j] = elements[j + 1];
                }
                --size;
                return;
            }
        }
    }

    
    void resize() {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newElements = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }

    
    void display() const {
        for (int i = 0; i < size; ++i) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }

    
    bool isSubsetOf(const UniqueSet<T>& other) const {
        for (int i = 0; i < size; ++i) {
            if (!other.contains(elements[i])) {
                return false;
            }
        }
        return true;
    }

    
    bool isSupersetOf(const UniqueSet<T>& other) const {
        for (int i = 0; i < other.size; ++i) {
            if (!contains(other.elements[i])) {
                return false;
            }
        }
        return true;
    }

    
    void clear() {
        delete[] elements;
        elements = nullptr;
        size = 0;
        capacity = 0;
    }

};

int main() {
    int intValues1[] = { 1, 2, 3, 4, 5 };
    int intValues2[] = { 3, 4, 5, 6, 7 };

    UniqueSet<int> intSet1(intValues1, sizeof(intValues1) / sizeof(intValues1[0]));
    UniqueSet<int> intSet2(intValues2, sizeof(intValues2) / sizeof(intValues2[0]));

    std::cout << "intSet1: ";
    intSet1.display();
    std::cout << "intSet2: ";
    intSet2.display();

    UniqueSet<int> unionSet = intSet1 + intSet2;
    std::cout << "Union: ";
    unionSet.display();

    // Создание и операции для строк
    std::string strValues1[] = { "apple", "banana", "cherry" };
    std::string strValues2[] = { "banana", "date", "fig" };

    UniqueSet<std::string> strSet1(strValues1, sizeof(strValues1) / sizeof(strValues1[0]));
    UniqueSet<std::string> strSet2(strValues2, sizeof(strValues2) / sizeof(strValues2[0]));

    std::cout << "strSet1: ";
    strSet1.display();
    std::cout << "strSet2: ";
    strSet2.display();

    UniqueSet<std::string> strUnionSet = strSet1 + strSet2;
    std::cout << "String Union: ";
    strUnionSet.display();

    // Создание и операции для пар (std::pair<int, double>)
    std::pair<int, double> pairValues1[] = { std::make_pair(1, 1.1), std::make_pair(2, 2.2) };
    std::pair<int, double> pairValues2[] = { std::make_pair(2, 2.2), std::make_pair(3, 3.3) };

    UniqueSet<std::pair<int, double>> pairSet1(pairValues1, sizeof(pairValues1) / sizeof(pairValues1[0]));
    UniqueSet<std::pair<int, double>> pairSet2(pairValues2, sizeof(pairValues2) / sizeof(pairValues2[0]));

    std::cout << "pairSet1: ";
    pairSet1.display();
    std::cout << "pairSet2: ";
    pairSet2.display();

    UniqueSet<std::pair<int, double>> pairUnionSet = pairSet1 + pairSet2;
    std::cout << "Pair Union: ";
    pairUnionSet.display();

    return 0;
}