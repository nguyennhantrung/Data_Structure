#pragma once

template<typename T>
class UniquePtr {
    private:
        T* ptr = nullptr;
        public: // Rule of five
        UniquePtr() {
            ptr = nullptr;
        }
        /*
        Need explicit to dont let the compiler convert data type implicitly
        EX: void take_ownership(UniquePtr<int> ptr) {
            // ...
            }
            
            int* raw_ptr = new int(42);
            take_ownership(raw_ptr); // Lỗi! ptr sẽ bị tự động chuyển đổi.
        */
        explicit UniquePtr(T* t) {
            ptr = t;
        }
        UniquePtr(const UniquePtr& other) = delete;
        UniquePtr& operator=(const UniquePtr& other)  = delete;
        // this is unique_ptr = nullptr;
        UniquePtr& operator=(nullptr) {
            reset();
            return *this;
        }

        ~UniquePtr() {
            if(ptr != nullptr) {
                delete ptr;
                ptr = nullptr;
            }
        }
        UniquePtr(const UniquePtr&& other) noexcept {
            this->ptr = other->ptr;
            other->ptr = nullptr;
        }
        UniquePtr& operator=(const UniquePtr&& other) noexcept {
            this->ptr = other->ptr;
            other->ptr = nullptr;
            return *this
        }
    public: // Common
        T* release(){
            T* temp = ptr;
            ptr = nullptr;
            return temp;
        }
        void reset (T* newPtr = nullptr){
            if(ptr != nullptr)  
                delete ptr;
            ptr = newPtr;
        }
        void swap(){}
        T* get(){
            return ptr;
        }
    public: // Operator
        T& operator*() {
            return *ptr;
        }
        T* operator->() {
            return ptr;
        }

};


template<typename T>
class SharedPtr {
    private:
        T* ptr = nullptr;
        int* ref;

        void cleanup() {
            if(ref) {
                (*ref)--;
                if(*ref == 0) {
                    if(ptr) {
                        delete ptr;
                        ptr = nullptr;
                    }
                    delete ref;
                    ref = nullptr;
                }
            }
        }
    public:
        SharedPtr() {
            ptr = nullptr;
            ref = nullptr;
        }
        SharedPtr(const T* other){
            ptr = other;
            if(other)
                ref = new int(1);
            else
                ref = nullptr;
        }
        SharedPtr(const SharedPtr& other) {
            ptr = other.ptr;
            ref = other.ref;
            if(ref)
                ++(*ref);
        }
        SharedPtr(const SharedPtr&& other) {
            ptr = other.ptr;
            ref = other.ref;
            other.ptr = nullptr;
            other.ref = nullptr;
        }
        ~SharedPtr() {
            cleanup();
        }
    public: 
        SharedPtr& operator=(const SharedPtr& other) {
            if(this != &other){
                cleanup();
                ptr = other.ptr;
                ref = other.ref;
                if(ref)
                    ++(*ref);
            }
            return *this;
        }
        SharedPtr& operator=(const SharedPtr&& other) {
            if(this != &other){
                cleanup();
                ptr = other.ptr;
                ref = other.ref;
                other.ptr = nullptr;
                other.ref = nullptr;
            }
            return *this;
        }
        SharedPtr& operator=(nullptr) {
            cleanup();
            ptr = nullptr;
            ref = nullptr;
            return *this;
        }
    public:
        void reset (T* newPtr = nullptr) {
            cleanup();
            ptr = newPtr;
            if(ptr) 
                ref = new int(1);
            else
                ref = nullptr;
        }
        T& operator*(){
            return *ptr;
        }
        T* operator->() {
            return ptr;
        }
        T* get() const {
            return ptr;
        }
        int use_count() {
            if(ref) 
                return *ref;
            return 0;
        }
};