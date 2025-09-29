# **Week 1 Mini Project: Embedded Resource Wrapper (ERW)**

**Goal:** Create a clean, modern C++ framework that safely models interaction with simulated low-level hardware registers and synchronization primitives, ensuring resource safety using RAII.

**Duration:** 3-5 days of focused coding and testing.

## **Phase 1: Simulated Hardware Interface (ARM/Embedded Focus)**

This phase simulates volatile memory access and basic hardware synchronization registers.

### **1.1 The Register Class**

Create a template or class to model a 32-bit peripheral register.

* **Implementation:**  
  * Create a class HardwareRegister\<T\> where T is the register type (e.g., uint32\_t).  
  * The underlying storage should be declared volatile to simulate memory-mapped I/O (MMIO).  
  * Overload the assignment operator (=) to simulate a write.  
  * Overload the cast operator or provide a read() function to simulate a read.

// Pseudocode for Hardware Register Class  
template\<typename T\>  
class HardwareRegister {  
private:  
    volatile T data; // The volatile keyword is critical here.  
public:  
    // Write: Simulates register write  
    void operator=(T val) volatile { data \= val; }

    // Read: Simulates register read  
    T read() const volatile { return data; }  
      
    // Demonstrate bitwise access  
    void set\_bit(int bit) volatile { data |= (1 \<\< bit); }  
};

### **1.2 The Peripheral Lock**

Simulate a system-level resource that requires a lock before access (like a shared communication bus or a memory controller).

* **Implementation:**  
  * Create a simple function acquire\_peripheral\_lock(int peripheral\_id) that returns a simulated "handle" (e.g., a simple integer ID) and prints "Lock Acquired".  
  * Create a simple function release\_peripheral\_lock(int handle) that prints "Lock Released".

## **Phase 2: C++ RAII and Smart Pointers Integration (C++ Focus)**

This phase uses smart pointers and custom deleters to implement the RAII principle for the simulated lock.

### **2.1 Custom Deleter for Lock**

* **Implementation:**  
  * Define a struct or class PeripheralDeleter (the custom deleter).  
  * It must have an overloaded function call operator operator() that accepts the lock handle and calls the release\_peripheral\_lock() function from Phase 1\.

### **2.2 The RAII Wrapper**

* **Implementation:**  
  * Create a function get\_locked\_peripheral(int peripheral\_id) that returns a std::unique\_ptr\<int, PeripheralDeleter\>.  
  * This function must call acquire\_peripheral\_lock() and package the resulting handle ID into the unique\_ptr.  
* **Verification:** Verify that when the std::unique\_ptr goes out of scope (e.g., at the end of a function), the custom deleter is automatically called, and "Lock Released" is printed—even if an exception occurs (simulated with throw).

## **Phase 3: DSA Application and System Context**

This phase integrates DSA concepts with the embedded context.

### **3.1 Device Management Array**

* **Implementation:**  
  * Use std::vector\<HardwareRegister\<uint32\_t\>\> to simulate a dynamically managed list of peripheral status registers.  
  * Write a function initialize\_devices(int count) that populates the vector.  
  * Write a function check\_device\_status(const std::vector\<...\>& regs) that iterates over the vector using a range-based for loop (C++ style) and reads the volatile register value, applying the concepts of **Dynamic Arrays** and **Amortized Constant Time** for expansion (though not actively testing expansion, you should be able to discuss the concept).

## **Knowledge Mapping Summary**

| Project Feature | Week 1 Topic Covered | Interview Relevance |
| :---- | :---- | :---- |
| volatile keyword in HardwareRegister | ARM: Memory-mapped I/O (MMIO), memory model intuition. | Demonstrates understanding of compiler optimizations and direct hardware interaction. |
| std::unique\_ptr with PeripheralDeleter | C++: RAII, Smart Pointers, Custom Deleters. | Essential for robust embedded code where resources must never leak (e.g., hardware locks, RTOS semaphores). |
| acquire\_peripheral\_lock / release\_peripheral\_lock | ARM: Exception Handling, Processor Modes (simulated resource access). | Allows discussion of critical sections, IRQ disabling, and synchronization primitives. |
| Use of std::vector and iteration | DSA: Dynamic Arrays, Amortized Complexity. | Shows ability to use standard library containers efficiently and safely. |

This mini-project is small enough to complete quickly but deep enough to require mastering the core Week 1 concepts simultaneously.