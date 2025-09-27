#pragma once

template<typename T>
class SimpleLRU {
    private:
        SimpleLRU(){}
        SimpleLRU(const SimpleLRU&) {}
        SimpleLRU& operator=(const SimpleLRU&) {return *this;}

        int numLRU = 5;
        
        struct node {
            int _key;
            T _value;
            node* _next;
            node* _prev;
            node(int key, T val, node* next = nullptr, node* prev = nullptr): _key(key), _value(val), _next(next), _prev(prev){}
            node(): _next(nullptr), _prev(nullptr){}
        };
        
        node* head = nullptr;
        node* tail = nullptr;
        int size = 0;

    public:
        static SimpleLRU& GetInstance() {
            static SimpleLRU simpleLRU;
            return simpleLRU;
        }
        void setNumLRD(const int& num ) {
            numLRU = num;
        }
        int getNumLRD() const {
            return numLRU;
        }

        node* searchNode(const T key)  {
            node* temp = head;
            while(temp != nullptr) {
                if(temp->_key == key) {
                    break;
                }
                temp = temp->_next;
            }
            return temp;
        }

        void getAPI(const int key) {
            // Check the LRU and return T if available, else 
            node* nodeValue = searchNode(key);
            if(nodeValue != nullptr) {
                if(nodeValue == head)   return;
                if(nodeValue == tail) tail = nodeValue->_prev;
                // Convert connection
                node* temp = nodeValue->_prev;
                temp->_next = nodeValue->_next;
                temp = nodeValue->_next;
                temp->_prev = nodeValue->_prev;
                
                head->_prev = nodeValue;
                nodeValue->_next = head;
                nodeValue->_prev = nullptr;
                head = nodeValue;
                std::cout << "Found key: " << key << std::endl;
            }
            else {
                std::cout << "Not found key: " << key << std::endl;
            }
        }

        void putAPI(const int key, const T& value) {
            // insert the value
            node* nodeValue = searchNode(key);
            if(nodeValue != nullptr) {
                if(nodeValue == head)   return;
                if(nodeValue == tail) tail = nodeValue->_prev;
                // Convert connection
                node* temp = nodeValue->_prev;
                temp->_next = nodeValue->_next;
                temp = nodeValue->_next;
                temp->_prev = nodeValue->_prev;
                
                head->_prev = nodeValue;
                nodeValue->_next = head;
                nodeValue->_prev = nullptr;
                head = nodeValue;

                head->_value = value;
            }
            else {
                head = new node(key, value, head);
                head->_next->_prev = head;
                ++size;
                while(size > numLRU) {
                    nodeValue = tail;
                    tail = tail->_prev;
                    tail->_next = nullptr;
                    delete nodeValue;
                    nodeValue = nullptr;
                    --size;
                }
            }
        }



};