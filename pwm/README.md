### for `adv.c`
---
que;  
write a C code that scans a $4 \times 4$ matrix keyboard (16 switches) every $50\text{ ms}$.

- If the **last switch (switch 16)** is pressed, the **PWM signal should be stopped / withdrawn**.
- The remaining switches (**switches 1 to 15**) produce a PWM signal of **$5\%, 10\%, 15\%, 20\%, \dots$ up to $75\%$** respectively.
- Assume a **switching frequency of $1000\text{ Hz}$** ($T_s = 1\text{ ms}$).
- Use **Timer 0** to generate the PWM and **Timer 1** to scan the matrix keyboard at a **$50\text{ ms}$** rate  

### for `main.c`
---
for a fixed switching frequency $F_s = 2\text{ kHz}$ ($T_s = 0.5\text{ ms} = 500\text{ counts}$ at $1\text{ MHz}$) and a fixed duty cycle $D = 0.5$ ($t_{\text{on}} = 250\text{ counts}$):

- **Timer 1 Reload ($T_s$):** $65536 - 500 = 65036 = \text{0xFE0C}$ (`TH1 = 0xFE`, `TL1 = 0x0C`)
    
- **Timer 0 Reload ($t_{\text{on}}$):** $65536 - 250 = 65286 = \text{0xFF06}$ (`TH0 = 0xFF`, `TL0 = 0x06`)
