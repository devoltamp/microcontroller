- **Structure (`struct`):** Groups variables of different data types under one name; each member gets its own sequential memory location (total size = sum of members).
    
- **Union (`union`):** Overlays all members at the **exact same memory address** (total size = size of largest member).
    
- **Why it is heavily used in 8051 C:**
    
    1. **16-bit to 8-bit Byte Splitting:** Overlaying an `unsigned int` (2 bytes) with a `struct` of two `unsigned char`s lets you load 16-bit timer/PCA values directly into `TH0`/`TL0` without bit-shifting (`>> 8`) or masking (`& 0xFF`). _(Note: Keil C51 is **big-endian**, so the first `char` holds the MSB and the second holds the LSB.)_
        
    2. **Bit-Field Packing:** Packing flags into single bits inside a 1-byte `struct` saves scarce internal RAM ($128\text{ bytes}$).
