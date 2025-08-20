#pragma once
#include <cstring>

namespace NNTStructure {
    template<typename T>
    class SingleLinkedList {
        public: // Structure
            struct linkedlist {
                linkedlist() {
                    _next = nullptr;
                }
                linkedlist(const T& value) {
                    memcpy(&_value, &value, sizeof(T));
                    _next = nullptr;
                }
                linkedlist(const T& value, linkedlist *next) {
                    memcpy(&_value, &value, sizeof(T));
                    _next = next;
                }
                T& get() {
                    return _value;
                }
                linkedlist *& next() {
                    return _next;
                }
                protected:
                T _value;
                linkedlist *_next;
            };
            
            struct iterator {
                iterator() {
                    node = nullptr;
                }
                iterator(linkedlist* other) {
                    node = other;
                }
                iterator& operator++() {
                    if(node == nullptr) 
                        throw std::out_of_range("nullptr");
                    node = node->next();
                    return *this;
                }
                iterator operator++(T) {
                    iterator temp = *this;
                    ++(*this);
                    return temp;
                }
                T& operator*() {
                    return node->get();
                }
                T* operator->() {
                    return &(node->get());
                }
                friend bool operator==(const iterator& A, const iterator& B) {
                    return A.node == B.node;
                }
                friend bool operator!=(const iterator& A, const iterator& B) {
                    return A.node != B.node;
                }

                private:
                linkedlist* node = nullptr;
            };

        public: // Common Functions
            SingleLinkedList<T>() {
                head = nullptr;
                tail = nullptr;
                _size = 0;
            }
            SingleLinkedList<T>(const SingleLinkedList<T>& other) {
                linkedlist * otherNode = other.head;
                while(otherNode != nullptr) {
                    append(otherNode->get());
                    otherNode = otherNode->next();   
                }
                _size = other._size;
            }
            SingleLinkedList<T>(T&& other) noexcept {
                head = other.head;
                tail = other.tail;
                _size = other.size;
                other.head = nullptr;
                other.tail = nullptr;
                other._size = 0;
            }
            ~SingleLinkedList(){
                linkedlist* temp;
                while(head != nullptr) {
                    temp = head;
                    head = head->next();
                    delete temp;
                }
                tail = nullptr;
                _size = 0;
            }
            SingleLinkedList<T>& operator=(const SingleLinkedList<T>& other){
                // Clean up
                linkedlist* temp;
                while(head != nullptr) {
                    temp = head;
                    head = head->next();
                    delete temp;
                    temp = nullptr;
                }
                head = nullptr;
                tail = nullptr;
                // Create copy list
                linkedlist * otherNode = other.head;
                while(otherNode != nullptr) {
                    append(otherNode->get());
                    otherNode = otherNode->next();   
                }
                _size = other._size;
                return *this;
            }
            SingleLinkedList<T>& operator=(T&& other) noexcept {
                head = other.head;
                tail = other.tail;
                _size = other.size;
                other.head = nullptr;
                other.tail = nullptr;
                other._size = 0;
                return *this;
            }
        public:
            int size() const { return _size; }
            T& operator[] (int index) const {
                if(index >= _size) {
                    throw std::out_of_range("index out of bounds");
                }

                int i = 0;
                linkedlist* curr = head;
                while(i < index) {
                    curr = curr->next();
                    i++;
                }
                return curr->get();
            }
            void append(const T& value) {
                if(head == nullptr) {
                    head = new linkedlist(value);
                    tail = head;
                    head->next() = nullptr;
                }
                else {
                    tail->next() = new linkedlist(value);
                    tail = tail->next();
                    tail->next() = nullptr;
                }
                _size = _size + 1;
            }
            void insert(const T& value, int index) {
                if(index > _size) {
                    throw std::out_of_range("index out of bounds");
                }
                if(index == 0) {
                    head = new linkedlist(value, head);
                }
                else if(index == _size) {
                    tail->next() = new linkedlist(value);
                    tail = tail->next();
                }
                else {
                    int i = 0;
                    linkedlist* curr = head;
                    while(i < index-1) {
                        curr = curr->next();
                        i++;
                    }
                    curr->next() = new linkedlist(value, curr->next());
                }
                _size = _size + 1;
            }
            void remove(const T& value) {
                linkedlist* curr = head;
                for(int i = 0; i < _size; i++) {
                    if(curr->get() == value) {
                        removeAt(i);
                        return;
                    }
                }
            }
            void removeAt(int index) {
                if(index >= _size) {
                    throw std::out_of_range("index out of bounds");
                }
                if(index == 0) {
                    if(head == tail) {
                        delete head;
                        tail = nullptr;
                        head = nullptr;
                    }
                    else {
                        linkedlist* curr = head;
                        head = head->next();
                        delete curr;
                        curr = nullptr;
                    }
                }
                else {
                    int i = 0;
                    linkedlist* curr = head;
                    while(i < index-1) {
                        curr = curr->next();
                        i++;
                    }
                    if(curr->next() == tail) {
                        tail = curr;
                        delete curr->next();
                        curr->next() = nullptr;
                    }
                    else
                    {
                        linkedlist* temp = curr->next();
                        curr->next() = curr->next()->next();
                        delete temp;
                        temp = nullptr;
                    }
                }
                _size = _size - 1;
            }
            iterator begin() {
                return iterator(head);
            }
            iterator end() {
                return iterator();
            }
        private:
            linkedlist* head = nullptr;
            linkedlist* tail = nullptr;
            int _size = 0;
    };
};



