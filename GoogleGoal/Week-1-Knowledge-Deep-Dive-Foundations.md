# **Week 1 Knowledge Deep Dive: Foundations**

This document outlines the specific concepts to master for your first week, covering ARM architecture fundamentals, core C++ features, and foundational data structures/algorithms.

## **1\. Focus Area: ARM Architecture Fundamentals**

**Goal:** Understand the processor's state, modes of operation, and basic instruction execution.

### **1.1 AArch32 vs. AArch64 (ARMv7 vs. ARMv8)**

| Feature | AArch32 (32-bit) | AArch64 (64-bit) | Key Interview Point |
| :---- | :---- | :---- | :---- |
| **Registers** | R0-R12, SP (R13), LR (R14), PC (R15). | X0-X30 (64-bit), W0-W30 (32-bit aliases), SP, PC. | Justify a design choice between 32-bit and 64-bit (e.g., memory addressability vs. code size/power consumption). |
| **Instruction Set** | ARM (32-bit) and Thumb (16/32-bit variable). | A64 (fixed 32-bit length). | How does the fixed instruction size of A64 simplify the pipeline compared to Thumb? |

### **1.2 Register Sets and Special Registers**

* **General Purpose Registers (GPRs):** Understand how registers are used for function arguments, local variables, and return values (e.g., the standard calling convention like AAPCS).  
* **Program Counter (PC):** Holds the address of the next instruction.  
* **Stack Pointer (SP):** Pointer to the top of the current stack.  
* **CPSR (Current Program Status Register) / PSTATE:**  
  * **Condition Flags (N, Z, C, V):** Negative, Zero, Carry, Overflow. Know how these are set by arithmetic/logic operations and used for conditional execution.  
  * **Mode Bits:** Determine the current processor privilege level.

### **1.3 Processor Modes and Exception Handling**

* **User Mode:** Least privileged, where application code runs.  
* **Supervisor (SVC) Mode:** Entered when a syscall or system request is made.  
* **IRQ/FIQ Modes:** Entered upon hardware interrupts. Know the difference (FIQ is for high-speed, low-latency interrupts).  
* **Abort/Undefined Modes:** For handling memory access violations or unknown instructions.  
* **Key Concept: The Vector Table:** Where the CPU jumps to when an exception occurs (e.g., reset, IRQ, data abort).

## **2\. Focus Area: C++ & Data Structures (DSA)**

**Goal:** Solidify Big O analysis, master fundamental data structures, and demonstrate a deep understanding of modern C++ memory management (C++11/14).

### **2.1 C++ Modern Memory Management (C++11/14)**

* **RAII (Resource Acquisition Is Initialization):** The fundamental C++ principle for managing resources (memory, file handles, locks). Be prepared to explain it and provide examples.  
* **Smart Pointers:**  
  * std::unique\_ptr: Sole ownership. Use when ownership must not be shared. **Interview Focus:** Implementing a custom deleter for hardware resources (e.g., releasing a peripheral lock).  
  * std::shared\_ptr: Shared ownership using reference counting. **Interview Focus:** Discussing the performance overhead of reference counting and how to avoid cycles (using std::weak\_ptr).  
* **Custom Deleters:** Why are they necessary for embedded programming, where a "resource" might be an allocated hardware handle or an RTOS semaphore, not just heap memory?

### **2.2 Data Structure & Algorithm (DSA) Foundations**

* **Big O Notation:** Master time and space complexity analysis. Be able to derive the complexity of nested loops, recursive calls, and common data structure operations (e.g., insertion in a dynamic array vs. a linked list).  
* **Dynamic Arrays (std::vector):**  
  * Implementation details: capacity vs. size. Amortized constant time insertion.  
  * Discuss the performance penalty of reallocations and how reserve() helps.  
* **Linked Lists:** Singly, doubly, and circularly linked lists. Know when they outperform arrays (e.g., constant time insertion/deletion at known locations).

## **3\. Focus Area: Practical Application (LeetCode/Practice)**

**Goal:** Translate theoretical knowledge into clean, efficient C++ code.

* **Daily LeetCode (Easy/Medium):** Focus on problems solvable with **Arrays, Strings, Two Pointers, and Sliding Window** techniques.  
* **Specific Algorithms to Master:**  
  * **Two Pointers:** Used for searching pairs, reversing arrays, or partitioning. (e.g., finding a pair that sums to target in a sorted array).  
  * **Sliding Window:** Used for problems requiring a sub-array/substring of a certain size or meeting a specific condition. (e.g., finding the longest substring without repeating characters).  
* **C++ Coding Style:** Ensure all practice solutions are written using modern C++ syntax, adhering to best practices (e.g., use const, range-based for loops, proper error handling/return types).