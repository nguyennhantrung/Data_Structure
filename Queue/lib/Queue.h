#pragma once

/*
    head -> node -> node -> tail
    push to head
    pop from head
    head = nullptr, tail = nullptr
    push => head = 1, tail = 1;
    push => head = 1, tail = 2;
    pop => head = 1, tail 1;

*/

namespace NNTStructure {
    template<typename T>
    class Queue {
    public:
        struct LinkedList {
            LinkedList() {
                next == nullptr;
                prev = nullptr;
            }
            LinkedList(const T& value, LinkedList* _next = nullptr, LinkedList* _prev = nullptr) {
                _value = value;
                next = _next;
                prev = _prev;
            }
            T _value;
            LinkedList* next = nullptr;
            LinkedList* prev = nullptr;
        };
    public:
        struct iterator {
            iterator() {
                node = nullptr;
            }
            iterator(LinkedList* ll) {
                node = ll;
            }
            T& operator*() { return node->_value; }
            T* operator->() { return &(node->_value); }
            iterator& operator++() {
                if (node != nullptr)
                    node = node->next;
                else 
                    throw std::out_of_range("out of range");
                return *this;
            }
            iterator operator++(T) {
                iterator temp = *this;
                ++(*this);
                return temp;
            }
            friend bool operator==(const iterator& A, const iterator& B) {
                return A.node == B.node;
            }
            friend bool operator!=(const iterator& A, const iterator& B) {
                return A.node != B.node;
            }
            private:
            LinkedList* node = nullptr;
        };
    public:
        Queue() {
            head = nullptr;
            tail = nullptr;
            _size = 0;
        }
        Queue(const Queue& other) {
            LinkedList* currOther = other.head;
            while(currOther != nullptr) {
                enqueue(currOther->_value);
                currOther = currOther->next;
            }
            _size = other._size;
        }
        ~Queue() {
            while(head != nullptr) {
                LinkedList* temp = head;
                head = head->next;
                delete temp;
                temp = nullptr;
            }
            tail = nullptr;
            _size = 0;
        }
        Queue& operator=(const Queue& other) {
            while(head != nullptr) {
                LinkedList* temp = head;
                head = head->next;
                delete temp;
                temp = nullptr;
            }
            tail = nullptr;

            LinkedList* currOther = other.head;
            while(currOther != nullptr) {
                enqueue(currOther->_value);
                currOther = currOther->next;
            }
            _size = other._size;
            return *this;
        }
        Queue(Queue&& other) noexcept {
            head = other.head;
            tail = other.tail;
            other.head = nullptr;
            other.tail = nullptr;
            _size = other._size;
            other._size = 0;
        }
        Queue& operator=(Queue&& other) noexcept {
            while(head != nullptr) {
                LinkedList* temp = head;
                head = head->next;
                delete temp;
                temp = nullptr;
            }

            head = other.head;
            tail = other.tail;
            other.head = nullptr;
            other.tail = nullptr;
            _size = other._size;
            other._size = 0;
            return *this;
        }

        int size() { return _size; }
        void enqueue (const T& value) {
            if(head == nullptr) {
                head = new LinkedList(value);
                tail = head;
            }
            else {
                tail->next = new LinkedList(value, tail->next, tail);
                tail = tail->next;
            }
            ++_size;
        }
        T dequeue () {
            T value = tail->_value;
            if(head == tail) {
                delete head;
                head = nullptr;
                tail = nullptr;
            }
            else {
                LinkedList* temp = tail;
                tail = tail->prev;
                delete temp; temp = nullptr;
                tail->next = nullptr;
            }
            --_size;
            return value;
        }

        iterator begin() { 
            return iterator(head); 
        }
        iterator end() { return iterator(nullptr); }
    private:
        LinkedList* head = nullptr;
        LinkedList* tail = nullptr;
        int _size = 0;
    };
}