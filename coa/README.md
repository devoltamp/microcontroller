https://www.iitg.ac.in/asahu/cs222-2011/
# lect -- 03
## 1. Introduction to MIPS Architecture & Instruction Set

- **MIPS Acronyms**:
    
    - **Architecture / ISA**: **MIPS** stands for _Microprocessor without Interlocked Pipeline Stages_.
        
    - **Performance Metric**: **MIPS** also stands for _Millions of Instructions Per Second_.
        
- **ISA Background**: MIPS is a representative Reduced Instruction Set Computer (RISC) architecture developed since the 1980s. It has been widely used in commercial systems by NEC, Nintendo, Silicon Graphics, and Sony. It serves as a standard model for teaching because it is realistic yet clear and easy to understand.
    
- **Instructions as Machine Language**: Instructions are the primitive commands understandable directly by the hardware. Higher-Level Languages (HLLs) like C, C++, or Java must be compiled down into machine instructions.
    
- **Instruction Set Design Goals**:
    
    - **Maximize performance**: Execute commands as quickly as possible.
        
    - **Minimize cost**: Keep hardware architecture simple and affordable.
        
    - **Reduce design time**: Simplify hardware logic to speed up engineering and manufacturing.

## 2. Categories of Instructions

MIPS instructions are categorized into four primary types to cover program functionality:

1. **Arithmetic Instructions**: Perform mathematical operations (e.g., `add`, `sub`).
    
2. **Data Movement Instructions**: Move data between memory and CPU registers (e.g., `lw`, `sw`).
    
3. **Decision Making Instructions**: Handle logic, branching, and function execution (e.g., jumps, conditional branching).
    
4. **Handling Constant Operands**: Deal with immediate value operations encoded directly inside the instructions.

## 3. MIPS Arithmetic & Principles

- **Fixed Operand Format**: All arithmetic instructions have exactly **3 operands**, and the operand order is strictly fixed with the **destination register first**.
    
    - _Syntax_: `operation destination, source1, source2`
        
- **Design Principle — Simplicity Favors Regularity**: Keeping the number of operands fixed to 3 makes hardware decoding simpler and faster.
    
- **Design Principle — Smaller is Faster**: Arithmetic instructions cannot operate directly on memory; operands must be registers. MIPS provides **32 hardware registers** to maintain high operating speeds.
    

### Compiling Arithmetic Expressions into MIPS

Because each arithmetic operation takes only two source inputs, complex expressions must be broken down into individual hardware instructions using temporary registers.

- **Single Operation Example**:
    
    - C Code: $A = B + C$
        
    - MIPS Code: `add $s0, $s1, $s2` (Assuming `$s0=A`, `$s1=B`, `$s2=C`)
        
- **Multi-Step Operation Example**:
    
    - C Code:
        
        C
        
        ````shell
        A = B + C + D;
        E = F - A;
        ````
        
    - MIPS Assembly Translation:
        
        Code snippet
        
        ````shell
        add $t0, $s1, $s2    # $t0 = B + C (intermediate sum in temp register)
        add $s0, $t0, $s3    # $s0 = $t0 + D = B + C + D (A)
        sub $s4, $s5, $s0    # $s4 = F - A (E)
        ````

---
## 4. Hardware System View & Register Architecture

 Registers vs. Memory * **Registers**: High-speed internal hardware storage locations inside the processor[cite: 7, 8]. **Scalar variables** used heavily in programs are mapped directly to registers by the compiler[cite: 8]. * **Memory**: Larger, slower external storage[cite: 8, 9]. **Structures, arrays, and complex data objects** reside in main memory[cite: 8].

*don't need to read everything -- that i write*

| Register Name | Register Number | Usage / Purpose                                                     |
| :------------ | :-------------- | :------------------------------------------------------------------ |
| `$zero`       | `0`             | Hardwired constant value `0`                                        |
| `$v0 - $v1`   | `2 - 3`         | Expression evaluation and function return values                    |
| `$a0 - $a3`   | `4 - 7`         | Function arguments passed to subroutines                  |
| `$t0 - $t7`   | `8 - 15`        | Temporary registers (not preserved across function calls) |
| `$s0 - $s7`   | `16 - 23`       | Saved registers (preserved across function calls)         |
| `$t8 - $t9`   | `24 - 25`       | Additional temporary registers                            |
| `$gp`         | `28`            | Global Pointer (points to static global data)             |
| `$sp`         | `29`            | Stack Pointer (points to top of stack)                    |
| `$fp`         | `30`            | Frame Pointer (points to base of current stack frame)     |
| `$ra`         | `31`            | Return Address (stores return address for procedure call) |

---
## 6. Memory Organization & Addressing
### Byte Addressing 
Memory is modeled as a large, 1D single-dimensional array of 8-bit bytes, indexed by addresses. * **Capacity and Alignment**: * A 32-bit architecture addresses up to $2^{32}$ bytes (addresses from `0` to $2^{32}-1$). * Data is primarily accessed in **Words** (1 word = 4 bytes = 32 bits). * There are $2^{30}$ words in a 32-bit address space, with aligned word addresses occurring at multiples of 4: `0, 4, 8, 12, ... 2^32 - 4`. 
### Byte Ordering (Endianness) 
When storing a 4-byte word spanning byte addresses `0, 1, 2, 3`, endianness determines how bytes are ordered: * **Big-Endian**: The **Most Significant Byte (MSB)** is stored at the lowest byte address (Address 0). * **Little-Endian**: The **Least Significant Byte (LSB)** is stored at the lowest byte address (Address 0). * **Non-Aligned Word**: A word memory access where the starting address is not divisible by 4 (e.g., starting at address 1 or 2), causing misaligned access.

---

## 7. Memory Access Instructions (Load & Store)

Because arithmetic operations occur only inside registers, data must be transferred between registers and memory using **Load** and **Store** instructions:
* **`lw` (Load Word)**: Copies 4 bytes of data **from Memory into a Register**.
* **`sw` (Store Word)**: Copies 4 bytes of data **from a Register into Memory**
* **Address Calculation**: Address format is `offset(base_register)` where actual memory address = `base_register + offset`

ex.
* c code
```
A[8] = h + A[8];
```
 `A` -> `$s3`
 `h` -> `$s2`
 `A[8]` -> `32($s3)`
* MIPS code
```shell
lw $t0, 32($s3) # Read A[8] from memory. Offset = 8 elements * 4 bytes/element = 32 add $t0, $s2, $t0 # $t0 = h + A[8]
add $t0, $s2, $t0 # $t0 = h + A[8]
sw $t0, 32($s3) # Store result back into A[8] memory address
```
---
## 8. swap c code

```c
void swap(int v[], int k){
	int temp;
	temp = v[k];
	v[k] = v[k+1];
	v[k+1] = temp;
}
```
into the MIPS
```shell
swap:
	muli $2, $5, 4
	add $2, $4, $2
	lw $15, 0($2)
	lw $16, 4($2)
	sw $16, 0($2)
	sw $15, 4($2)
	jr $31
```
here the main aspect of byte offset is given,
byte offset = k * 4
$2 --> $v0 --> offset (k*4)
next, calculated the memory address

---

# lect -- 04
