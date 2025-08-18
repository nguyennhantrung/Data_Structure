#pragma once
#include <cstring>
namespace NNTStructure {
/*
    List base on static array
    - Rule of five
        - Copy constructor
        - Copy assignment
        - Destructor
        - Move constructor
        - Move assignment
*/
    template<typename T>
    class List {
    public: 
        List<T>(){
            _capacity = 1;
            _size = 0;
            _array = new T[_capacity]();
        }

        ~List() {
            delete[] _array;
        }

        // Copy constructor
        List<T>(const List<T>& other) {
            _capacity = other.capacity();
            _size = other.size();
            _array = new T[_capacity];
            // Even though _array is private, this works because both *this and other are List<T> objects, 
            // and class methods can access private members of any List<T> instance.
            memcpy(_array, other._array, _size * sizeof(T));
        }

        // copy assignment
        List<T>& operator=(const List<T>& other) {
            if (this == &other) return *this;  // handle self-assignment
            delete[] _array;                    // clear current array to apply new income

            _capacity = other.capacity();
            _size = other.size();
            _array = new T[_capacity];
            // Even though _array is private, this works because both *this and other are List<T> objects, 
            // and class methods can access private members of any List<T> instance.
            memcpy(_array, other._array, _size * sizeof(T));
            // "this" is a pointer, use *this to return a List<T> 
            return *this;
        }

        // Move constructor
        // If you don’t mark them noexcept, the compiler assumes they might throw, 
        // so containers will fall back to using the copy constructor instead.
        List<T>(List<T>&& other) noexcept {
            _capacity = other.capacity();
            _size = other.size();
            _array = new T[_capacity];
            // Even though _array is private, this works because both *this and other are List<T> objects, 
            // and class methods can access private members of any List<T> instance.
            memcpy(_array, other._array, _size * sizeof(T));
            other._capacity = 0;
            other._size = 0;
            other._array = nullptr;
        }

        // Move assignment
        // If you don’t mark them noexcept, the compiler assumes they might throw, 
        // so containers will fall back to using the copy constructor instead.
        List<T>& operator=(List<T>&& other) noexcept {
            if (this == &other) return *this;  // handle self-assignment
            delete[] _array;                    // clear current array to apply new income

            _capacity = other.capacity();
            _size = other.size();
            _array = new T[_capacity];
            // Even though _array is private, this works because both *this and other are List<T> objects, 
            // and class methods can access private members of any List<T> instance.
            memcpy(_array, other._array, _size * sizeof(T));
            other._capacity = 0;
            other._size = 0;
            other._array = nullptr;
            // "this" is a pointer, use *this to return a List<T> 
            return *this;
        }

        // Normally, operator[] returns a reference to allow modification:
        T& operator[](int index){
            if(index >= _size || index < 0)
                throw std::out_of_range("Index out of bounds");
                // return T();
            return _array[index];
        }

        // This operator is use whe create a const dynamic array, this const dynamic array is expected to not modify the element
        // the first const refers to const list<T> 
        // the second const means this function will not change any data of this class. Just use in reading data
        const T& operator[] (int index) const{
            if(index < 0 || index >= _size) 
                throw std::out_of_range("Index out of bounds");
            return _array[index];
        }

        T& get(int index) {
            if(index < 0 || index >= _size) 
                throw std::out_of_range("Index out of bounds");
            return _array[index];
        }

        void append(T value) {
            if(_size == _capacity) {
                _capacity = _capacity * 2;
                T *newArr = new T[_capacity]();
                memcpy(newArr, _array, _size * sizeof(T));
                // If T is not trivially copyable, memcpy is dangerous. Prefer:
                // std::copy(_array, _array + _size, newArr);
                if(_array != nullptr)
                    delete[] _array;
                _array = newArr;
            }
            _array[_size] = value;
            _size++;
        }

        void insert(T value, int index) {
            if(index < 0  || index > _size) 
                throw std::out_of_range("index out of bounds");
            if(_size == _capacity) {
                _capacity = _capacity * 2;
                T *newArr = new T[_capacity]();
                memcpy(newArr, _array, _size * sizeof(T));
                // If T is not trivially copyable, memcpy is dangerous. Prefer:
                // std::copy(_array, _array + _size, newArr);
                if(_array != nullptr)
                    delete[] _array;
                _array = newArr;
            }
            for(int i = _size; i > index; i-- ) {
                _array[i] = _array[i-1];
            }
            _array[index] = value;
            _size++;
        }

        void remove(T value) {
            for(int i = 0; i < _size; i++) {
                if(_array[i] == value) {
                    removeAt(i);
                    return;
                }
            }
        }

        void removeAt(int index) {
            if(index < 0  || index >= _size) 
                throw std::out_of_range("index out of bounds");
            for(int i = index; i < _size-1; i++) {
                _array[i] = _array[i+1];
            }
            _size--;
        }

        int search(T value) {
            for(int i = 0; i < _size; i++) {
                if(_array[i] == value) {
                    return i;
                }
            }
            return -1;
        }

        int size() const { return _size; }
        int capacity() const { return _capacity; }

    public: // Iterator
        struct iterator {
            // These using declarations are standard practice for C++ iterators
            using difference_type   = std::ptrdiff_t; // Required for random access iterators
            using iterator_category = std::random_access_iterator_tag; // Or forward_iterator_tag, etc.
            
            using value_type = T;
            using pointer    = T*;
            using reference  = T&;
            iterator(pointer iter) {
                _iterator = iter;
            }

            // Equality operators
            // This compare the position of element in array, not value
            // Equality Operators are written as non-member function. 
            // Therefore, need use friend to be able to access private and protected variable
            friend bool operator!=(const iterator a, const iterator b) {
                return a._iterator != b._iterator;
            }
            friend bool operator==(const iterator a, const iterator b) {
                return a._iterator == b._iterator;
            }

            // Dereference operator (required for all iterators)
            // Use "reference | T&" for direect change value.
            reference operator*() {
                return *_iterator;
            }

            // Member access operator (optional but good practice) 
            pointer operator->() {
                return _iterator;
            }

            // Prefix increment operator (++it)
            // Use iterator& to return changable value of iterator 
            iterator& operator++() {
                _iterator ++;   // increase address of pointer (T*)
                return *this;   // "this" is struct iterator*, "*this" will return value, not pointer.
            }

            // Postfix increment operator (it++)
            // The input parameter is a dummy  to differentiate it from the prefix version.
            iterator operator++(T) {
                iterator temp = *this;  // Store current value to temp variable
                ++(*this);              // Call the prefix increment operator to increase current value
                return temp;            // Return the temp variable
            }
            private: pointer _iterator;
        };
        
        iterator begin() {
            return iterator(&_array[0]);
        }
        iterator end() {
            return iterator(&_array[_size]);
        }

    private:
        T *_array = nullptr;
        int _size = 0;
        int _capacity = 0;
    };
}



