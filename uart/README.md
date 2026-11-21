the 8051 has a built-in full-duplex UART controlled via `SCON` (Serial Control) and `SBUF` (Serial Buffer). **Timer 1 in Mode 2 (8-bit auto-reload)** generates the baud rate clock.

- **Baud Rate Calculation ($11.0592\text{ MHz}$ crystal, $9600\text{ bps}$):**
    
$$\text{TH1} = 256 - \frac{11.0592\text{ MHz}}{12 \times 32 \times 9600} = 256 - 3 = 253 = \text{0xFD}$$
    
- **`SCON = 0x50`:** Selects **Mode 1** (8-bit UART, variable baud rate) and enables reception (`REN = 1`).
    
- **Flags:** `TI` sets when a byte finishes transmitting; `RI` sets when a byte is received in `SBUF`. Both must be cleared in software.
