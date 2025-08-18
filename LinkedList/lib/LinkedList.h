#pragma once

namespace NNTStructure {
    template<typename T>
    class LinkedList {
        public:
            LinkedList<T>() {
                next = nullptr;
            }

            LinkedList<T>(const T& other) {
                value = other.value;
                next = other.next;
            }
            LinkedList<T>(T&& other) noexcept {
                value = other.value;
                next = other.next;
                other.next = nullptr;
            }
            ~LinkedList(){
                
            }
            T& operator=(const T& other){
                value = other.value;
                next = other.next;
                return *this;
            }
            T& operator=(T&& other) noexcept {
                value = other.value;
                next = other.next;
                other.next = nullptr;
                return *this;
            }
            void insert(T value) {
                
            }

        private:
            T value;
            LinkedList<T>* next;
    };
}