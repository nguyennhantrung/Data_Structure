#pragma once

namespace NNTStructure {
    template<typename T>
    class Stack {
    public:
        Stack() {}
        ~Stack() {}
        Stack(const Stack& other) {}
        Stack& operator=(const Stack& other){
            return *this;
        }
        Stack(const Stack&& other) {}
        Stack& operator=(const Stack&& other){
            return *this;
        }
    public:
        int size() { return _size; }
        void push() {}
        void pop() {}
    protected:
        struct LinkedList {
            T _value;
            LinkedList* _next;
            LinkedList* _prev;
        }
    public:
        struct iterator {
            iterator() {}
            iterator(const LinkedList& ll) {}

        private:
            LinkedList* node = nullptr;
        }
    private:
        int _size = 0;
    };

};