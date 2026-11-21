the 8051 can access up to **$64\text{ KB}$ of external Program Memory (ROM)** and **$64\text{ KB}$ of external Data Memory (RAM)**:

- **Port 0 (`P0`):** Multiplexed lower address/data bus (`AD0–AD7`). Requires an external latch (**74LS373**) controlled by `ALE` to demultiplex `A0–A7`.
    
- **Port 2 (`P2`):** Outputs upper address byte (`A8–A15`).
    
- **Control Signals:**
    
    - `PSEN` (active low): Read strobe for external ROM (`code` space).
        
    - `RD` (`P3.7`) & `WR` (`P3.6`): Read/Write strobes for external RAM (`xdata` space).
        
- In Keil C51, the **`xdata`** keyword instructs the compiler to generate `MOVX` instructions (activating `RD`/`WR` on Port 0/2), while **`code`** uses `MOVC` (activating `PSEN`).
