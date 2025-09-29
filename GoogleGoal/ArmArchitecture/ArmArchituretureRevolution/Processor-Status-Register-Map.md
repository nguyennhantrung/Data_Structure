# **👑 Processor Status Register Map: CPSR vs. PSTATE**

This document maps the architectural transition from the single, consolidated AArch32 status register (CPSR) to the distributed, hierarchical processor state (PSTATE) in AArch64.

## **1\. AArch32: Consolidated Status (CPSR)**

In the 32-bit architecture (ARMv7 and earlier), the **Current Program Status Register (**CPSR**)** holds all condition flags, execution state, and privilege modes within a single 32-bit register.

### **A. Condition Code Flags (NZCV)**

The four main condition flags are grouped into the most significant bits (MSBs) of the CPSR. These flags are set automatically by the **Arithmetic Logic Unit (ALU)** after every data processing operation (e.g., ADD, SUB).

| Bit | Name | Function |
| :---- | :---- | :---- |
| 31 | **N** | **Negative:** Set if the result is negative (MSB is 1). |
| 30 | **Z** | **Zero:** Set if the result is zero. |
| 29 | **C** | **Carry:** Set if an unsigned overflow/carry-out occurred. |
| 28 | **V** | **Overflow:** Set if a signed overflow occurred. |

### **B. Processor Mode Field (Bits \[4:0\])**

The current level of privilege is determined by the 5-bit Mode field in the least significant bits (LSBs) of the CPSR. Changing these bits causes a **mode switch**, which involves switching between different banks of shadowed registers (like a separate SP for each mode).

| Binary Value | Mode Name | Description |
| :---- | :---- | :---- |
| 0b10000 | **User** | Unprivileged application code (EL0 Equivalent). |
| 0b10011 | **SVC** | Supervisor (OS Kernel) Mode. |
| 0b10111 | **Abort** | Handles memory access failures. |
| 0b11010 | **FIQ** | Fast Interrupt Request (highest priority interrupt). |
| 0b11111 | **System** | Privileged, but uses the same registers as User mode. |

CPSR Structure Summary (32 bits)31N​……​28V​…Reserved​7I/F​6T​5Reserved​…I/F​4Mode​…0​

## **2\. AArch64: Hierarchical State (PSTATE)**

AArch64 replaces the CPSR with the abstracted **Processor State (**PSTATE**)**. The information is now organized in a dedicated set of system registers, making the structure cleaner and more robust for modern computing tasks like virtualization.

### **A. Condition Flags (NZCV Register)**

The condition codes retain their familiar bit positions but are accessed through a **dedicated** NZCV **system register** using MRS (Move from System Register) and MSR (Move to System Register) instructions. This separation cleans up register access.

NZCV Register (Bits 31-28)……​31N​30Z​29C​28V​……​​

### **B. Exception Levels (ELs)**

Processor privilege is controlled by the **Exception Level** system, which defines a strict hierarchy, unlike the mixed modes of AArch32. The current EL is tracked internally within PSTATE via the CurrentEL field.

| Level | Name | AArch32 Equivalent | Key Responsibility |
| :---- | :---- | :---- | :---- |
| **EL3** | **Secure Monitor** | None | Highest privilege: Security, firmware, TrustZone control. |
| **EL2** | **Hypervisor** | None | Virtual Machine Monitor (VMM) and guest OS management. |
| **EL1** | **OS Kernel** | SVC Mode | Operating System kernel and drivers. |
| **EL0** | **Applications** | User Mode | Unprivileged user programs. |

**Key Advantage of ELs:** The system ensures that critical resources, like the Stack Pointer, are separate for each level. For example, the SP used in EL1 (SP\_EL1) is different from the SP used in EL0 (SP\_EL0). This separation is fundamental to securely managing different operating environments (like multiple VMs or an OS and its applications).