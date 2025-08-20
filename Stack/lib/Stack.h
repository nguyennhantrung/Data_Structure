#pragma once

/*
    head -> node -> node -> tail
    push to head
    pop from head
    head = nullptr, tail = nullptr
    push => head = 1, tail = 1;
    push => head = 2, head next = 1;
    pop => head = head-> next;

*/


namespace NNTStructure {
    template<typename T>
    class Stack {
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
                    node = node->prev;
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
        Stack() {
            head = nullptr;
            _size = 0;
        }
        ~Stack() {
            while(head != nullptr) {
                LinkedList* temp = head;
                head = head->next;
                delete temp; temp = nullptr;
            }
            _size = 0;
        }
        Stack(const Stack& other) {
            LinkedList* currOther = other.head;
            LinkedList* curr = nullptr;
            head = nullptr;
            while(currOther != nullptr) {
                // need logic here
                if(head == nullptr)  {
                    curr = new LinkedList(currOther->_value);
                    head = curr;
                }
                else {
                    curr->next = new LinkedList(currOther->_value, curr->next, curr);
                    curr = curr->next;
                }
                currOther = currOther->next;
            }
            _size = other._size;
        }
        Stack& operator=(const Stack& other){
            while(head != nullptr)  {
                LinkedList* temp = head;
                head = head->next;
                delete temp;
                temp = nullptr;
            }

            LinkedList* currOther = other.head;
            LinkedList* curr = nullptr;
            head = nullptr;
            while(currOther != nullptr) {
                // need logic here
                if(head == nullptr)  {
                    curr = new LinkedList(currOther->_value);
                    head = curr;
                }
                else {
                    curr->next = new LinkedList(currOther->_value, curr->next, curr);
                    curr = curr->next;
                }
                currOther = currOther->next;
            }
            _size = other._size;

            return *this;
        }
        Stack(Stack&& other) noexcept {
            head = other.head;
            other.head = nullptr; 
            _size = other._size;
        }
        Stack& operator=(Stack&& other) noexcept {
            while(head != nullptr)  {
                LinkedList* temp = head;
                head = head->next;
                delete temp;
                temp = nullptr;
            }

            head = other.head;
            other.head = nullptr;
            return *this;
        }
    public:
        int size() { return _size; }
        void push(const T& value) {
            if(head == nullptr) {
                head = new LinkedList(value);
            }
            else {
                head = new LinkedList(value, head);
                head->next->prev = head;
            }
            ++_size;
        }
        T pop() {
            if(head == nullptr) {
                throw std::out_of_range("out of range");
            }
            T value = head->_value;
            LinkedList* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
            temp = nullptr;
            _size = _size - 1;
            return value;
        }
        void insert (const T& value, int index) {
            if(index > _size) {
                throw std::out_of_range("out of range");
            }
            if(index == 0) {
                push(value);
            }
            else {
                LinkedList* temp = head;
                while(index-- != 1) {
                    temp = temp ->next;
                }
                temp->next = new LinkedList(value, temp->next, temp);
                if(temp->next->next != nullptr)
                    temp->next->next->prev = temp->next;
                _size = _size + 1;
            }
        }
        iterator begin() { 
            LinkedList* temp = head;
            while(temp->next != nullptr) {
                temp = temp->next;
            }
            return iterator(temp); 
        }
        iterator end() { return iterator(nullptr); }
    private:
        LinkedList* head = nullptr;
        int _size = 0;
    };

};