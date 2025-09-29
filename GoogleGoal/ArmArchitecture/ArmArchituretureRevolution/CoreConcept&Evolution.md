# **🧠 ARM Architecture: Core Concepts & Evolution Blueprint**

## **1\. AArch32 vs. AArch64 (The Fundamental Shift)**

### **🚀 Evolution and Address Space**

* **AArch32 (32-bit)**  
  * **Address Space:** 232 bytes (Max 4 GB RAM).  
  * **Instruction Sets:** A32 (ARM) and T32 (Thumb, 16/32-bit encoding).  
  * **Historical Context (User Curiosity):** Foundational architecture from ARMv1 up to ARMv7.  
* **AArch64 (64-bit)**  
  * **Address Space:** 264 bytes (Vastly larger memory support).  
  * **Instruction Set:** A64 (fixed 32-bit instructions).  
  * **Endianness (User Curiosity):** Bi-Endian by design, but modern implementations (Linux, Windows) default to **Little-Endian**.

## **2\. Register Sets (The CPU's Internal Storage)**

### **🗃️ General Purpose Registers (GPRs)**

* **AArch32 GPRs:** 16 registers (R0 \- R15), 32-bits wide.  
* **AArch64 GPRs:** 31 registers (X0 \- X30), **64-bits wide**.  
  * **W Registers (User Curiosity):** W0-W30 are aliases for the **lower 32 bits** of X0-X30. When using a W register, the upper 32 bits of the corresponding X register are zeroed out.  
  * **Upper 32 bits Access (User Curiosity):** There is no direct "Hn" register name; the upper bits are only manipulated using 64-bit instructions on the entire Xn register.

### **🌟 Special Registers (Detailed)**

* **Program Counter (**PC**)**  
  * **AArch32 Name & Behavior:** Alias for R15. When read, its value reflects the current instruction address plus 8 bytes (due to the pipeline design), which often confused developers.  
  * **AArch64 Name & Behavior:** Dedicated PC register, **not a GPR**. It holds the **exact** address of the instruction being executed, simplifying debugging and program flow.  
* **Stack Pointer (**SP**)**  
  * **AArch32 Name & Alignment:** Alias for R13, typically required to be **4-byte aligned** (word-aligned).  
  * **AArch64 Name & Alignment (CRITICAL):** Dedicated SP register. **Mandatory 16-byte alignment** at the point of any external interface (like function calls or exceptions). This strict alignment ensures the efficient and safe use of STP (STore Pair) and LDP (LoaD Pair) instructions.  
* **Program Status Flags**  
  * **AArch32 Name & Structure:** **CPSR** (Current Program Status Register). A single 32-bit register where different fields control processor mode, interrupt masking, and condition flags.  
  * **AArch64 Name & Structure:** **PSTATE** (Processor State). This is an abstraction, not a single visible register. The most important bits are the **Condition Flags (**NZCV**)**, which are handled separately.  
  * NZCV **Register (Detail):** Holds the four critical condition flags used by conditional Branch instructions:  
    * N (Negative): Set if the result was negative.  
    * Z (Zero): Set if the result was zero.  
    * C (Carry): Set if an arithmetic operation resulted in a carry-out (unsigned overflow).  
    * V (Overflow): Set if an arithmetic operation resulted in a signed overflow.

## **3\. Modes and Exception Levels (Privilege Hierarchy)**

### **🛡️ AArch32 Processor Modes**

* **Unprivileged:**  
  * **User Mode (EL0 Equivalent):** Lowest privilege. Runs application code. Cannot access critical control registers.  
* **Highly Privileged:**  
  * **Supervisor (SVC) Mode:** Runs the OS Kernel. Entered via a system call.  
  * **IRQ / FIQ / Abort / Undef Modes:** Handlers for interrupts and exceptions.

### **👑 AArch64 Exception Levels (ELs)**

* **Hierarchical Model:** Higher number \= higher privilege.  
  * **EL0 (User):** Applications (lowest privilege).  
  * **EL1 (OS Kernel):** Linux/Windows kernel, drivers.  
  * **EL2 (Hypervisor \- User Curiosity):** Dedicated level for running the **Virtual Machine Monitor** (VMM) to manage multiple guest OS instances securely.  
  * **EL3 (Secure Monitor):** Highest privilege for security and trusted boot firmware.

## **4\. Instruction Types (The Language of the CPU)**

### **🔑 The Three Pillars of RISC Operations**

* **Data Processing:**  
  * **Function:** Performs mathematical and logical calculations (e.g., ADD, SUB, LSL).  
  * **Constraint:** Must operate exclusively on data held in **registers**.  
* **Load/Store (The Most Frequent):**  
  * **Function:** Moves data between the registers and the external memory.  
  * **Examples:** LDR (Load Register), STR (Store Register).  
* **Branch:**  
  * **Function:** Changes the sequence of instructions by modifying the PC register. Essential for program flow control.  
  * **Examples:** B (Unconditional Jump), BL (Branch with Link \- used for function calls).